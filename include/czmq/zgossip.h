#pragma once

#include "../common.h"
#include "zactor.h"


class ZGossip : public ZActor, public Php::Base {
private:
    bool _stopped = false;
public:
    ZGossip() : ZActor(), Php::Base() {}
    zactor_t *zgossip_handle() const { return (zactor_t *) get_handle(); }


    void __construct(Php::Parameters &param) {
        set_handle(zactor_new(zgossip, NULL), true, "zactor");
    }

    void set_verbose(Php::Parameters &param) {
        zstr_send (zgossip_handle(), "VERBOSE");
    }

    Php::Value bind(Php::Parameters &param) {
        Php::Value result;
        zstr_sendx (zgossip_handle(), "BIND", param[0].stringValue().c_str(), NULL);
        zstr_sendx (zgossip_handle(), "PORT", NULL);
        char *command, *port_str;
        zstr_recvx (zgossip_handle(), &command, &port_str, NULL);
        if (streq (command, "PORT") && port_str != NULL) {
            std::string port(port_str);
            result = port;
        }
        if(command)
            free(command);
        if(port_str)
            free(port_str);
        return result.isNull() ? nullptr : result;
    }

    void connect(Php::Parameters &param) {
        zstr_sendx (zgossip_handle(), "CONNECT", param[0].stringValue().c_str(), NULL);
    }

    void configure(Php::Parameters &param) {
        zstr_sendx (zgossip_handle(), "LOAD", param[0].stringValue().c_str(), NULL);
    }

    void set(Php::Parameters &param) {
        zstr_sendx (zgossip_handle(), "SET", param[0].stringValue().c_str(), param[1].stringValue().c_str(), NULL);
    }

    void publish(Php::Parameters &param) {
        zstr_sendx (zgossip_handle(), "PUBLISH", param[0].stringValue().c_str(), param[1].stringValue().c_str(), NULL);
    }

    Php::Value count() {
        zstr_sendx (zgossip_handle(), "STATUS", NULL);
        char *command, *status;
        zstr_recvx (zgossip_handle(), &command, &status, NULL);
        assert (streq (command, "STATUS"));
        Php::Value result = status;
        free(command);
        free(status);
        return result;
    }

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