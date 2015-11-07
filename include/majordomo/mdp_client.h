#pragma once

#include <phpcpp.h>
#include <czmq.h>
#include "zmdp_common.h"
#include "../../include/czmq/zmsg.h"

class MajordomoClient : public Php::Base {
private:
  std::string broker;
  zsock_t *client = NULL;   //  Socket to broker
  int verbose = 0;          //  Print activity to stdout
  int timeout = 30000;      //  default 30s timeout

  void connect_to_broker () {
  		if (client)
  			zsock_destroy (&client);

  		client = zsock_new_dealer (broker.c_str());
  		zsock_set_linger(client, 0);

  		if (verbose)
  			zclock_log ("I: connecting to broker at %s...", broker.c_str());
  	}

  void send (char * service, zmsg_t **request_p) {
      zmsg_t *request = *request_p;

        //  Prefix request with protocol frames
        //  Frame 1: empty frame (delimiter)
        //  Frame 2: "MDPCxy" (six bytes, MDP/Client x.y)
        //  Frame 3: Service name (printable string)
        zmsg_pushstr (request, service);
        zmsg_pushstr (request, MDPC_CLIENT);
        zmsg_pushstr (request, "");
        if (verbose) {
            zclock_log ("I: send request to '%s' service:", service);
            zmsg_dump (request);
        }
        zmsg_send (request_p, client);
  }

  	zmsg_t * recv (char **command_p, char **service_p) {

  		zmsg_t *msg = zmsg_recv (client);
  		if (msg == NULL)
  			return NULL;

  		if (verbose) {
  			zclock_log ("I: received reply:");
  			zmsg_dump (msg);
  		}

  		//  Message format:
  		//  Frame 1: empty frame (delimiter)
  		//  Frame 2: "MDPCxy" (six bytes, MDP/Client x.y)
  		//  Frame 3: REPORT|NAK
  		//  Frame 4: Service name (printable string)
  		//  Frame 5..n: Application frames

  		//  We would handle malformed replies better in real code
  		assert (zmsg_size (msg) >= 5);

  		zframe_t *empty = zmsg_pop (msg);
  		assert (zframe_streq (empty, ""));
  		zframe_destroy (&empty);

  		zframe_t *header = zmsg_pop (msg);
  		assert (zframe_streq (header, MDPC_CLIENT));
  		zframe_destroy (&header);

  		zframe_t *command = zmsg_pop (msg);
  		assert (zframe_streq (command, MDPC_REPORT) ||
  				zframe_streq (command, MDPC_NAK));
  		if (command_p)
  			*command_p = zframe_strdup (command);
  		zframe_destroy (&command);

  		zframe_t *service = zmsg_pop (msg);
  		if (service_p)
  			*service_p = zframe_strdup (service);
  		zframe_destroy (&service);

  		return msg;     //  Success
  	}

public:

    MajordomoClient() : Php::Base() { };
    virtual ~MajordomoClient() {
		if (client)
			zsock_destroy (&client);
	}

	void __construct(Php::Parameters &param) {
		if(param.size() == 0)
			throw Php::Exception("MajordomoClient need broker endpoint to connect.");

		broker = param[0].stringValue();
		if(param.size() > 1)
			verbose = (int) param[1];

		connect_to_broker ();
	}

	Php::Value call(Php::Parameters &param){

		if(param.size() == 0)
			throw Php::Exception("MajordomoClient call need service name and params..");

		zmsg_t *zmsg = nullptr;

		if(param.size() > 1) {
		    if(param[1].isString()) {
		        zmsg = zmsg_new ();
                zmsg_pushstr (zmsg, param[1].stringValue().c_str());
		    } else {
                ZMsg *zzmsg = dynamic_cast<ZMsg *>(param[1].implementation());
                if(zzmsg) {
                    zmsg = zmsg_dup(zzmsg->zmsg_handle());
                } else {
                    ZFrame *frame = dynamic_cast<ZFrame *>(param[1].implementation());
                    if(frame) {
                        zmsg = zmsg_new ();
                        zmsg_pushmem (zmsg, zframe_data(frame->zframe_handle()), zframe_size(frame->zframe_handle()));
                    }
                }
            }
		}


		// Qua devo confezionare la richiesta
        if(zmsg) {
		    send ((char *) param[0].stringValue().c_str(), &zmsg);
		    zmsg_t *reply = recv (NULL, NULL);
            if(reply)
                return Php::Object("Zmsg", new ZMsg(reply, true));

        }

        return nullptr;
	}

	void call_async(Php::Parameters &param){

		if(param.size() == 0)
			throw Php::Exception("MajordomoClient call_async need service name and params..");

		std::string service = param[0];

		if(param.size() > 1)
			std::string params = param[1];

		zmsg_t *request = zmsg_new ();
		zmsg_pushstr (request, "Hello world");
		send ((char*) service.c_str(), &request);

	}

    static Php::Class<MajordomoClient> php_register() {
        Php::Class<MajordomoClient> o("MajordomoClient");
        o.method("__construct", &MajordomoClient::__construct);
        o.method("call", &MajordomoClient::call);
        o.method("call_async", &MajordomoClient::call_async);
        return o;
    }

};