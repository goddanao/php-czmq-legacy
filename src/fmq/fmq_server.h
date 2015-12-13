#pragma once

#include "../common.h"

class FileMqServer : public ZActor, public Php::Base {
private:

    static void *new_actor(Php::Parameters &param, zpoller_t *poller) {
        zactor_t *fmqserver = zactor_new (fmq_server, NULL);

        if(fmqserver) {

            if(param.size()>1) {
                if(param.size() > 2 && param[1].isString() && param[2].isString()) {
                    zstr_sendx (fmqserver, "PUBLISH", param[1].stringValue().c_str(), param[2].stringValue().c_str(), NULL);
                    char *result;
                    zstr_recvx (fmqserver, &result, NULL);
                    zstr_free(&result);
                }

                zconfig_t * config;

                // Options
                Php::Array array;
                if(param[1].isArray() && param[1].size() > 0) {
                    config = ZUtils::phparray_to_zconfig(param[1], "fmq_server");
                }
                else
                if(param.size() == 4 && param[3].isArray() && param[3].size() > 0) {
                    config = ZUtils::phparray_to_zconfig(param[3], "fmq_server");
                }

                if(config) {
                    std::string fname = "/tmp/" + ZUtils::uuid() + ".cfg";
                    zconfig_save(config, fname.c_str());
                    zconfig_destroy(&config);
                    zstr_sendx (fmqserver, "LOAD", fname.c_str(), NULL);
                }

            }

            if(param.size()>0) {
                zstr_sendx (fmqserver, "BIND", param[0].stringValue().c_str(), NULL);
                zclock_sleep(200);
            }

            if(poller)
                zpoller_add(poller, fmqserver);

            return fmqserver;
        }
        return nullptr;
    }


public:
    FileMqServer() : ZActor(&FileMqServer::new_actor), Php::Base() { _type = "fmq_server"; }
    zactor_t *fmq_broker_handle() const { return (zactor_t *) get_handle(); }

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
		if(result) {
            Php::Value ret = streq(result,"SUCCESS");
            zstr_free(&result);
            return ret;
		}
	    return false;
	}

	static void run(Php::Parameters &param) {
	    _run(&FileMqServer::new_actor,
        [](void *actor){
            zactor_destroy((zactor_t **) &actor);
        },
        [param](void *actor, void *socket){
            return true;
        },
        param);
    }


    static Php::Class<FileMqServer> php_register() {
        Php::Class<FileMqServer> o("Server");
        o.method("__construct", &FileMqServer::__construct,{
            Php::ByVal("endpoint", Php::Type::String, true),
            Php::ByVal("options", Php::Type::Array, false)
        });
        o.method("run", &FileMqServer::run, {
           Php::ByVal("endpoint", Php::Type::String, true),
           Php::ByVal("path", Php::Type::String, true),
           Php::ByVal("alias", Php::Type::String, true),
           Php::ByVal("options", Php::Type::Array, false)
        });
        o.method("set_verbose", &FileMqServer::set_verbose);
        o.method("bind", &FileMqServer::bind, {
            Php::ByVal("endpoint", Php::Type::String, true)
        });
        o.method("load_config", &FileMqServer::load_config, {
            Php::ByVal("filename", Php::Type::String, true)
        });
        o.method("save_config", &FileMqServer::save_config, {
            Php::ByVal("filename", Php::Type::String, true)
        });
        o.method("set_config", &FileMqServer::set_config, {
            Php::ByVal("key", Php::Type::String, true),
            Php::ByVal("value", Php::Type::String, true)
        });
        o.method("publish", &FileMqServer::publish, {
			Php::ByVal("local_path", Php::Type::String, true),
			Php::ByVal("alias", Php::Type::String, true)
        });

        o.method("send", &FileMqServer::send, {
            Php::ByVal("data", Php::Type::String, true)
        });
        o.method("recv", &FileMqServer::recv);
        o.method("send_string", &FileMqServer::send_string, {
            Php::ByVal("data", Php::Type::String, true)
        });
        o.method("recv_string", &FileMqServer::recv_string);
        o.method("send_picture", &FileMqServer::send_picture, {
            Php::ByVal("picture", Php::Type::String, true)
        });
        o.method("recv_picture", &FileMqServer::recv_picture, {
            Php::ByVal("picture", Php::Type::String, true)
        });

		// IZSocket intf support
        o.method("get_fd", &FileMqServer::get_fd);
        o.method("get_socket", &FileMqServer::_get_socket);

        return o;
    }

};
