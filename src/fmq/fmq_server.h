#pragma once

#include "../common.h"

class FileMqServer : public ZHandle, public Php::Base {
public:
    FileMqServer() : ZHandle(), Php::Base() {}
    zactor_t *fmq_broker_handle() const { return (zactor_t *) get_handle(); }

	void __construct(Php::Parameters &param) {
		void *args = (param.size() == 0) ? nullptr : (void *) param[0].stringValue().c_str();
		set_handle(zactor_new (fmq_server, args), true, "fmq_server");
	}

	void set_verbose(Php::Parameters &param) {
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

	Php::Value publish(Php::Parameters &param) {
		if(param.size() != 2)
			throw Php::Exception("Please specify a path and alias.");
		zstr_sendx (fmq_broker_handle(), "PUBLISH", param[0].stringValue().c_str(), param[1].stringValue().c_str(), NULL);

		char *result;
		zstr_recvx (fmq_broker_handle(), &result, NULL);
		if(!result)
			return false;
		Php::Value ret = streq(result,"SUCCESS");
		zstr_free(&result);
		return ret;
	}

    Php::Value recv(Php::Parameters &param) {
        zmsg_t *msg = zmsg_recv (get_socket());
        if(!msg)
            return nullptr;
        return Php::Object("ZMsg", new ZMsg(msg, true));
    }

    static Php::Class<FileMqServer> php_register() {
        Php::Class<FileMqServer> o("Server");
        o.method("__construct", &FileMqServer::__construct);
        o.method("set_verbose", &FileMqServer::set_verbose);
        o.method("load_config", &FileMqServer::load_config);
        o.method("set_config", &FileMqServer::set_config);
        o.method("save_config", &FileMqServer::save_config);
        o.method("bind", &FileMqServer::bind);
        o.method("publish", &FileMqServer::publish, {
			Php::ByVal("local_path", Php::Type::String, true),
			Php::ByVal("alias", Php::Type::String, true)
        });

		// IZSocket intf support
        o.method("get_socket", &FileMqServer::_get_socket);
        o.method("get_fd", &FileMqServer::_get_fd);
        o.method("recv", &FileMqServer::recv);

        return o;
    }

};
