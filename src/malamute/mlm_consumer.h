#pragma once

#include "mlm_client.h"

class MalamuteConsumer : public ZActor, public Php::Base {
private:

    static void *new_actor(Php::Parameters &param, zpoller_t *poller) {
        mlm_client_t *client = mlm_client_new();

        if(client) {

            if(poller)
                zpoller_add(poller, mlm_client_msgpipe(client));

            std::string _endpoint = (param.size() > 0) ? param[0].stringValue() : "";
            std::string _stream   = "";
            std::string _subject  = "";

            if(param.size()>1) {
                std::vector<std::string> parts = ZUtils::explode(param[1].stringValue(), '.');
                if(parts.size() > 1) {
                    _stream     = parts[0];
                    for(int idx = 1; idx < parts.size(); idx++)
                        _subject = (_subject + (_subject != "" ? "." : "") + parts[idx]);
                }
            }

            int rc = mlm_client_connect(client, _endpoint.c_str(), 0, "");
            if(rc == 0 && _stream != "" && _subject != "")
                rc = mlm_client_set_consumer(client, _stream.c_str(), _subject.c_str());
            if(rc == -1) {
                mlm_client_destroy(&client);
                throw Php::Exception("Internal Error: Can't create Malamute Consumer.");
            }


        }
        return client;
    }

public:

    MalamuteConsumer() : ZActor("mlm_client", &MalamuteConsumer::new_actor), Php::Base() { }
    mlm_client_t *mlm_consumer_handle() const { return (mlm_client_t *) get_handle(); }

    zmsg_t *_recv() override {
        return mlm_client_recv(mlm_consumer_handle());
    }

    Php::Value consume(Php::Parameters &param) {
        std::vector<std::string> parts = ZUtils::explode(param[0].stringValue(), '.');
        std::string _stream   = "";
        std::string _subject  = "";
        if(parts.size() > 1) {
            _stream     = parts[0];
            for(int idx = 1; idx < parts.size(); idx++)
                _subject = (_subject + (_subject != "" ? "." : "") + parts[idx]);
        }
        if(_subject == "")
            return false;

        return mlm_client_set_consumer(mlm_consumer_handle(), _stream.c_str(), _subject.c_str()) == 0;
    }

    Php::Value headers(Php::Parameters &param) {
        return MalamuteClient::_headers(mlm_consumer_handle(), param.size() > 0 ? param[0].stringValue() : "");
    }

    static void run(Php::Parameters &param) {
        _run(param, &MalamuteConsumer::new_actor,
        [](void *actor){
            mlm_client_destroy((mlm_client_t **) &actor);
        },
        [param](void *actor, void *socket){
            zmsg_t *body = mlm_client_recv ((mlm_client_t *) actor);
            if(!body) return false;
            Php::Value result = param[2](Php::Object("ZMsg", new ZMsg(body, true)), MalamuteClient::_headers((mlm_client_t *) actor));
            return !(result.isBool() && !result.boolValue());
        });
    }

    static Php::Class<MalamuteConsumer> php_register() {
        Php::Class<MalamuteConsumer> o("Consumer");
        o.method("__construct", &MalamuteConsumer::__construct, {
            Php::ByVal("endpoint", Php::Type::String, true),
            Php::ByVal("stream", Php::Type::String, false)
        });
        o.method("consume", &MalamuteConsumer::consume, {
            Php::ByVal("stream", Php::Type::String, true)
        });
        o.method("run", &MalamuteConsumer::run, {
            Php::ByVal("endpoint", Php::Type::String, true),
            Php::ByVal("stream", Php::Type::String, true),
            Php::ByVal("callback", Php::Type::Callable, true)
        });
        o.method("headers", &MalamuteConsumer::headers, {
            Php::ByVal("header", Php::Type::String, false)
        });

        // ZEmitter
        o.method("start", &MalamuteConsumer::start);
        ZHandle::register_izemitter((Php::Class<MalamuteConsumer> *) &o);

        // Recv
        ZHandle::register_recv((Php::Class<MalamuteConsumer> *) &o);

        // IZSocket intf support
        ZHandle::register_izsocket((Php::Class<MalamuteConsumer> *) &o);

        return o;
    }

};
