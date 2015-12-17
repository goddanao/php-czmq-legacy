#pragma once

#include "../common.h"

class ZBeacon : public ZActor, public Php::Base {
private:

    static void *new_actor(Php::Parameters &param, zpoller_t *poller) {
        zactor_t *beacon = zactor_new (zbeacon, NULL);
        if(beacon) {
            if(param.size()>0 && param[0].boolValue()) {
                zstr_send (beacon, "VERBOSE");
            }
        }
        return beacon;
    }

public:

    ZBeacon() : ZActor(&ZBeacon::new_actor), Php::Base() { }
    zactor_t *zbeacon_handle() const { return (zactor_t *) get_handle(); }

    void set_verbose() {
        zstr_send (zbeacon_handle(), "VERBOSE");
    }

    Php::Value set_port(Php::Parameters &param) {
        int port_number = param[0].numericValue();
        zsock_send (zbeacon_handle(), "si", "CONFIGURE", port_number);
        char *hostname =  zstr_recv (zbeacon_handle());
        if(*hostname) {
            Php::Value result = hostname;
            zstr_free(&hostname);
            return result;
        }
        return false;
    }

    void subscribe(Php::Parameters &param) {
        std::string filter = param[0].stringValue();
        zsock_send (zbeacon_handle(), "sb", "SUBSCRIBE", filter.c_str(), filter.size());
    }

    void unsubscribe(Php::Parameters &param) {
        zstr_sendx (zbeacon_handle(), "UNSUBSCRIBE", NULL);
    }

    void publish(Php::Parameters &param) {
        int interval  = (param.size() > 1) ? (int) param[1] : 1000;
        std::string data = param[0].stringValue();
        zsock_send (zbeacon_handle(), "sbi", "PUBLISH", data.c_str(), data.size(), interval);
    }

    void silence() {
        zstr_sendx (zbeacon_handle(), "SILENCE", NULL);
    }

    static Php::Class<ZBeacon> php_register() {
        Php::Class<ZBeacon> o("ZBeacon");

        o.method("__construct", &ZBeacon::__construct, {
            Php::ByVal("verbose", Php::Type::Bool, false)
        });
        o.method("set_verbose", &ZBeacon::set_verbose);
        o.method("set_port", &ZBeacon::set_port, {
            Php::ByVal("port", Php::Type::Numeric, true),
        });
        o.method("subscribe", &ZBeacon::subscribe, {
             Php::ByVal("filter", Php::Type::String, true),
         });
        o.method("unsubscribe", &ZBeacon::unsubscribe);

        o.method("publish", &ZBeacon::publish, {
            Php::ByVal("data", Php::Type::String, true),
            Php::ByVal("interval", Php::Type::Numeric, false)
        });

        o.method("silence", &ZBeacon::silence);
        o.method("recv", &ZBeacon::recv);

        // ZEmitter
        o.method("start", &ZBeacon::start);
        ZHandle::register_izemitter((Php::Class<ZBeacon> *) &o);

        // IZSocket intf support
        ZHandle::register_izsocket((Php::Class<ZBeacon> *) &o);

        return o;
    }

};