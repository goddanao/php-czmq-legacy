#pragma once

#include "../common.h"

class ZPoller : public ZHandle {
private:
    bool _verbose = false;
    bool _stopped = false;

    Php::Value idle_callback;

    std::map<void *, Php::Object> pollers;

    void _add(Php::Value p);
    void _remove(Php::Value p);
public:
    ZPoller() : ZHandle() {}
    ZPoller(zpoller_t *handle, bool owned) : ZHandle(handle, owned, "zpoller") {}
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
        o.method("on_idle", &ZPoller::on_idle, {
            Php::ByVal("callback", Php::Type::Callable, true)
        });
        o.method("add", &ZPoller::add);
        o.method("remove", &ZPoller::remove);
        o.method("start", &ZPoller::start);
        o.method("stop", &ZPoller::stop);
        o.method("expired", &ZPoller::expired);
        o.method("terminated", &ZPoller::terminated);

        return o;
   }

};