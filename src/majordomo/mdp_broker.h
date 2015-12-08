#pragma once

#include "../common.h"

class MajordomoBrokerV2 : public ZHandle, public Php::Base {
private:
    bool _stopped = false;
    std::string _endpoint = "";
public:

    MajordomoBrokerV2() : ZHandle(), Php::Base() {}
    zactor_t *zmdpbroker_handle() const { return (zactor_t *) get_handle(); }

	void __construct(Php::Parameters &param) {
	    _endpoint = (param.size() > 0) ? param[0].stringValue() : "";
	    bool _verbose  = (param.size() > 1) ? param[1].boolValue() : false;
		zactor_t *broker = zactor_new(mdp_broker, NULL);
		if(broker) {
			set_handle(broker, true, "mdp_broker_v2");
			if(_verbose)
			    zstr_sendx (broker, "VERBOSE", NULL);
			if(_endpoint != "")
			    zstr_sendx (broker, "BIND", _endpoint.c_str(), NULL);
        }
	}

    void set_verbose(Php::Parameters &param) {
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

	void run(Php::Parameters &param) {
        zpoller_t *poller = zpoller_new(zmdpbroker_handle());
        while (!zsys_interrupted) {
            void *socket = zpoller_wait(poller, 1000);
            if(zpoller_terminated(poller)) {
                zpoller_destroy(&poller);
                break;
            }
        }
        zpoller_destroy(&poller);
    }

    static Php::Class<MajordomoBrokerV2> php_register() {
        Php::Class<MajordomoBrokerV2> o("Broker");
        o.method("__construct", &MajordomoBrokerV2::__construct, {
            Php::ByVal("endpoint", Php::Type::String, false),
            Php::ByVal("verbose", Php::Type::Bool, false)
        });
        o.method("set_verbose", &MajordomoBrokerV2::set_verbose);
        o.method("run", &MajordomoBrokerV2::run);
        o.method("bind", &MajordomoBrokerV2::bind, {
          Php::ByVal("endpoint", Php::Type::String, true)
        });
        o.method("load_config", &MajordomoBrokerV2::load_config, {
            Php::ByVal("filename", Php::Type::String, true)
        });
        o.method("save_config", &MajordomoBrokerV2::save_config, {
            Php::ByVal("filename", Php::Type::String, true)
        });
        o.method("set_config", &MajordomoBrokerV2::set_config, {
            Php::ByVal("key", Php::Type::String, true),
            Php::ByVal("value", Php::Type::String, true)
        });

		// IZSocket intf support
        o.method("get_fd", &MajordomoBrokerV2::get_fd);
        o.method("get_socket", &MajordomoBrokerV2::_get_socket);


        return o;
    }
};