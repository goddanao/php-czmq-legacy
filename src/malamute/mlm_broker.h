#pragma once

#include "../czmq/zactor.h"

class MalamuteBroker : public ZActor, public Php::Base {
public:
    MalamuteBroker() : ZActor(), Php::Base() {}
    zactor_t *mlm_broker_handle() const { return (zactor_t *) get_handle(); }

	void __construct(Php::Parameters &param) {
		set_handle(zactor_new (mlm_server, NULL), true, "mlm_broker");
		if(param.size() > 0 && param[0].boolValue())
		    zstr_sendx (mlm_broker_handle(), "VERBOSE", NULL);
	}

	void set_verbose(Php::Parameters &param) {
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

    static Php::Class<MalamuteBroker> php_register() {
        Php::Class<MalamuteBroker> o("Broker");
        o.method("__construct", &MalamuteBroker::__construct);
        o.method("set_verbose", &MalamuteBroker::set_verbose);
        o.method("bind", &MalamuteBroker::bind);
        o.method("load_config", &MalamuteBroker::load_config);
        o.method("save_config", &MalamuteBroker::save_config);
        o.method("set_config", &MalamuteBroker::set_config);

         // IZSocket intf support
        o.method("get_socket", &MalamuteBroker::_get_socket);
        o.method("get_fd", &MalamuteBroker::_get_fd);
        return o;
    }

};
