#pragma once

#include "zactor.h"

class ZAuth  : public ZActor {
public:
    ZAuth() : ZActor() {}
    zactor_t *zauth_handle() const { return (zactor_t *) get_handle(); }

    void __construct(Php::Parameters &param);

    void set_verbose();

    void allow(Php::Parameters &param);

    void deny(Php::Parameters &param);

    void configure(Php::Parameters &param);

    static Php::Class<ZAuth> php_register() {
        Php::Class<ZAuth> o("ZAuth");
        o.method("__construct", &ZAuth::__construct);
        o.method("set_verbose", &ZAuth::set_verbose);
        o.method("allow", &ZAuth::allow, {
            Php::ByVal("ip", Php::Type::String, true)
        });
        o.method("deny", &ZAuth::deny, {
             Php::ByVal("ip", Php::Type::String, true)
         });
        o.method("configure", &ZAuth::configure);
        o.property("AUTH_PLAIN", "PLAIN", Php::Const);
        o.property("AUTH_CURVE", "CURVE", Php::Const);
        o.property("AUTH_GSSAPI", "GSSAPI", Php::Const);
        return o;
    }

};
