#pragma once

#include "zactor.h"

class ZPoller : public ZActor {
private:
    bool _verbose = false;
    bool _stopped = false;

    std::map<void *, Php::Object> pollers;
    Php::Value socket_callback = NULL;
    Php::Value idle_callback = NULL;

    void _add(Php::Value p);
    void _remove(Php::Value p);
public:
    ZPoller() : ZActor() {}
    zpoller_t *zpoller_handle() const { return (zpoller_t *) get_handle(); }

    void __construct(Php::Parameters &param);
    void set_verbose(Php::Parameters &param);
    void on_idle(Php::Parameters &param);
    void add(Php::Parameters &param);
    void remove(Php::Parameters &param);
    void start(Php::Parameters &param);
    void stop();

    Php::Value expired();
    Php::Value terminated();

    static Php::Class<ZPoller> php_register() {

        Php::Class<ZPoller> o("ZPoller");

        o.method("__construct", &ZPoller::__construct);
        o.method("set_verbose", &ZPoller::set_verbose);
        o.method("on_idle", &ZPoller::on_idle);
        o.method("add", &ZPoller::add);
        o.method("remove", &ZPoller::remove);
        o.method("start", &ZPoller::start);
        o.method("stop", &ZPoller::stop);

        return o;
   }

};