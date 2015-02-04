#pragma once

#include "zhandle.h"

class ZChunk : public ZHandle {
public:
    ZChunk() : ZHandle() {}
    ZChunk(zchunk_t *handle, bool owned) : ZHandle(handle, owned, "zchunk") {}
    zchunk_t *zchunk_handle() const { return (zchunk_t *) get_handle(); }

    void __construct(Php::Parameters &param);

    void dump();

    static Php::Class<ZChunk> php_register();

};
