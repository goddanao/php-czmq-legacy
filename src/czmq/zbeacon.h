#pragma once

#include "../common.h"

class ZBeacon : public ZHandle, public Php::Base {
public:

    ZBeacon() : ZHandle(), Php::Base() {}
    zactor_t *zbeacon_handle() const { return (zactor_t *) get_handle(); }

    void __construct(Php::Parameters &param) {
        set_handle(zactor_new(zbeacon, NULL), true, "zactor");
    }

    void set_verbose() {
        zstr_send (zbeacon_handle(), "VERBOSE");
    }

    Php::Value set_port(Php::Parameters &param) {
        int port_number = param[0].numericValue();
        zsock_send (zbeacon_handle(), "si", "CONFIGURE", port_number);
        char *port =  zstr_recv (zbeacon_handle());
        Php::Value result = port;
        zstr_free(&port);
        return result;
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

        o.method("__construct", &ZBeacon::__construct);
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

        // IZSocket intf support
        o.method("get_fd", &ZBeacon::get_fd);
        o.method("get_socket", &ZBeacon::_get_socket);

        return o;
    }

};