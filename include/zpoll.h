#pragma once

#include <phpcpp.h>
#include <iostream>
#include <czmq.h>
#include "zhandle.h"

class ZPoll : public Php::Base {
private:
    bool _verbose = false;
    std::vector<zmq_pollitem_t> _items;
    std::map<void *, size_t> _index;
    std::map<int, size_t> _fdindex;
    std::map<void *, Php::Value> _objects;

    void reindex(size_t const index);

public:

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

    static Php::Class<ZPoll> php_register() {

        Php::Class<ZPoll> o("ZPoll");

        o.method("set_verbose", &ZPoll::set_verbose);
        o.method("add", &ZPoll::add);
        o.method("has", &ZPoll::has);
        o.method("remove", &ZPoll::remove);
        o.method("check_for", &ZPoll::check_for);
        o.method("events", &ZPoll::events);
        o.method("poll", &ZPoll::poll);
        o.method("has_input", &ZPoll::has_input);
        o.method("has_output", &ZPoll::has_output);
        o.method("has_error", &ZPoll::has_error);

        return o;

    }


};