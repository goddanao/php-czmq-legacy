#pragma once

#include <phpcpp.h>
#include <iostream>
#include <czmq.h>
#include "zpoll.h"
#include "zhandle.h"

class ZReactor : public Php::Base {
private:
    bool _verbose       = false;
    bool _dispatching   = false;

    Php::Object _poller; // will hold ZPollerEx _poller;
    std::map<ZHandle *, Php::Value> _objects;
    std::map<ZHandle *, Php::Value> _callbacks;
    std::vector<ZHandle *> _objectsRemoveLater;

    void flush_remove_later();

    void _remove(ZHandle *to_remove);

public:

    void __construct(Php::Parameters &param);

    void set_verbose(Php::Parameters &param);

    void add(Php::Parameters &param);

    Php::Value has(Php::Parameters &param);

    void remove(Php::Parameters &param);

    void check_for(Php::Parameters &param);

    Php::Value events(Php::Parameters &param);

    Php::Value poll(Php::Parameters &param);

    Php::Value has_input(Php::Parameters &param);

    Php::Value has_output(Php::Parameters &param);

    Php::Value has_error(Php::Parameters &param);

    static Php::Class<ZReactor> php_register() {
        Php::Class<ZReactor> o("ZReactor");

        o.method("__construct", &ZReactor::__construct);
        o.method("set_verbose", &ZReactor::set_verbose);
        o.method("add", &ZReactor::add);
        o.method("has", &ZReactor::has);
        o.method("remove", &ZReactor::remove);
        o.method("check_for", &ZReactor::check_for);
        o.method("events", &ZReactor::events);
        o.method("poll", &ZReactor::poll);
        o.method("has_input", &ZReactor::has_input);
        o.method("has_output", &ZReactor::has_output);
        o.method("has_error", &ZReactor::has_error);

        return o;
    }

};