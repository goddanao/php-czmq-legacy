#pragma once

#include "zhandle.h"
#include "zhash.h"
#include "zchunk.h"
#include "zframe.h"

class ZMsg  : public ZHandle {
public:
    ZMsg() : ZHandle() {}
    ZMsg(zmsg_t *handle, bool owned) : ZHandle(handle, owned, "zmsg") {}
    zmsg_t *zmsg_handle() const { return (zmsg_t *) get_handle(); }

    void __construct(Php::Parameters &param);

    Php::Value append(Php::Parameters &param);          // ZFrame
    Php::Value prepend(Php::Parameters &param);         // ZFrame
    Php::Value pop();                                   // ZFrame

    void append_picture(Php::Parameters &param);  // Picture Format
    void prepend_picture(Php::Parameters &param); // Picture Format
    Php::Value pop_picture(Php::Parameters &param);     // Picture Format

    Php::Value append_string(Php::Parameters &param);   // String
    Php::Value prepend_string(Php::Parameters &param);  // String
    Php::Value pop_string();      // String

    Php::Value send(Php::Parameters &param);
    Php::Value recv(Php::Parameters &param);

    void remove(Php::Parameters &param);
    Php::Value first();
    Php::Value next();
    Php::Value last();

    Php::Value get_size();
    Php::Value get_content_size();

    void dump();


    static Php::Class<ZMsg> php_register() {
        Php::Class<ZMsg> o("ZMsg");
        o.method("__construct", &ZMsg::__construct);

        o.method("append_picture", &ZMsg::append_picture);
        o.method("prepend_picture", &ZMsg::prepend_picture);
        o.method("pop_picture", &ZMsg::pop_picture);

        o.method("append", &ZMsg::append);
        o.method("prepend", &ZMsg::prepend);
        o.method("pop", &ZMsg::pop);

        o.method("append_string", &ZMsg::append_string);
        o.method("prepend_string", &ZMsg::prepend_string);
        o.method("pop_string", &ZMsg::pop_string);

        o.method("send", &ZMsg::send);
        o.method("recv", &ZMsg::recv);

        o.method("remove", &ZMsg::remove);
        o.method("first", &ZMsg::first);
        o.method("next", &ZMsg::next);
        o.method("last", &ZMsg::last);

        o.method("get_size", &ZMsg::get_size);
        o.method("get_content_size", &ZMsg::get_content_size);

        o.method("dump", &ZMsg::dump);
        return o;
    }

};
