#pragma once

#include "../czmq/zactor.h"

class FmqBroker : public ZActor, public Php::Base {
    bool verbose = false;
    bool stopped = false;
    Php::Value on_idle_callback;
    Php::Value on_tick_callback;
public:
    FmqBroker() : ZActor(), Php::Base() {}
    zactor_t *fmq_broker_handle() const { return (zactor_t *) get_handle(); }


	void __construct(Php::Parameters &param) {
		void *args = (param.size() == 0) ? nullptr : (void *) param[0].stringValue().c_str();
		set_handle(zactor_new (fmq_server, args), true, "fmq_broker");
	}

	void set_verbose(Php::Parameters &param) {
		verbose = true;
		zstr_sendx (fmq_broker_handle(), "VERBOSE", NULL);
	}

	void load_config(Php::Parameters &param) {
		if(param.size() == 0)
			throw Php::Exception("Please specify a config file to load.");
		zstr_sendx (fmq_broker_handle(), "LOAD", param[0].stringValue().c_str(), NULL);
	}

	void set_config(Php::Parameters &param) {
		if(param.size() != 2)
			throw Php::Exception("Please specify a key and a value for config.");
		zstr_sendx (fmq_broker_handle(), "SET", param[0].stringValue().c_str(), param[1].stringValue().c_str(), NULL);
	}

	void save_config(Php::Parameters &param) {
		if(param.size() == 0)
			throw Php::Exception("Please specify a config file to save.");
		zstr_sendx (fmq_broker_handle(), "SAVE", param[0].stringValue().c_str(), NULL);
	}

	Php::Value bind(Php::Parameters &param) {
		if(param.size() == 0)
			throw Php::Exception("FileMq Broker can't bind endpoint.");

		zstr_sendx (fmq_broker_handle(), "BIND", param[0].stringValue().c_str(), NULL);

		char *command, *port_str;
		zstr_sendx (fmq_broker_handle(), "PORT", NULL);
		zstr_recvx (fmq_broker_handle(), &command, &port_str, NULL);
		if(streq(command, "PORT")) {
			Php::Value result = port_str;
			free(command);
			free(port_str);
			return result;
		}

		return true;
	}

	void on_idle(Php::Parameters &param) {
	   if(param.size()>0 && param[0].isCallable())
			on_idle_callback = param[0];
	}

	void on_tick(Php::Parameters &param) {
	   if(param.size()>0 && param[0].isCallable())
			on_tick_callback = param[0];
	}

	void stop() {
		stopped = true;
	}

	void run(Php::Parameters &param) {
		int64_t stop_after = -1;
		int64_t started = zclock_time();

		if(param.size()>0 && param[0].isNumeric())
			stop_after = param[0].numericValue();

		stopped = false;

		zpoller_t *poller = zpoller_new(fmq_broker_handle(), NULL);

		while(!zsys_interrupted && !stopped) {

			if(stop_after != -1 && ((zclock_time() - started) > stop_after))
				break;

			void *socket = zpoller_wait(poller, 1000);
			if(socket) {
				char *event, *data;
				int result = zstr_recvx (socket, &event, &data, NULL);
				if(result != -1) {
					zsys_info("fmqbroker: %s -> %s", event, data);




					zstr_free(&event);
					zstr_free(&data);
				}
			}
			else
			if(zpoller_expired(poller)) {
				if(on_tick_callback.isCallable())
					on_tick_callback(this);
				// zsys_info("mlmbroker: TICK");
	//            if(on_idle_callback.isCallable())
	//                on_idle_callback(this);
			}
			else
			if(zpoller_terminated(poller)) {
				break;
			}
		}

		zpoller_destroy(&poller);
	}

    static Php::Class<FmqBroker> php_register() {
        Php::Class<FmqBroker> o("Broker");
        o.method("__construct", &FmqBroker::__construct);
        o.method("set_verbose", &FmqBroker::set_verbose);
        o.method("load_config", &FmqBroker::load_config);
        o.method("set_config", &FmqBroker::set_config);
        o.method("save_config", &FmqBroker::save_config);
        o.method("bind", &FmqBroker::bind);
        o.method("on_tick", &FmqBroker::on_tick);
        o.method("on_idle", &FmqBroker::on_idle);
        o.method("run", &FmqBroker::run);
        o.method("stop", &FmqBroker::stop);
        return o;
    }

};
