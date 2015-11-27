#pragma once

#include "../common.h"

class ZFrame  : public ZHandle, public Php::Base  {
public:
    ZFrame() : ZHandle(), Php::Base() {}
    ZFrame(zframe_t *handle, bool owned) : ZHandle(handle, owned, "zframe"), Php::Base() {}
    zframe_t *zframe_handle() const { return (zframe_t *) get_handle(); }

    void __construct(Php::Parameters &param) {
        if(param.size() > 0)
            set_handle(zframe_new(param[0].rawValue(), param[0].size()), true, "zframe");
        else
    	    set_handle(zframe_new(NULL, 0), true, "zframe");
    }

    Php::Value __toString() {
        Php::Value result = "";
        char *frame = zframe_strdup(zframe_handle());
        if(frame) {
            result = frame;
            zstr_free(&frame);
        }
        return result;
    }

    void dump() {
    	zframe_print(zframe_handle(), NULL);
    }

    void pack(Php::Parameters &params) {
        Php::Value _packed = Php::call("call_user_func_array", "pack", params);
        if(_packed.size() > 0)
            zframe_reset(zframe_handle(), _packed.rawValue(), _packed.size());
        else
            zframe_reset(zframe_handle(), NULL, 0);
    }

    Php::Value unpack(Php::Parameters &param) {
        return Php::call("unpack", param[0], this);
    }

    static Php::Class<ZFrame> php_register() {
        Php::Class<ZFrame> o("ZFrame");
        o.method("__construct", &ZFrame::__construct);
        o.method("dump", &ZFrame::dump);
        o.method("pack", &ZFrame::pack,{
            Php::ByVal("format", Php::Type::String, true)
        });
        o.method("unpack", &ZFrame::unpack,{
            Php::ByVal("format", Php::Type::String, true)
        });
        return o;
    }

};
