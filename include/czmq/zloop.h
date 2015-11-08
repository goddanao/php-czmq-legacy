#pragma once

#include "../common.h"
#include "zsocket.h"

class ZLoop : public ZHandle, public Php::Base  {
private:
    bool _verbose;
    zlistx_t *_callbacks = nullptr;

    static int cb_loop_stop(zloop_t *loop, int timer_id, void *arg) {
        return -1;
    }

    static int cb_timer(zloop_t *loop, int timer_id, void *arg) {
        Php::Value *cb = (Php::Value *) arg;
        Php::Object zloop("ZLoop", new ZLoop(loop, false));
        (*cb)(timer_id, zloop);
        return 0;
    }

    static int cb_socket(zloop_t *loop, zsock_t *reader, void *arg) {
        Php::Value *cb = (Php::Value *) arg;
        Php::Object zloop("ZLoop", new ZLoop(loop, false));
        Php::Object socket("ZSocket", new ZSocket(reader, false));
        (*cb)(socket, zloop);
        return 0;
    }

    static void s_callbacks_destroy(Php::Value **cb_p) {
         Php::Value *cb = *cb_p;
         delete cb;
    }

public:

    ZLoop() : ZHandle(), Php::Base() {}
    ZLoop(zloop_t *handle, bool owned) : ZHandle(handle, owned, "zloop"), Php::Base() {}
    zloop_t *zloop_handle() const { return (zloop_t *) get_handle(); }

    void __construct(Php::Parameters &param) {
        _callbacks = zlistx_new();
        zlistx_set_destructor (_callbacks, (czmq_destructor *) s_callbacks_destroy);
        set_handle(zloop_new (), true, "zloop");
    }

    void __destruct() {
        if(_callbacks)
            zlistx_destroy(&_callbacks);
    }

    void set_verbose(Php::Parameters &param) {
        zloop_set_verbose(zloop_handle(), param.size() > 0 ? param[0].boolValue() : false);
    }

    void set_max_timers(Php::Parameters &param) {
        if(param.size() > 0)
            zloop_set_max_timers(zloop_handle(), param[0].numericValue());
    }

    void start() {
        zloop_start(zloop_handle());
    }

    void stop() {
        zloop_timer (zloop_handle(), 1, 1, cb_loop_stop, nullptr);
    }

    void ignore_interrupts() {
        zloop_ignore_interrupts(zloop_handle());
    }

    Php::Value add_timer(Php::Parameters &param) {
        bool valid = (param.size() >= 2 && param[0].isNumeric() && param[1].isCallable());
        if(valid) {
            Php::Value *cb = new Php::Value(param[1]);
            zlistx_add_end(_callbacks, cb);
            return zloop_timer (zloop_handle(), param[0].numericValue(), (param.size() > 2 ? param[2].numericValue() : 1), cb_timer, cb);
        }
        throw Php::Exception("ZLoop add_timer require a delay and a callback.");
    }

    void remove_timer(Php::Parameters &param) {
        zloop_timer_end(zloop_handle(), param[0].numericValue());
    }

    void add(Php::Parameters &param) {
        bool valid = (param.size() >= 2 && param[0].isObject() && param[1].isCallable());
        if(valid) {
            ZHandle  *zh = dynamic_cast<ZHandle *> (param[0].implementation());
            if(zh) {
                zsock_t *socket = (zsock_t*)zh->get_socket();
                if(socket) {
                    Php::Value *cb = new Php::Value(param[1]);
                    zlistx_add_end(_callbacks, cb);
                    zloop_reader (zloop_handle(), socket, cb_socket, cb);
                    if(param.size() > 2 && param[2].boolValue())
                        zloop_reader_set_tolerant(zloop_handle(), socket);
                    return;
                }
             }
        }
        throw Php::Exception("ZLoop add require a ZActor or ZSocket and a callback.");
    }

    void remove(Php::Parameters &param) {
        bool valid = (param.size() == 1 && param[0].isObject());
        if(valid) {
            ZHandle  *zh = dynamic_cast<ZHandle *> (param[0].implementation());
            if(zh) {
                zsock_t *socket = (zsock_t*)zh->get_socket();
                if(socket) {
                    zloop_reader_end (zloop_handle(), socket);
                    return;
                }
             }
        }
        throw Php::Exception("ZLoop remove require a ZActor or ZSocket.");
    }

    static Php::Class<ZLoop> php_register() {
        Php::Class<ZLoop> o("ZLoop");

        o.method("__construct", &ZLoop::__construct);
        o.method("set_verbose", &ZLoop::set_verbose);
        o.method("set_max_timers", &ZLoop::set_max_timers);
        o.method("start", &ZLoop::start);
        o.method("stop", &ZLoop::stop);
        o.method("add", &ZLoop::add);
        o.method("remove", &ZLoop::remove);
        o.method("add_timer", &ZLoop::add_timer);
        o.method("remove_timer", &ZLoop::remove_timer, {
            Php::ByVal("timer_id", Php::Type::Numeric, true)
        });
        o.method("ignore_interrupts", &ZLoop::ignore_interrupts);

        return o;
    }

};
