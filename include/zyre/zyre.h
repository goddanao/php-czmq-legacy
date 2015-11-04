#pragma once

#include "../common.h"
#include <zyre.h>

class Zyre : public ZHandle {
private:
    bool _verbose = false;
public:
    Zyre() : ZHandle() {}
    Zyre(zyre_t *handle, bool owned) : ZHandle(handle, owned, "zyre") {}
    zyre_t *zyre_handle() { return (zyre_t *) get_handle(); }

   void __construct(Php::Parameters &param);

    Php::Value get_uuid();

    Php::Value get_name();
    Php::Value get_peers();
    Php::Value get_groups();
    Php::Value set_endpoint(Php::Parameters &param);
    void gossip_bind(Php::Parameters &param);
    void gossip_connect(Php::Parameters &param);
    Php::Value get_peer_header(Php::Parameters &param);

    static Php::Value get_version();

    void dump();

    void set_verbose();

    void set_header(Php::Parameters &param);

    Php::Value start();

    void stop();

    Php::Value join(Php::Parameters &param);

    Php::Value leave(Php::Parameters &param);

    Php::Value recv();

    Php::Value send_peer(Php::Parameters &param);

    Php::Value send_group(Php::Parameters &param);

    static Php::Class<Zyre> php_register() {

        Php::Class<Zyre> o("Zyre");

        o.method("__construct", &Zyre::__construct, {
            Php::ByVal("name", Php::Type::String, false)
        });

        o.method("start", &Zyre::start);
        o.method("stop", &Zyre::stop);
        o.method("recv", &Zyre::recv);
        o.method("dump", &Zyre::dump);
        o.method("get_uuid", &Zyre::get_uuid);

        o.method("get_name", &Zyre::get_name);
        o.method("get_peers", &Zyre::get_peers);
        o.method("get_groups", &Zyre::get_groups);
        o.method("set_endpoint", &Zyre::set_endpoint, {
            Php::ByVal("endpoint", Php::Type::String, true)
        });
        o.method("gossip_bind", &Zyre::gossip_bind, {
            Php::ByVal("endpoint", Php::Type::String, true)
        });
        o.method("gossip_connect", &Zyre::gossip_connect, {
            Php::ByVal("endpoint", Php::Type::String, true)
        });
        o.method("get_peer_header", &Zyre::get_peer_header, {
            Php::ByVal("name", Php::Type::String, true)
        });

        o.method("get_version", &Zyre::get_version);
        o.method("set_verbose", &Zyre::set_verbose);

        o.method("set_header", &Zyre::set_header, {
            Php::ByVal("name", Php::Type::String, true),
            Php::ByVal("value", Php::Type::String, true)
        });

        o.method("join", &Zyre::join, {
            Php::ByVal("group", Php::Type::String, true)
        });
        o.method("leave", &Zyre::leave, {
            Php::ByVal("group", Php::Type::String, true)
        });
        o.method("send_peer", &Zyre::send_peer, {
            Php::ByVal("peer", Php::Type::String, true),
            Php::ByVal("data", Php::Type::String, true)
        });
        o.method("send_group", &Zyre::send_group, {
            Php::ByVal("group", Php::Type::String, true),
            Php::ByVal("data", Php::Type::String, true)
        });



        return o;
    }

};
