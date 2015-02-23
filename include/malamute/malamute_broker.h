#pragma once

#include "../czmq/zactor.h"

class MalamuteBroker : public ZActor {
    bool verbose = false;
    bool stopped = false;
    zactor_t *broker = NULL;
    Php::Value on_idle_callback;
    Php::Value on_tick_callback;
public:
    MalamuteBroker() : ZActor() {}
    zactor_t *mlm_broker_handle() const { return (zactor_t *) get_handle(); }

    void __construct(Php::Parameters &param);

    void set_verbose(Php::Parameters &param);

    Php::Value bind(Php::Parameters &param);

    void on_idle(Php::Parameters &param);

    void on_tick(Php::Parameters &param);

    void load_config(Php::Parameters &param);

    void set_config(Php::Parameters &param);

    void save_config(Php::Parameters &param);

    void run(Php::Parameters &param);

    void stop();

    Php::Value get_status();

    static Php::Class<MalamuteBroker> php_register() {
        Php::Class<MalamuteBroker> o("Broker");
        o.method("__construct", &MalamuteBroker::__construct);
        o.method("set_verbose", &MalamuteBroker::set_verbose);
        o.method("load_config", &MalamuteBroker::load_config);
        o.method("set_config", &MalamuteBroker::set_config);
        o.method("save_config", &MalamuteBroker::save_config);
        o.method("bind", &MalamuteBroker::bind);
        o.method("get_status", &MalamuteBroker::get_status);
        o.method("on_tick", &MalamuteBroker::on_tick);
        o.method("on_idle", &MalamuteBroker::on_idle);
        o.method("run", &MalamuteBroker::run);
        o.method("stop", &MalamuteBroker::stop);
        return o;
    }

};
