#pragma once

#include "mlm_client.h"

class MalamuteConsumer : public ZActor, public Php::Base {
private:

    static void *new_actor(Php::Parameters &param, zpoller_t *poller) {
        mlm_client_t *client = mlm_client_new();

        if(client) {
            std::string _endpoint = (param.size() > 0) ? param[0].stringValue() : "";
            std::string _stream   = (param.size() > 1) ? param[1].stringValue() : "";
            std::string _subject  = (param.size() > 2 && param[2].isString()) ? param[2].stringValue() : "";
            int _timeout = 0;

            int rc = mlm_client_connect(client, _endpoint.c_str(), _timeout, "");
            if(rc != -1 && _stream != "" && _subject != "")
                rc = mlm_client_set_consumer(client, _stream.c_str(), _subject.c_str());
            if(rc == -1)
                throw Php::Exception("Internal Error: Can't create Malamute Consumer.");

            if(poller)
                zpoller_add(poller, mlm_client_msgpipe(client));
        }
        return client;
    }

public:

    MalamuteConsumer() : ZActor(&MalamuteConsumer::new_actor), Php::Base() { _type = "mlm_client"; }
    mlm_client_t *mlm_consumer_handle() const { return (mlm_client_t *) get_handle(); }

    bool _send(zmsg_t *msg) override {
        return false;
    }

    zmsg_t *_recv() override {
        return mlm_client_recv(mlm_consumer_handle());
    }

    Php::Value consume(Php::Parameters &param) {
        return mlm_client_set_consumer(mlm_consumer_handle(), param[0].stringValue().c_str(), param[1].stringValue().c_str()) == 0;
    }

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
        return _headers(mlm_consumer_handle(), param.size() > 0 ? param[0].stringValue() : "");
    }

    static void run(Php::Parameters &param) {
        _run(&MalamuteConsumer::new_actor,
        [](void *actor){
            mlm_client_destroy((mlm_client_t **) &actor);
        },
        [param](void *actor, void *socket){
            zmsg_t *body = mlm_client_recv ((mlm_client_t *) actor);
            if(body) {
                Php::Value result = param[3](Php::Object("ZMsg", new ZMsg(body, true)), _headers((mlm_client_t *) actor));
                if(result.isBool() && !result.boolValue())
                    return false;
            }
            return true;
        },
        param);
    }

    static Php::Class<MalamuteConsumer> php_register() {
        Php::Class<MalamuteConsumer> o("Consumer");
        o.method("__construct", &MalamuteConsumer::__construct, {
            Php::ByVal("endpoint", Php::Type::String, true),
            Php::ByVal("stream", Php::Type::String, false),
            Php::ByVal("pattern", Php::Type::String, false)
        });
        o.method("consume", &MalamuteConsumer::consume, {
            Php::ByVal("stream", Php::Type::String, true),
            Php::ByVal("pattern", Php::Type::String, true)
        });
        o.method("run", &MalamuteConsumer::run, {
            Php::ByVal("endpoint", Php::Type::String, true),
            Php::ByVal("stream", Php::Type::String, true),
            Php::ByVal("pattern", Php::Type::String, true),
            Php::ByVal("callback", Php::Type::Callable, true)
        });
        o.method("headers", &MalamuteConsumer::headers, {
            Php::ByVal("header", Php::Type::String, false)
        });

        o.method("recv", &MalamuteConsumer::recv);
        o.method("recv_string", &MalamuteConsumer::recv_string);
        o.method("recv_picture", &MalamuteConsumer::recv_picture, {
            Php::ByVal("picture", Php::Type::String, true)
        });

        // IZSocket intf support
        o.method("get_fd", &MalamuteConsumer::get_fd);
        o.method("get_socket", &MalamuteConsumer::_get_socket);


        return o;
    }

};
