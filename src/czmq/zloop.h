#pragma once

#include "zsocket.h"

class ZLoop : public ZHandle, public ZEmitter, public Php::Base  {
private:
    zlistx_t *_callbacks = nullptr;

    typedef struct {
        Php::Value *cb;
        Php::Value *obj;
    } _cbdata;

    static int cb_loop_stop(zloop_t *loop, int timer_id, void *arg) {
        return -1;
    }

    static int cb_timer(zloop_t *loop, int timer_id, void *arg) {
        _cbdata *data = (_cbdata *) arg;
        (*data->cb)(timer_id, Php::Object("ZLoop", new ZLoop(loop, false)));
        return 0;
    }

    static int cb_events(zloop_t *loop, zmq_pollitem_t *item, void *arg) {
        _cbdata *data = (_cbdata *) arg;
        (*data->cb)(*data->obj, item->revents, Php::Object("ZLoop", new ZLoop(loop, false)));
        return 0;
    }

    static int cb_socket(zloop_t *loop, zsock_t *reader, void *arg) {
        _cbdata *data = (_cbdata *) arg;
        (*data->cb)(*data->obj, Php::Object ("ZLoop", new ZLoop(loop, false)));
        return 0;
    }

    static void s_callbacks_destroy(_cbdata **cb_p) {
        _cbdata *data = (*cb_p);
        if(data->obj != nullptr)
            delete (Php::Value *) data->obj;
        if(data->cb != nullptr)
            delete (Php::Value *) data->cb;
        delete data;
    }

public:

    ZLoop() : ZHandle(), ZEmitter(), Php::Base() { _callbacks = zlistx_new(); }
    ZLoop(zloop_t *handle, bool owned) : ZHandle(handle, owned, "zloop"), ZEmitter(), Php::Base() { _callbacks = zlistx_new(); }
    zloop_t *zloop_handle() const { return (zloop_t *) get_handle(); }

    void __construct(Php::Parameters &param) {
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

    #if (CZMQ_VERSION <= CZMQ_MAKE_VERSION(3,0,2))
        void ignore_interrupts() {
            zloop_ignore_interrupts(zloop_handle());
        }
    #endif


    Php::Value add_timer(Php::Parameters &param) {
        bool valid = (param.size() >= 2 && param[0].isNumeric() && param[1].isCallable());
        if(valid) {
            _cbdata *data = new _cbdata();
            data->obj = nullptr;
            data->cb  = new Php::Value(param[1]);
            zlistx_add_end(_callbacks, data);
            return zloop_timer (zloop_handle(), param[0].numericValue(), (param.size() > 2 ? param[2].numericValue() : 1), cb_timer, data);
        }
        throw Php::Exception("ZLoop add_timer require a delay and a callback.");
    }

    void remove_timer(Php::Parameters &param) {
        zloop_timer_end(zloop_handle(), param[0].numericValue());
    }

    Php::Value add(Php::Parameters &param) {

        // Register callback data
        _cbdata *data = new _cbdata();
        data->obj  = new Php::Value(param[0]);
        data->cb   = new Php::Value(param[1]);
        zlistx_add_end(_callbacks, data);

        short event = (param.size() > 2) ? (short) param[2].numericValue() : ZMQ_POLLIN;
        zmq_pollitem_t item = ZUtils::phpvalue_to_pollitem(param[0], event);
        if(item.socket == nullptr && item.fd == INVALID_SOCKET)
            throw Php::Exception("Cannot create PollItem.");

        zloop_poller(zloop_handle(), &item, cb_events, data);

        if(param.size() > 3 && param[3].boolValue())
            zloop_poller_set_tolerant(zloop_handle(), &item);

        return true;
    }

    void remove(Php::Parameters &param) {
        zmq_pollitem_t item = ZUtils::phpvalue_to_pollitem(param[0]);
        if(item.socket == nullptr && item.fd == INVALID_SOCKET)
            throw Php::Exception("Cannot remove PollItem.");
        zloop_poller_end(zloop_handle(), &item);
    }

    static Php::Class<ZLoop> php_register() {
        Php::Class<ZLoop> o("ZLoop");

        o.method("__construct", &ZLoop::__construct);
        o.method("set_verbose", &ZLoop::set_verbose);
        o.method("set_max_timers", &ZLoop::set_max_timers, {
            Php::ByVal("max_timers", Php::Type::Numeric, true)
        });
        o.method("start", &ZLoop::start);
        o.method("stop", &ZLoop::stop);
        o.method("add", &ZLoop::add, {
            Php::ByVal("pollitem", Php::Type::String, true),
            Php::ByVal("callback", Php::Type::Callable, true),
            Php::ByVal("mode", Php::Type::Numeric, false)
        });
        o.method("remove", &ZLoop::remove, {
            Php::ByVal("pollitem", Php::Type::String, true)
        });
        o.method("add_timer", &ZLoop::add_timer, {
           Php::ByVal("timeout", Php::Type::Numeric, true),
           Php::ByVal("callback", Php::Type::Callable, true),
           Php::ByVal("repeat", Php::Type::Numeric, false)
       });
        o.method("remove_timer", &ZLoop::remove_timer, {
            Php::ByVal("timer_id", Php::Type::Numeric, true)
        });

        #if (CZMQ_VERSION <= CZMQ_MAKE_VERSION(3,0,2))
            o.method("ignore_interrupts", &ZLoop::ignore_interrupts);
        #endif

        return o;
    }

};
