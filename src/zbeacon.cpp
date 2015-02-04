#include "../include/zbeacon.h"
#include "../include/zmsg.h"

void ZBeacon::__construct(Php::Parameters &param) {
	set_handle(zactor_new(zbeacon, NULL), true, "zactor");
}

void ZBeacon::set_verbose(Php::Parameters &param) {
    zstr_send (zbeacon_handle(), "VERBOSE");
}

Php::Value ZBeacon::set_port(Php::Parameters &param) {
    int port_number = param[0].numericValue();
    zsock_send (zbeacon_handle(), "si", "CONFIGURE", port_number);
    char *port =  zstr_recv (zbeacon_handle());
    Php::Value result = port;
    free(port);
    return result;
}

void ZBeacon::subscribe(Php::Parameters &param) {
    std::string filter = param[0].stringValue();
    zsock_send (zbeacon_handle(), "sb", "SUBSCRIBE", filter.c_str(), filter.size());
}

void ZBeacon::unsubscribe(Php::Parameters &param) {
    zstr_sendx (zbeacon_handle(), "UNSUBSCRIBE", NULL);
}

void ZBeacon::publish(Php::Parameters &param) {
    int interval  = (param.size() > 1) ? (int) param[1] : 1000;
    std::string data = param[0];
    zsock_send (zbeacon_handle(), "sbi", "PUBLISH", data.c_str(), data.size(), interval);
}

void ZBeacon::silence() {
    zstr_sendx (zbeacon_handle(), "SILENCE", NULL);
}

Php::Value ZBeacon::recv(Php::Parameters &param) {
    int rcvtimeout = param.size() > 0 ? param[0].numericValue() : 500;

    void *zbsocket = get_socket();
    zsock_set_rcvtimeo(zbsocket, rcvtimeout);

    if(!socket)
        throw Php::Exception("ZBeacon error while accessing zmq socket handle for zactor.");

   	while(!_stopped) {
   		zmsg_t *msg = zmsg_recv(zbsocket);
   		if(!msg)
   		    break;
   		else
   		    return Php::Object("ZMsg", new ZMsg(msg, true));
   	}
   	return nullptr;
}
