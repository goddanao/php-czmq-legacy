#pragma once

#include "mlm_client.h"

class MalamuteWorker : public ZActor, public Php::Base {
private:

    static void *new_actor(Php::Parameters &param, zpoller_t *poller) {
        mlm_client_t *client = mlm_client_new();

        if(client) {
            std::string _endpoint = (param.size() > 0) ? param[0].stringValue() : "";
            std::string _name     = (param.size() > 1) ? param[1].stringValue() : "";
            std::string _pattern  = (param.size() > 2 && param[2].isString()) ? param[2].stringValue() : "";
            int _timeout = 0;

            int rc = mlm_client_connect(client, _endpoint.c_str(), _timeout, (_pattern != "") ? "" : _name.c_str());
            if(rc != -1 && (_pattern != ""))
                rc = mlm_client_set_worker(client, _name.c_str(), _pattern.c_str());
            if(rc == -1)
                throw Php::Exception("Internal Error: Can't create Malamute Consumer.");

            if(poller)
                zpoller_add(poller, mlm_client_msgpipe(client));
        }
        return client;
    }

public:

    MalamuteWorker() : ZActor(&MalamuteWorker::new_actor), Php::Base() { _type = "mlm_client"; }
    mlm_client_t *mlm_worker_handle() const { return (mlm_client_t *) get_handle(); }

	static Php::Value _headers(mlm_client_t *client, std::string _header = "") {
        Php::Value result;
        result["connected"]  = mlm_client_connected(client);
        result["command"]  = mlm_client_command(client);
        result["status"]   = mlm_client_status(client);
        result["reason"]   = mlm_client_reason(client);
        result["address"]  = mlm_client_address(client);
        result["sender"]   = mlm_client_sender(client);
        result["subject"]  = mlm_client_subject(client);
        result["tracker"]  = mlm_client_tracker(client);
        if(_header != "")
            return result[_header];
        return result;

    }

    Php::Value headers(Php::Parameters &param) {
        return _headers(mlm_worker_handle(), param.size() > 0 ? param[0].stringValue() : "");
    }

    Php::Value get_client() { return Php::Object("Malamute\\Client", new MalamuteClient((mlm_client_t *) get_handle(), false)); }


    static void run(Php::Parameters &param) {
        _run(&MalamuteWorker::new_actor,
        [](void *actor){
            mlm_client_destroy((mlm_client_t **) &actor);
        },
        [param](void *actor, void *socket) {
            zmsg_t *request = mlm_client_recv ((mlm_client_t *) actor);
            if(!request)
                return false;

            std::string sender(mlm_client_sender((mlm_client_t *) actor));

            Php::Value result = param[3](Php::Object("ZMsg", new ZMsg(request, true)), _headers((mlm_client_t *) actor));

            if(result.isBool() && !result.boolValue())
                return false;

            if(sender != "") {
                zmsg_t *reply = ZUtils::phpvalue_to_zmsg(result);
                mlm_client_sendto((mlm_client_t *) actor, sender.c_str(), param[1].stringValue().c_str(), mlm_client_subject((mlm_client_t *) actor), 0, &reply);
            }
            return true;
        },
        param);
    }

    static Php::Class<MalamuteWorker> php_register() {
        Php::Class<MalamuteWorker> o("Worker");
        o.method("__construct", &MalamuteWorker::__construct, {
            Php::ByVal("endpoint", Php::Type::String, true),
            Php::ByVal("name", Php::Type::String, true),
            Php::ByVal("pattern", Php::Type::String, false)
        });
        o.method("run", &MalamuteWorker::run, {
            Php::ByVal("endpoint", Php::Type::String, true),
            Php::ByVal("name", Php::Type::String, true),
            Php::ByVal("pattern", Php::Type::String, true),
            Php::ByVal("callback", Php::Type::Callable, true)
        });
        o.method("headers", &MalamuteWorker::headers, {
            Php::ByVal("header", Php::Type::String, false)
        });

        o.method("get_client", &MalamuteWorker::get_client);

        // IZSocket intf support
        o.method("get_fd", &MalamuteWorker::get_fd);
        o.method("get_socket", &MalamuteWorker::_get_socket);

        return o;
    }

};