#pragma once

#include "mlm_client.h"

class MalamuteWorker : public ZActor, public Php::Base {
private:

    static void *new_actor(Php::Parameters &param, zpoller_t *poller) {
        mlm_client_t *client = mlm_client_new();

        if(client) {
            std::string _endpoint = (param.size() > 0) ? param[0].stringValue() : "";

            std::vector<std::string> parts = ZUtils::explode(param[1].stringValue(), '.');
            if(parts.size() <= 0)
                return nullptr;

            std::string _name     = parts[0];
            std::string _pattern  = "";

            for(int idx = 1; idx < parts.size(); idx++)
                _pattern = (_pattern + (_pattern != "" ? "." : "") + parts[idx]);

            int _timeout = 0;

            zsys_info("Creating Service '%s' with pattern '%s'", _name.c_str(), _pattern.c_str());

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

    bool _send(zmsg_t *msg) override {
        return mlm_client_sendto(mlm_worker_handle(), mlm_client_sender(mlm_worker_handle()), mlm_client_address(mlm_worker_handle()), mlm_client_subject(mlm_worker_handle()), 0, &msg);
    }

    zmsg_t *_recv() override {
        return mlm_client_recv (mlm_worker_handle());
    }

    Php::Value headers(Php::Parameters &param) {
        return MalamuteClient::_headers(mlm_worker_handle(), param.size() > 0 ? param[0].stringValue() : "");
    }

    static void run(Php::Parameters &param) {
        _run(param, &MalamuteWorker::new_actor,
        [](void *actor){
            mlm_client_destroy((mlm_client_t **) &actor);
        },
        [param](void *actor, void *socket) {
            zmsg_t *request = mlm_client_recv ((mlm_client_t *) actor);
            if(!request)
                return false;

            std::string _sender(mlm_client_sender((mlm_client_t *) actor));

            Php::Value result = param[2](Php::Object("ZMsg", new ZMsg(request, true)), MalamuteClient::_headers((mlm_client_t *) actor));

            if(result.isBool() && !result.boolValue())
                return false;

            if(_sender != "") {
                zmsg_t *reply = ZUtils::phpvalue_to_zmsg(result);
                if(mlm_client_sendto((mlm_client_t *) actor, _sender.c_str(), mlm_client_address((mlm_client_t *) actor), mlm_client_subject((mlm_client_t *) actor), 0, &reply) != 0)
                    return false;
            }
            return true;
        });
    }

    static Php::Class<MalamuteWorker> php_register() {
        Php::Class<MalamuteWorker> o("Worker");
        o.method("__construct", &MalamuteWorker::__construct, {
            Php::ByVal("endpoint", Php::Type::String, true),
            Php::ByVal("name", Php::Type::String, true)
        });
        o.method("run", &MalamuteWorker::run, {
            Php::ByVal("endpoint", Php::Type::String, true),
            Php::ByVal("name", Php::Type::String, true),
            Php::ByVal("callback", Php::Type::Callable, true)
        });
        o.method("headers", &MalamuteWorker::headers, {
            Php::ByVal("header", Php::Type::String, false)
        });

        // Send / Recv
        ZHandle::register_recv((Php::Class<MalamuteWorker> *) &o);
        ZHandle::register_send((Php::Class<MalamuteWorker> *) &o);

        // IZSocket intf support
        ZHandle::register_izsocket((Php::Class<MalamuteWorker> *) &o);

        return o;
    }

};