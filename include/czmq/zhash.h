
#pragma once

#include <phpcpp.h>
#include <iostream>
#include <czmq.h>
#include "../common.h"

class ZHash  : public ZHandle {
public:
    ZHash() : ZHandle() {}
    ZHash(zhash_t *handle, bool owned) : ZHandle(handle, owned, "zhash") {}
    zhash_t *zhash_handle() const { return (zhash_t *) get_handle(); }

    void __construct(Php::Parameters &param) {
    	set_handle(zhash_new(), true, "zhash");
    }

    static Php::Class<ZHash> php_register() {
        Php::Class<ZHash> o("ZHash");
        o.method("__construct", &ZHash::__construct);
        return o;
    }
};
