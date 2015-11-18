#pragma once

#include "../czmq/zactor.h"

class MalamuteBroker : public ZActor, public Php::Base {
    bool verbose = false;
public:
    MalamuteBroker() : ZActor(), Php::Base() {}
    zactor_t *mlm_broker_handle() const { return (zactor_t *) get_handle(); }

	void __construct(Php::Parameters &param) {
		void *args = (param.size() == 0) ? nullptr : (void *) param[0].stringValue().c_str();
		set_handle(zactor_new (mlm_server, args), true, "mlm_broker");
	}

	void set_verbose(Php::Parameters &param) {
		verbose = true;
		zstr_sendx (mlm_broker_handle(), "VERBOSE", NULL);
	}

	void load_config(Php::Parameters &param) {
		if(param.size() == 0)
			throw Php::Exception("Please specify a config file to load.");
		zstr_sendx (mlm_broker_handle(), "LOAD", param[0].stringValue().c_str(), NULL);
	}

	void set_config(Php::Parameters &param) {
		if(param.size() != 2)
			throw Php::Exception("Please specify a key and a value for config.");
		zstr_sendx (mlm_broker_handle(), "SET", param[0].stringValue().c_str(), param[1].stringValue().c_str(), NULL);
	}

	void save_config(Php::Parameters &param) {
		if(param.size() == 0)
			throw Php::Exception("Please specify a config file to save.");
		zstr_sendx (mlm_broker_handle(), "SAVE", param[0].stringValue().c_str(), NULL);
	}

	Php::Value bind(Php::Parameters &param) {
		if(param.size() == 0)
			throw Php::Exception("Malamute Broker can't bind endpoint.");

		zstr_sendx (mlm_broker_handle(), "BIND", param[0].stringValue().c_str(), NULL);

		char *command, *port_str;
		zstr_sendx (mlm_broker_handle(), "PORT", NULL);
		zstr_recvx (mlm_broker_handle(), &command, &port_str, NULL);
		if(streq(command, "PORT")) {
			Php::Value result = port_str;
			free(command);
			free(port_str);
			return result;
		}

		return true;
	}

	Php::Value get_status() {
	//
	//	Php::Value result;
	//
	//	zstr_sendx(mlm_broker_handle(), "STATUS", NULL);
	//	zsock_wait(mlm_broker_handle());
	//
	//    zhash_t *services= NULL;
	//    zhash_t *workers = NULL;
	//    zlist_t *waiting = NULL;
	//	zsock_recv(mlm_broker_handle(), "ppp", &services, &workers, &waiting);
	//	zsock_wait(mlm_broker_handle());
	//
	//	if(services != NULL)	{
	//
	//		zlist_t *keys = zhash_keys(services);
	//		if(keys != NULL) {
	//			char *item = (char *) zlist_first(keys);
	//			int service_idx = 0;
	//
	//			while(item) {
	//				service_t *svc = (service_t *) zhash_lookup(services, item);
	//				if(svc != NULL) {
	//					std::string idx = item;
	//					result["services"][idx]["workers"] = (int) svc->workers;
	//					result["services"][idx]["requests"] = (int) zlist_size(svc->requests);
	//					result["services"][idx]["waiting"] = (int) zlist_size(svc->waiting);
	//					result["services"][idx]["blacklist"] = (int) zlist_size(svc->blacklist);
	//					service_idx++;
	//				}
	//				item = (char *) zlist_next(keys);
	//			}
	//			zlist_destroy(&keys);
	//		}
	//
	//		return result;
	//	}
	//	else
			return nullptr;
	}


    static Php::Class<MalamuteBroker> php_register() {
        Php::Class<MalamuteBroker> o("Broker");
        o.method("__construct", &MalamuteBroker::__construct);
        o.method("set_verbose", &MalamuteBroker::set_verbose);
        o.method("load_config", &MalamuteBroker::load_config);
        o.method("set_config", &MalamuteBroker::set_config);
        o.method("save_config", &MalamuteBroker::save_config);
        o.method("bind", &MalamuteBroker::bind);
        o.method("get_status", &MalamuteBroker::get_status);

         // IZSocket intf support
        o.method("get_socket", &MalamuteBroker::_get_socket);
        o.method("get_fd", &MalamuteBroker::_get_fd);

        return o;
    }

};
