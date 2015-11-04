#pragma once

#include "../common.h"

class ZChunk  : public ZHandle {
public:
    ZChunk() : ZHandle() {}
    ZChunk(zchunk_t *handle, bool owned) : ZHandle(handle, owned, "zchunk") {}
    zchunk_t *zchunk_handle() const { return (zchunk_t *) get_handle(); }

    void __construct(Php::Parameters &param) {
    	zchunk_t *chunk = zchunk_new(NULL,0);
    	if(chunk)
    		set_handle(chunk, true, "zchunk");
    	else
    		throw Php::Exception("Can't create ZChunk");
    }

    void dump() {
    	zchunk_print(zchunk_handle());
    }

    static Php::Class<ZChunk> php_register() {
        Php::Class<ZChunk> o("ZChunk");
        o.method("__construct", &ZChunk::__construct);
        o.method("dump", &ZChunk::dump);
        return o;
    }

};
