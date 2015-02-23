#pragma once

#include "../czmq/zactor.h"
#include "zmdp_common.h"
#include "zmdp_broker.h"

class MajordomoBroker : public ZActor {
private:
    bool _stopped = false;
    bool _verbose = false;
    Php::Value on_idle_callback;
    Php::Value on_tick_callback;
public:
    MajordomoBroker() : ZActor() {}
    zactor_t *zmdpbroker_handle() const { return (zactor_t *) get_handle(); }

    void __construct(Php::Parameters &param);

	Php::Value bind(Php::Parameters &param);

    void pause();

    void resume();

    void stop();

    void on_idle(Php::Parameters &param);

    void on_tick(Php::Parameters &param);

    void set_verbose(Php::Parameters &param);

    void set_capture(Php::Parameters &param);

    Php::Value get_status();

    void run(Php::Parameters &param);

     static Php::Class<MajordomoBroker> php_register() {
        Php::Class<MajordomoBroker> o("Broker");
        o.method("__construct", &MajordomoBroker::__construct);
        o.method("bind", &MajordomoBroker::bind);
        o.method("set_verbose", &MajordomoBroker::set_verbose);
        o.method("pause", &MajordomoBroker::pause);
        o.method("resume", &MajordomoBroker::resume);
        o.method("run", &MajordomoBroker::run);
        o.method("stop", &MajordomoBroker::stop);
        o.method("on_idle", &MajordomoBroker::on_idle);
        o.method("on_tick", &MajordomoBroker::on_tick);
        o.method("get_status", &MajordomoBroker::get_status);
        o.method("set_capture", &MajordomoBroker::set_capture, {
            Php::ByVal("socket_endpoint", Php::Type::String, true)
        });
        return o;
    }
};