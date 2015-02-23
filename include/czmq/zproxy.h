#pragma once

#include "zactor.h"
#include "zutils.h"


class ZProxy : public ZActor {
private:
    bool _verbose = false;
public:
    ZProxy() : ZActor() {}
    zactor_t *zproxy_handle() const { return (zactor_t *) get_handle(); }

    void __construct(Php::Parameters &param);

    void set_verbose(Php::Parameters &param);

    void pause();

    void resume();

    void set_frontend(Php::Parameters &param);

    void set_backend(Php::Parameters &param);

    void set_capture(Php::Parameters &param);

    static Php::Class<ZProxy> php_register() {
        Php::Class<ZProxy> o("ZProxy");

        o.method("__construct", &ZProxy::__construct);
        o.method("set_verbose", &ZProxy::set_verbose);
        o.method("pause", &ZProxy::pause);
        o.method("resume", &ZProxy::resume);
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

        return o;
    }

};
