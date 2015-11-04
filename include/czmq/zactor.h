#pragma once

#include "../common.h"
#include "../../include/czmq/zmsg.h"

class ZActor  : public ZHandle  {
private:
    bool _verbose = false;

public:
    ZActor() : ZHandle() {}
    ZActor(zactor_t *handle, bool owned) : ZHandle(handle, owned, "zactor") {}
    zactor_t *zactor_handle() const { return (zactor_t *) get_handle(); }

    void set_verbose (Php::Parameters &param) {
    	_verbose = param.size() > 0 ? param[0].boolValue() : true;
    	zstr_send (zactor_handle(), "VERBOSE");
    }

    Php::Value send_picture(Php::Parameters &param) {
        zmsg_t *msg = zmsg_new();
        ZMsg z(msg, false);
        z.append_picture(param);
        return (zmsg_send (&msg, get_socket()) == 0);
    }

    Php::Value recv_picture(Php::Parameters &param) {
        zmsg_t *msg = zmsg_recv (get_socket());
        if(!msg)
            return nullptr;
        ZMsg z(msg, true);
        return z.pop_picture(param);
    }

    Php::Value send_string(Php::Parameters &param) {
        zmsg_t *msg = zmsg_new();
        ZMsg z(msg, false);
        z.append_string(param);
        return (zmsg_send (&msg, get_socket()) == 0);
    }

    Php::Value recv_string(Php::Parameters &param) {
        zmsg_t *msg = zmsg_recv (get_socket());
        if(!msg)
            return nullptr;
        ZMsg z(msg, true);
        return z.pop_string();
    }

    Php::Value send(Php::Parameters &param) {
        ZMsg *zmsg = dynamic_cast<ZMsg *>(param[0].implementation());
        zmsg_t *czmsg = zmsg_dup(zmsg->zmsg_handle());
        return zmsg_send(&czmsg, get_socket());
    }

    Php::Value recv(Php::Parameters &param) {
        zmsg_t *msg = zmsg_recv (get_socket());
        if(!msg)
            return nullptr;
        return Php::Object("ZMsg", new ZMsg(msg, true));
    }

    static Php::Class<ZActor> php_register() {
        Php::Class<ZActor> o("ZActor");
        o.method("set_verbose", &ZActor::set_verbose);
        o.method("send", &ZActor::send);
        o.method("recv", &ZActor::recv);
        o.method("send_string", &ZActor::send_string);
        o.method("recv_string", &ZActor::recv_string);
        o.method("send_picture", &ZActor::send_picture);
        o.method("recv_picture", &ZActor::recv_picture);
        return o;
    }

};
