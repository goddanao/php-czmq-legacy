#include <phpcpp.h>
#include "../../include/czmq/zmsg.h"
#include "../../include/czmq/zactor.h"

void ZActor::set_verbose (Php::Parameters &param) {
	_verbose = param.size() > 0 ? param[0].boolValue() : true;
	zstr_send (zactor_handle(), "VERBOSE");
}

Php::Value ZActor::send_picture(Php::Parameters &param) {
    zmsg_t *msg = zmsg_new();
    ZMsg z(msg, false);
    z.append_picture(param);
    return (zmsg_send (&msg, get_socket()) == 0);
}

Php::Value ZActor::recv_picture(Php::Parameters &param) {
    zmsg_t *msg = zmsg_recv (get_socket());
    if(!msg)
        return nullptr;
    ZMsg z(msg, true);
    return z.pop_picture(param);
}

Php::Value ZActor::send_string(Php::Parameters &param) {
    zmsg_t *msg = zmsg_new();
    ZMsg z(msg, false);
    z.append_string(param);
    zsys_info("stocazzo prima");
    void *cc = this->get_socket();
    zsys_info("stocazzo prima get_socket");
    bool rc = (zmsg_send (&msg, cc) == 0);
     zsys_info("stocazzo dopo");
    return rc;
}

Php::Value ZActor::recv_string(Php::Parameters &param) {
    zmsg_t *msg = zmsg_recv (get_socket());
    if(!msg)
        return nullptr;
    ZMsg z(msg, true);
    return z.pop_string();
}

Php::Value ZActor::send(Php::Parameters &param) {
    ZMsg *zmsg = dynamic_cast<ZMsg *>(param[0].implementation());
    zmsg_t *czmsg = zmsg_dup(zmsg->zmsg_handle());
    return zmsg_send(&czmsg, get_socket());
}

Php::Value ZActor::recv(Php::Parameters &param) {
    zmsg_t *msg = zmsg_recv (get_socket());
    if(!msg)
        return nullptr;
    return Php::Object("ZMsg", new ZMsg(msg, true));
}