#pragma once

#include "../common.h"

class ZAuth  : public ZActor, public Php::Base  {
private:

    static void *new_actor(Php::Parameters &param, zpoller_t *poller) {
        zactor_t *auth = zactor_new (zauth, NULL);
        if(auth) {
            if(param.size()>0 && param[0].boolValue()) {
                zstr_send (auth, "VERBOSE");
                zsock_wait(auth);
            }
        }
        return auth;
    }

public:

    ZAuth() : ZActor(&ZAuth::new_actor), Php::Base() { }
    zactor_t *zauth_handle() const { return (zactor_t *) get_handle(); }

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

        std::string mode = ZUtils::toUpper(param[0].stringValue()); // PLAIN CURVE GSSAPI
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
        o.method("__construct", &ZAuth::__construct, {
            Php::ByVal("verbose", Php::Type::Bool, false)
        });
        o.method("set_verbose", &ZAuth::set_verbose);
        o.method("recv", &ZAuth::recv);
        o.method("allow", &ZAuth::allow, {
            Php::ByVal("ip", Php::Type::String, true)
        });
        o.method("deny", &ZAuth::deny, {
             Php::ByVal("ip", Php::Type::String, true)
         });
        o.method("configure", &ZAuth::configure, {
            Php::ByVal("mode", Php::Type::String, true),
            Php::ByVal("path", Php::Type::String, false)
        });

       // IZSocket intf support
       ZHandle::register_izsocket((Php::Class<ZAuth> *) &o);

        o.property("AUTH_PLAIN", "PLAIN", Php::Const);
        o.property("AUTH_CURVE", "CURVE", Php::Const);
        o.property("AUTH_GSSAPI", "GSSAPI", Php::Const);

        return o;
    }

};
