#pragma once

#include "../common.h"

class ZContext   : public ZHandle, public Php::Base  {
public:
    ZContext() : ZHandle(), Php::Base() {}
    ZContext(void *handle, bool owned) : ZHandle(handle, owned, "zcontext"), Php::Base() {}
    void *zcontext_handle() const { return get_handle(); }

    static Php::Value is_interrupted() { return zctx_interrupted; }

    static Php::Class<ZContext> php_register() {
        Php::Class<ZContext> o("ZContext");
        o.method("is_interrupted", &ZContext::is_interrupted);
        return o;
    }

};