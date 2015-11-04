#pragma once

#include "../common.h"

class ZCertStore : public ZHandle {
public:
    ZCertStore() : ZHandle();
    ZCertStore(zcertstore_t *handle, bool owned) : ZHandle(handle, owned, "zcertstore") {}
    zcertstore_t *zcertstore_handle() const { return (zcertstore_t *) get_handle(); }

    void __construct(Php::Parameters &param);

    Php::Value lookup (Php::Parameters &param);

    void insert(Php::Parameters &param);

    void dump();

};
