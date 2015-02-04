#pragma once

#include "zhandle.h"

class ZLoop : public ZHandle {
private:
    bool _verbose;
public:
    ZLoop() : ZHandle() {}
    ZLoop(zloop_t *handle, bool owned) : ZHandle(handle, owned, "zloop") {}
    zloop_t *zloop_handle() const { return (zloop_t *) get_handle(); }

    void __construct(Php::Parameters &param);
    void set_verbose(Php::Parameters &param);

    static Php::Class<ZLoop> php_register() {
        Php::Class<ZLoop> o("ZLoop");
        o.method("__construct", &ZLoop::__construct);
        o.method("set_verbose", &ZLoop::set_verbose);
        return o;
    }

};
