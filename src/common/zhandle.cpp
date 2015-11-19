#include "../czmq/zsocket.h"

Php::Value ZHandle::_get_fd () const {
    return get_fd();
}

Php::Value ZHandle::_get_socket () const {
    return Php::Object("ZSocket", new ZSocket((zsock_t *) get_socket(), false));
}

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
    ZMsg *zmsg = dynamic_cast<ZMsg *>(param[0].implementation());
    zmsg_t *czmsg = zmsg_dup(zmsg->zmsg_handle());
    return zmsg_send(&czmsg, get_socket());
}

Php::Value ZHandle::recv(Php::Parameters &param) {
    zmsg_t *msg = zmsg_recv (get_socket());
    if(!msg)
        return nullptr;
    return Php::Object("ZMsg", new ZMsg(msg, true));
}