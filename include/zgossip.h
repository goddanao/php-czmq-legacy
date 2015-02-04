#pragma once

#include "zactor.h"

class ZGossip : public ZActor {
private:
    bool _stopped = false;
public:
    ZGossip() : ZActor() {}
    zactor_t *zgossip_handle() const { return (zactor_t *) get_handle(); }

    void __construct(Php::Parameters &param);

    void set_verbose(Php::Parameters &param);

    Php::Value bind(Php::Parameters &param);
    void connect(Php::Parameters &param);

    void configure(Php::Parameters &param);

    void set(Php::Parameters &param);

    void publish(Php::Parameters &param);

    Php::Value count();

    static Php::Class<ZGossip> php_register() {
        Php::Class<ZGossip> o("ZGossip");
        o.method("__construct", &ZGossip::__construct);
        o.method("set_verbose", &ZGossip::set_verbose);
        o.method("configure", &ZGossip::configure);
        o.method("bind", &ZGossip::bind);
        o.method("connect", &ZGossip::connect);
        o.method("set", &ZGossip::set);
        o.method("publish", &ZGossip::publish);
        o.method("count", &ZGossip::count);

        o.method("send", &ZGossip::send);
        o.method("recv", &ZGossip::recv);
        o.method("send_string", &ZGossip::send_string);
        o.method("recv_string", &ZGossip::recv_string);
        o.method("send_picture", &ZGossip::send_picture);
        o.method("recv_picture", &ZGossip::recv_picture);

        return o;
    }

};