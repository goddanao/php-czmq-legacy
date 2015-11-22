#pragma once

#include "../common.h"

class ZProxy : public ZHandle, public Php::Base {
private:
    bool _verbose = false;
public:
    ZProxy() : ZHandle(), Php::Base() {}
    zactor_t *zproxy_handle() const { return (zactor_t *) get_handle(); }

    void __construct(Php::Parameters &param) {
        set_handle(zactor_new(zproxy, NULL), true, "zactor");
    }

    void pause() {
        zstr_sendx (zproxy_handle(), "PAUSE", NULL);
        zsock_wait (zproxy_handle());
    }

    void resume() {
        zstr_sendx (zproxy_handle(), "RESUME", NULL);
        zsock_wait (zproxy_handle());
    }

    void set_verbose(Php::Parameters &param) {
        _verbose = param.size() > 0 ? param[0].boolValue() : true;
        if(!_verbose)
            return;
        zstr_sendx (zproxy_handle(), "VERBOSE", NULL);
        zsock_wait (zproxy_handle());
    }

    void set_frontend(Php::Parameters &param) {
        if(param.size() < 2)
            return;
        std::string socket_type = toUpper(param[0].stringValue());
        std::string socket_endpoints = param[1];
        zstr_sendx(zproxy_handle(), "FRONTEND", socket_type.c_str(), socket_endpoints.c_str(), NULL);
        zsock_wait(zproxy_handle());
    }

    void set_backend(Php::Parameters &param) {
        if(param.size() < 2)
            return;
        std::string socket_type = toUpper(param[0]);
        std::string socket_endpoints = param[1];
        zstr_sendx(zproxy_handle(), "BACKEND", socket_type.c_str(), socket_endpoints.c_str(), NULL);
        zsock_wait(zproxy_handle());
    }

    void set_capture(Php::Parameters &param) {
        if(param.size() < 1)
            return;
        std::string socket_endpoints = param[0];
        zstr_sendx(zproxy_handle(), "CAPTURE", socket_endpoints.c_str(), NULL);
        zsock_wait(zproxy_handle());
    }

    Php::Value recv(Php::Parameters &param) {
        zmsg_t *msg = zmsg_recv (get_socket());
        if(!msg)
            return nullptr;
        return Php::Object("ZMsg", new ZMsg(msg, true));
    }

    static Php::Class<ZProxy> php_register() {
        Php::Class<ZProxy> o("ZProxy");

        o.method("__construct", &ZProxy::__construct);
        o.method("set_verbose", &ZProxy::set_verbose);
        o.method("pause", &ZProxy::pause);
        o.method("resume", &ZProxy::resume);
        o.method("recv", &ZProxy::recv);

        o.method("set_frontend", &ZProxy::set_frontend, {
            Php::ByVal("socket_type", Php::Type::String, true),
            Php::ByVal("socket_endpoint", Php::Type::String, true)
        });
        o.method("set_backend", &ZProxy::set_backend, {
            Php::ByVal("socket_type", Php::Type::String, true),
            Php::ByVal("socket_endpoint", Php::Type::String, true)
        });
        o.method("set_capture", &ZProxy::set_capture, {
            Php::ByVal("socket_endpoint", Php::Type::String, true)
        });

        // IZSocket intf support
        o.method("get_socket", &ZProxy::_get_socket);
        o.method("get_fd", &ZProxy::_get_fd);

        return o;
    }

};
