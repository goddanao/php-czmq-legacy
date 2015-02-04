#pragma once

#include "zactor.h"

class ZBeacon : public ZActor {
private:
    bool _verbose = false;
    bool _stopped = false;
public:
    ZBeacon() : ZActor() {}
    zactor_t *zbeacon_handle() const { return (zactor_t *) get_handle(); }

    void __construct(Php::Parameters &param);

    void set_verbose(Php::Parameters &param);

    Php::Value set_port(Php::Parameters &param);

    void subscribe(Php::Parameters &param);

    void unsubscribe(Php::Parameters &param);

    void publish(Php::Parameters &param);

    void silence();

    Php::Value recv(Php::Parameters &param);

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

        return o;
    }

};