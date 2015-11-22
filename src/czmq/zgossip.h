#pragma once

#include "../common.h"

class ZGossip : public ZHandle, public Php::Base {
private:
    bool _stopped = false;

public:

    ZGossip() : ZHandle(), Php::Base() {}
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

    Php::Value recv(Php::Parameters &param) {
        zmsg_t *msg = zmsg_recv (get_socket());
        if(!msg)
            return nullptr;
        return Php::Object("ZMsg", new ZMsg(msg, true));
    }

    static Php::Class<ZGossip> php_register() {
        Php::Class<ZGossip> o("ZGossip");
        o.method("__construct", &ZGossip::__construct);
        o.method("set_verbose", &ZGossip::set_verbose);

        o.method("configure", &ZGossip::configure, {
            Php::ByVal("filename", Php::Type::String, true)
        });
        o.method("bind", &ZGossip::bind, {
            Php::ByVal("endpoint", Php::Type::String, true)
        });
        o.method("connect", &ZGossip::connect, {
            Php::ByVal("endpoint", Php::Type::String, true)
        });
        o.method("set", &ZGossip::set, {
            Php::ByVal("property", Php::Type::String, true),
            Php::ByVal("value", Php::Type::String, true)
        });
        o.method("publish", &ZGossip::publish, {
            Php::ByVal("property", Php::Type::String, true),
            Php::ByVal("value", Php::Type::String, true)
        });

        o.method("count", &ZGossip::count);

        o.method("recv", &ZGossip::recv);

        // IZSocket intf support
        o.method("get_socket", &ZGossip::_get_socket);
        o.method("get_fd", &ZGossip::_get_fd);

        return o;
    }

};