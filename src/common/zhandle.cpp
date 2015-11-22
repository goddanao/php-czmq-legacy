#include "../czmq/zsocket.h"

Php::Value ZHandle::send_picture(Php::Parameters &param) {
    zmsg_t *msg = zmsg_new();
    ZMsg z(msg, false);
    z.append_picture(param);
    return (zmsg_send (&msg, get_socket()) == 0);
}

Php::Value ZHandle::recv_picture(Php::Parameters &param) {
    zmsg_t *msg = zmsg_recv (get_socket());
    if(!msg)
        return nullptr;
    ZMsg z(msg, true);
    return z.pop_picture(param);
}

Php::Value ZHandle::send_string(Php::Parameters &param) {
    zmsg_t *msg = zmsg_new();
    ZMsg z(msg, false);
    z.append_string(param);
    return (zmsg_send (&msg, get_socket()) == 0);
}

Php::Value ZHandle::recv_string(Php::Parameters &param) {
    zmsg_t *msg = zmsg_recv (get_socket());
    if(!msg)
        return nullptr;
    ZMsg z(msg, true);
    return z.pop_string();
}

Php::Value ZHandle::send(Php::Parameters &param) {
    Php::Value p(param[0]);
    zmsg_t *czmsg = ZMsg::msg_from_param(&p);
    return zmsg_send(&czmsg, get_socket());
}

Php::Value ZHandle::recv(Php::Parameters &param) {
    zmsg_t *msg = zmsg_recv (get_socket());
    if(!msg)
        return nullptr;
    return Php::Object("ZMsg", new ZMsg(msg, true));
}