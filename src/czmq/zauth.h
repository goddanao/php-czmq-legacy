#pragma once

#include "../common.h"

class ZAuth  : public ZHandle, public Php::Base  {
public:
    ZAuth() : ZHandle(), Php::Base() {}
    zactor_t *zauth_handle() const { return (zactor_t *) get_handle(); }

    void __construct(Php::Parameters &param) {
        set_handle(zactor_new(zauth, NULL), true, "zactor");
    }

    void set_verbose() {
        zstr_send (zauth_handle(), "VERBOSE");
        zsock_wait(zauth_handle());
    }

    void allow(Php::Parameters &param) {
        zstr_sendx (zauth_handle(), "ALLOW", param[0].stringValue().c_str(), NULL);
        zsock_wait(zauth_handle());
    }

    void deny(Php::Parameters &param) {
        zstr_sendx (zauth_handle(), "DENY", param[0].stringValue().c_str(), NULL);
        zsock_wait(zauth_handle());
    }

    void configure(Php::Parameters &param) {
        if(param.size() == 0)
            return;

        std::string mode = param[0]; // PLAIN CURVE GSSAPI
        if(mode == "PLAIN") {
            if(param.size() < 2) {
                throw Php::Exception("Auth mode PLAIN requires a config filename.");
            }
            std::string filename = param[1];
            zstr_sendx (zauth_handle(), "PLAIN", (void *) filename.c_str(), NULL);
            zsock_wait(zauth_handle());
        }
        else
        if(mode == "CURVE") {
            if(param.size() < 2) {
                throw Php::Exception("Auth mode CURVE requires a directory storing client keys.");
            }
            std::string directory = param[1];
            zstr_sendx (zauth_handle(), "CURVE", (void *) directory.c_str(), NULL);
            zsock_wait(zauth_handle());
        }
        else
        if(mode == "GSSAPI") {
            zstr_sendx (zauth_handle(), "GSSAPI", NULL);
            zsock_wait(zauth_handle());
        }
        else {
            throw Php::Exception("Auth mode not supported.");
        }
    }

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

        o.method("get_socket", &ZAuth::_get_socket);
        o.method("get_fd", &ZAuth::_get_fd);

        o.property("AUTH_PLAIN", "PLAIN", Php::Const);
        o.property("AUTH_CURVE", "CURVE", Php::Const);
        o.property("AUTH_GSSAPI", "GSSAPI", Php::Const);

        return o;
    }

};
