#include "../../include/majordomo/mdp_client.h"
#include "../../include/czmq/zmsg.h"

MajordomoClient::~MajordomoClient() {
	if (client)
		zsock_destroy (&client);
}

void MajordomoClient::__construct(Php::Parameters &param) {
	if(param.size() == 0)
		throw Php::Exception("MajordomoClient need broker endpoint to connect.");

	broker = param[0].stringValue();
	if(param.size() > 1)
		verbose = (int) param[1];

	connect_to_broker ();
}

void MajordomoClient::connect_to_broker () {
 	if (client)
        zsock_destroy (&client);

    client = zsock_new_dealer (broker.c_str());
    zsock_set_linger(client, 0);

    if (verbose)
        zclock_log ("I: connecting to broker at %s...", broker.c_str());
}

void MajordomoClient::send (char * service, zmsg_t **request_p) {
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

zmsg_t * MajordomoClient::recv (char **command_p, char **service_p) {

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

Php::Value MajordomoClient::call(Php::Parameters &param){

	if(param.size() == 0)
		throw Php::Exception("MajordomoClient call need service name and params..");

	std::string service = param[0];

	if(param.size() > 1)
		std::string params = param[1];

    // Qua devo confezionare la richiesta

	zmsg_t *request = zmsg_new ();
	zmsg_pushstr (request, "Hello world");
	send ((char*) service.c_str(), &request);
	zmsg_t *reply = recv (NULL, NULL);

    if(reply) {
	    Php::Object result("Zmsg", new ZMsg(reply, true));
        return result;
    } else {
        return nullptr;
    }
}

void MajordomoClient::call_async(Php::Parameters &param){

	if(param.size() == 0)
		throw Php::Exception("MajordomoClient call_async need service name and params..");

	std::string service = param[0];

	if(param.size() > 1)
		std::string params = param[1];

	zmsg_t *request = zmsg_new ();
	zmsg_pushstr (request, "Hello world");
	send ((char*) service.c_str(), &request);

}