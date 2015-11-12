#pragma once

#include "../czmq/zactor.h"

class MajordomoBroker : public ZActor, public Php::Base {
private:
    bool _stopped = false;
    bool _verbose = false;
    std::string _endpoint = "";
    Php::Value on_idle_callback;
    Php::Value on_tick_callback;

public:

    MajordomoBroker() : ZActor(), Php::Base() {}
    zactor_t *zmdpbroker_handle() const { return (zactor_t *) get_handle(); }

	void __construct(Php::Parameters &param) {
	    _endpoint = (param.size() > 0) ? param[0].stringValue() : "";
	    _verbose  = (param.size() > 1) ? param[1].boolValue() : false;
		zactor_t *broker = zactor_new(mdp_broker, NULL);
		if(broker) {
			set_handle(broker, true, "mdp_broker");
			if(_verbose)
			    zstr_sendx (broker, "VERBOSE", NULL);
			if(_endpoint != "")
			    zstr_sendx (broker, "BIND", _endpoint.c_str(), NULL);
        }
	}

    void set_verbose(Php::Parameters &param) {
		_verbose = true;
		zstr_sendx (zmdpbroker_handle(), "VERBOSE", NULL);
	}

    void load_config(Php::Parameters &param) {
		if(param.size() == 0)
			throw Php::Exception("Please specify a config file to load.");
		zstr_sendx (zmdpbroker_handle(), "LOAD", param[0].stringValue().c_str(), NULL);
	}

	void save_config(Php::Parameters &param) {
		if(param.size() == 0)
			throw Php::Exception("Please specify a config file to save.");
		zstr_sendx (zmdpbroker_handle(), "SAVE", param[0].stringValue().c_str(), NULL);
	}

	void set_config(Php::Parameters &param) {
        if(param.size() != 2)
            throw Php::Exception("Please specify a key and a value for config.");
        zstr_sendx (zmdpbroker_handle(), "SET", param[0].stringValue().c_str(), param[1].stringValue().c_str(), NULL);
    }

	Php::Value bind(Php::Parameters &param) {
		if(param.size() == 0)
			throw Php::Exception("Majordomo Broker can't bind endpoint.");
		zstr_sendx (zmdpbroker_handle(), "BIND", param[0].stringValue().c_str(), NULL);

		return true;
	}

//	Php::Value get_status() {
//
//		Php::Value result;
//
//		zstr_sendx(zmdpbroker_handle(), "STATUS", NULL);
//
//		zhash_t *services= NULL;
//		zhash_t *workers = NULL;
//		zlist_t *waiting = NULL;
//		zsock_recv(zmdpbroker_handle(), "ppp", &services, &workers, &waiting);
//
//		if(services != NULL)	{
//
//			zlist_t *keys = zhash_keys(services);
//			if(keys != NULL) {
//				char *item = (char *) zlist_first(keys);
//				int service_idx = 0;
//
//				while(item) {
//					service_t *svc = (service_t *) zhash_lookup(services, item);
//					if(svc != NULL) {
//						std::string idx = item;
//						result["services"][idx]["workers"] = (int) svc->workers;
//						result["services"][idx]["requests"] = (int) zlist_size(svc->requests);
//						result["services"][idx]["waiting"] = (int) zlist_size(svc->waiting);
//						result["services"][idx]["blacklist"] = (int) zlist_size(svc->blacklist);
//						service_idx++;
//					}
//					item = (char *) zlist_next(keys);
//				}
//				zlist_destroy(&keys);
//			}
//
//			return result;
//		}
//		else
//			return nullptr;
//	}

//	void on_idle(Php::Parameters &param) {
//		if(param.size()>0 && param[0].isCallable())
//			on_idle_callback = param[0];
//		else
//			on_idle_callback = nullptr;
//	}
//
//	void on_tick(Php::Parameters &param) {
//		if(param.size()>0 && param[0].isCallable())
//			on_tick_callback = param[0];
//		else
//			on_tick_callback = nullptr;
//	}

	void run(Php::Parameters &param) {
		_stopped = false;
		while(!_stopped) {
			char *event, *data;
			int result = zstr_recvx (zmdpbroker_handle(), &event, &data, NULL);
			if(result != -1) {
				zsys_info("broker %s -> %s", event, data);
				zstr_free(&event);
				zstr_free(&data);
			} else {
				break;
			}
		}
	}

     static Php::Class<MajordomoBroker> php_register() {
        Php::Class<MajordomoBroker> o("MajordomoBroker");
        o.method("__construct", &MajordomoBroker::__construct, {
            Php::ByVal("endpoint", Php::Type::String, false),
            Php::ByVal("verbose", Php::Type::Bool, false)
        });
        o.method("set_verbose", &MajordomoBroker::set_verbose);
        o.method("load_config", &MajordomoBroker::load_config);
        o.method("save_config", &MajordomoBroker::save_config);
        o.method("set_config", &MajordomoBroker::set_config);
        o.method("bind", &MajordomoBroker::bind);
        o.method("run", &MajordomoBroker::run);
//        o.method("set_capture", &MajordomoBroker::set_capture, {
//            Php::ByVal("socket_endpoint", Php::Type::String, true)
//        });
//        o.method("pause", &MajordomoBroker::pause);
//        o.method("resume", &MajordomoBroker::resume);
//        o.method("stop", &MajordomoBroker::stop);
//        o.method("on_idle", &MajordomoBroker::on_idle);
//        o.method("on_tick", &MajordomoBroker::on_tick);
//        o.method("get_status", &MajordomoBroker::get_status);

        return o;
    }
};