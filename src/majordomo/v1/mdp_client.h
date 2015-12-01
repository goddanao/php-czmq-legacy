#pragma once

#include "../../czmq/zmsg.h"
#include "zmdp_common.h"

class MajordomoClientV1 : public ZHandle, public Php::Base {
private:
  std::string _broker;
  bool _verbose = false;
  int timeout = 30000;      //  default 30s timeout

  void connect_to_broker () {
    zsock_t *sock = mdp_client_handle();
    if (sock)
  	    zsock_destroy (&sock);

  		sock = zsock_new_dealer (_broker.c_str());
  		zsock_set_linger(sock, 0);

        set_handle(sock, true, "mdp_client_v1");

  		if (_verbose)
  			zclock_log ("I: connecting to broker at %s...", _broker.c_str());
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
        if (_verbose) {
            zclock_log ("I: send request to '%s' service:", service);
            zmsg_dump (request);
        }
        zmsg_send (request_p, mdp_client_handle());
  }

  	zmsg_t * recv (char **command_p, char **service_p) {

  		zmsg_t *msg = zmsg_recv (mdp_client_handle());
  		if (msg == NULL)
  			return NULL;

  		if (_verbose) {
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

    MajordomoClientV1() : ZHandle(), Php::Base() {}
    MajordomoClientV1(zsock_t *handle, bool owned) : ZHandle(handle, owned, "mdp_client_vX"), Php::Base() {}
    zsock_t *mdp_client_handle() const { return (zsock_t *) get_handle(); }

	void __construct(Php::Parameters &param) {
		if(param.size() == 0)
			throw Php::Exception("MajordomoClient need broker endpoint to connect.");

		_broker = param[0].stringValue();
		if(param.size() > 1)
			_verbose = param[1].boolValue();

		connect_to_broker ();
	}

	Php::Value call(Php::Parameters &param){

		if(param.size() == 0)
			throw Php::Exception("MajordomoClient call need service name and params..");

		zmsg_t *zmsg = nullptr;
		if(param.size() > 1) {
			zmsg = ZUtils::phpvalue_to_zmsg(param[1]);
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

    static Php::Class<MajordomoClientV1> php_register() {
        Php::Class<MajordomoClientV1> o("Client");
        o.method("__construct", &MajordomoClientV1::__construct);
        o.method("call", &MajordomoClientV1::call, {
            Php::ByVal("service", Php::Type::String, true),
            Php::ByVal("data", Php::Type::String, false)
        });
        o.method("call_async", &MajordomoClientV1::call_async, {
             Php::ByVal("service", Php::Type::String, true),
             Php::ByVal("data", Php::Type::String, false)
        });

        // IZSocket intf support
		o.method("get_fd", &MajordomoClientV1::get_fd);
        o.method("get_socket", &MajordomoClientV1::_get_socket);

        return o;
    }

};