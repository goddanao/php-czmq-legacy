#pragma once

#include "../common.h"

class ZPoller : public ZHandle {
private:
    bool _verbose = false;
    bool _stopped = false;

    Php::Value idle_callback;

    std::map<void *, Php::Object> pollers;

    void _add(Php::Value p) {
        if(p.isObject()) {
            ZHandle *zhandle = dynamic_cast<ZHandle *>(p.implementation());
            if(zhandle != NULL) {
                zpoller_add(zpoller_handle(), zhandle->get_socket());
                std::pair<void *, Php::Value> el = {zhandle->get_socket(), p};
                pollers.insert(el);
            } else {
                throw Php::Exception("ZPoller add need a ZHandle");
            }
        }
    }

    void _remove(Php::Value p) {
        if(p.isObject()) {
            ZHandle *zhandle = dynamic_cast<ZHandle*>(p.implementation());
            if(zhandle != NULL) {
                zpoller_remove(zpoller_handle(), zhandle->get_socket());
                pollers.erase(zhandle->get_handle());
            } else {
                throw Php::Exception("ZPoller remove need a ZHandle");
            }
        }
    }

public:
    ZPoller() : ZHandle() {}
    ZPoller(zpoller_t *handle, bool owned) : ZHandle(handle, owned, "zpoller") {}
    zpoller_t *zpoller_handle() const { return (zpoller_t *) get_handle(); }


    void __construct(Php::Parameters &param) {
        zpoller_t *poller = zpoller_new(NULL);
        if(poller) {
            set_handle(poller, true, "zpoller");
            if(param.size() >= 0)
                add(param);
        } else
            throw Php::Exception("Can't create ZPoller");
    }

    void set_verbose(Php::Parameters &param) {
        _verbose = param.size() > 0 ? param[0].boolValue() : true;
    }

    void add(Php::Parameters &param) {
        for (auto &p : param) {
            if(p.isArray()) {
                for (auto &pvalue : p)
                    _add(pvalue.second);
            } else {
                _add(p);
            }
        }
    }

    void remove(Php::Parameters &param) {
        for (auto &p : param) {
            if(p.isArray()) {
                for (auto &pvalue : p)
                    _remove(pvalue.second);
            } else {
                _remove(p);
            }
        }
    }

    void stop() {
        _stopped = true;
    }

    void start(Php::Parameters &param) {

        _stopped = false;

        bool _socket_callable = (param.size() > 0 && param[0].isCallable());
        bool _idle_callable = idle_callback.isCallable();

        while(!_stopped) {
            void *socket = zpoller_wait(zpoller_handle(), 1000);
            if(zpoller_terminated(zpoller_handle()))
                break;
            else
            if(zpoller_expired(zpoller_handle()) && _idle_callable) {
                idle_callback(this);
            }
            else
            if(socket && _socket_callable) {
                param[0](pollers[socket], this);
            }
        }

    }

    void on_idle(Php::Parameters &param) {
        if(param.size() > 0 && param[0].isCallable()) {
            idle_callback = param[0];
        }
        else {
            idle_callback = NULL;
        }
    }

    Php::Value expired() {
        return zpoller_expired(zpoller_handle());
    }

    Php::Value terminated() {
        return zpoller_terminated(zpoller_handle());
    }

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