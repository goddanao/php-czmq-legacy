#pragma once

#include "zhandle.h"

class ZActor  : public ZHandle {
private:
    bool _verbose = false;
public:
    ZActor() : ZHandle() {}
    ZActor(zactor_t *handle, bool owned) : ZHandle(handle, owned, "zactor") {}
    zactor_t *zactor_handle() const { return (zactor_t *) get_handle(); }

    void set_verbose (Php::Parameters &param);

    static Php::Class<ZActor> php_register() {
        Php::Class<ZActor> o("ZActor");
        o.method("set_verbose", &ZActor::set_verbose);
        o.method("send", &ZActor::send);
        o.method("recv", &ZActor::recv);
        o.method("send_string", &ZActor::send_string);
        o.method("recv_string", &ZActor::recv_string);
        o.method("send_picture", &ZActor::send_picture);
        o.method("recv_picture", &ZActor::recv_picture);
        return o;
    }

};
