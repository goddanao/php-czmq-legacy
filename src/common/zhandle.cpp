#include "../czmq/zsocket.h"

Php::Value ZHandle::_get_socket() {
    return Php::Object("ZSocket", new ZSocket((zsock_t*) get_socket(), false));
}

Php::Value ZHandle::send_picture(Php::Parameters &param) {
    zmsg_t *msg = zmsg_new();
    ZMsg z(msg, false);
    z.append_picture(param);
    return _send (msg);
}

Php::Value ZHandle::recv_picture(Php::Parameters &param) {
    zmsg_t *msg = _recv ();
    if(!msg)
        return nullptr;
    ZMsg z(msg, true);
    return z.pop_picture(param);
}

Php::Value ZHandle::send_string(Php::Parameters &param) {
    zmsg_t *msg = ZUtils::phpvalue_to_zmsg(param[0]);
    return _send(msg);
}

Php::Value ZHandle::recv_string(Php::Parameters &param) {
    zmsg_t *msg = _recv ();
    if(!msg)
        return nullptr;
    ZMsg z(msg, true);
    return z.pop_string();
}

Php::Value ZHandle::send(Php::Parameters &param) {
    zmsg_t *msg = ZUtils::params_to_zmsg(param);
    return _send(msg);
}

Php::Value ZHandle::recv(Php::Parameters &param) {
    zmsg_t *msg = _recv ();
    if(!msg)
        return nullptr;
    return Php::Object("ZMsg", new ZMsg(msg, true));
}