#pragma once

#include "../common.h"

class ZFrame  : public ZHandle {
public:
    ZFrame() : ZHandle() {}
    ZFrame(zframe_t *handle, bool owned) : ZHandle(handle, owned, "zframe") {}
    zframe_t *zframe_handle() const { return (zframe_t *) get_handle(); }

    void __construct(Php::Parameters &param);

    Php::Value __toString();

    void dump();

    static Php::Class<ZFrame> php_register() {
        Php::Class<ZFrame> o("ZFrame");
        o.method("__construct", &ZFrame::__construct);
        o.method("dump", &ZFrame::dump);
        return o;
    }

};
