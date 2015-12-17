#pragma once

#include "../common.h"

class MalamuteBroker : public ZActor, public Php::Base {
private:

    static void *new_actor(Php::Parameters &param, zpoller_t *poller) {
        zactor_t *broker = zactor_new(mlm_server, NULL);
        if(broker) {

            // Options
            if(param.size() > 1 && param[1].isArray() && param[1].size() > 0) {
                zconfig_t * config;
                config = ZUtils::phparray_to_zconfig(param[1], "mlm_broker");
               if(config) {
                    std::string fname = "/tmp/" + ZUtils::uuid() + ".cfg";
                    zconfig_save(config, fname.c_str());
                    zconfig_destroy(&config);
                    zstr_sendx (broker, "LOAD", fname.c_str(), NULL);
                }
            }

            if(param.size() > 0 && param[0].stringValue() != "") {
                zstr_sendx (broker, "BIND", param[0].stringValue().c_str(), NULL);
                zclock_sleep(200);
            }

            if(poller)
                zpoller_add(poller, broker);

            return broker;
        }
        return nullptr;
    }

public:

    MalamuteBroker() : ZActor("mlm_broker", &MalamuteBroker::new_actor), Php::Base() { }
    zactor_t *mlm_broker_handle() const { return (zactor_t *) get_handle(); }

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
			zstr_free(&command);
			zstr_free(&port_str);
			return result;
		}

		return true;
	}

	static void run(Php::Parameters &param) {
        _run(param, &MalamuteBroker::new_actor);
    }

    static Php::Class<MalamuteBroker> php_register() {
        Php::Class<MalamuteBroker> o("Broker");
        o.method("__construct", &MalamuteBroker::__construct, {
            Php::ByVal("endpoint", Php::Type::String, true),
            Php::ByVal("options", Php::Type::Array, false)
        });

        o.method("bind", &MalamuteBroker::bind, {
          Php::ByVal("endpoint", Php::Type::String, true)
        });

        o.method("run", &MalamuteBroker::run, {
          Php::ByVal("endpoint", Php::Type::String, true),
          Php::ByVal("options", Php::Type::Array, false)
        });

        // load / save /set config
        ZHandle::register_config((Php::Class<MalamuteBroker> *) &o);

        // ZEmitter
        o.method("start", &MalamuteBroker::start);
        ZHandle::register_izemitter((Php::Class<MalamuteBroker> *) &o);

        // Send / Recv
        ZHandle::register_recv((Php::Class<MalamuteBroker> *) &o);
        ZHandle::register_send((Php::Class<MalamuteBroker> *) &o);

        // IZSocket intf support
        ZHandle::register_izsocket((Php::Class<MalamuteBroker> *) &o);

        return o;
    }

};
