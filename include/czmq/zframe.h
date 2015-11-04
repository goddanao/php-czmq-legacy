#pragma once

#include "../common.h"

class ZFrame  : public ZHandle {
public:
    ZFrame() : ZHandle() {}
    ZFrame(zframe_t *handle, bool owned) : ZHandle(handle, owned, "zframe") {}
    zframe_t *zframe_handle() const { return (zframe_t *) get_handle(); }

    void __construct(Php::Parameters &param) {
    	set_handle(zframe_new(NULL, 0), true, "zframe");
    }

    Php::Value __toString() {
        char *frame = zframe_strdup (zframe_handle());
    	Php::Value buffer = frame;
    	free(frame);
    	return buffer.stringValue();
    }

    void dump() {
    	zframe_print(zframe_handle(), NULL);
    }

    static Php::Class<ZFrame> php_register() {
        Php::Class<ZFrame> o("ZFrame");
        o.method("__construct", &ZFrame::__construct);
        o.method("dump", &ZFrame::dump);
        return o;
    }

};
