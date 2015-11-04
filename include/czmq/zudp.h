#pragma once

#include "../common.h"
#include "zframe.h"
#include "zmsg.h"

class ZUdp : public ZHandle {
    SOCKET _socket;
public:
    ZUdp() : ZHandle() {}
    ZUdp(SOCKET handle, bool owned) : ZHandle(&handle, owned, "zudp") {}
    SOCKET  zudp_handle() const { return _socket; }

    void __construct(Php::Parameters &param);

    void send(Php::Parameters &param);

    Php::Value recv();

    static Php::Class<ZUdp> php_register() {
        Php::Class<ZUdp> o("ZUdp");
        o.method("__construct", &ZUdp::__construct);
        o.method("send", &ZUdp::send);
        o.method("recv", &ZUdp::recv);
        return o;
    }

};
