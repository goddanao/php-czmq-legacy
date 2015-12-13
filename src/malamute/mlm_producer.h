#pragma once

#include "mlm_client.h"

class MalamuteProducer   : public ZActor, public Php::Base {
private:

    static void *new_actor(Php::Parameters &param, zpoller_t *poller) {
        mlm_client_t *client = mlm_client_new();

        if(client) {
            std::string _endpoint = (param.size() > 0) ? param[0].stringValue() : "";
            std::string _stream   = (param.size() > 1) ? param[1].stringValue() : "";
            int _timeout = 0;

            int rc = mlm_client_connect(client, _endpoint.c_str(), _timeout, "");
            if(rc != -1)
                rc = mlm_client_set_producer(client, _stream.c_str());
            if(rc == -1)
                throw Php::Exception("Internal Error: Can't create Malamute Consumer.");

            if(poller)
                zpoller_add(poller, mlm_client_msgpipe(client));
        }
        return client;
    }

public:

    MalamuteProducer() : ZActor(&MalamuteProducer::new_actor), Php::Base() { _type = "mlm_client"; }
    mlm_client_t *mlm_producer_handle() const { return (mlm_client_t *) get_handle(); }

    bool _send(zmsg_t *msg) override {
        char *subject = zmsg_popstr(msg);
        int rc = mlm_client_send(mlm_producer_handle(), subject, &msg);
        zstr_free(&subject);
        return rc == 0;
    }

    zmsg_t *_recv() override {
        return nullptr;
    }

    static void run(Php::Parameters &param) {
        void *actor = new_actor(param, NULL);
        bool stopped = false;
        while (!zsys_interrupted) {
            Php::Value result = param[3]();
            if(result.isBool() && !result.boolValue())
                break;
            zmsg_t *reply = ZUtils::phpvalue_to_zmsg(result);
            mlm_client_send((mlm_client_t *) actor, param[2].stringValue().c_str(), &reply);
        }
        mlm_client_destroy((mlm_client_t **) &actor);
    }

    Php::Value send_picture(Php::Parameters &param) {
        zmsg_t *msg = zmsg_new();
        // first frame is subject
        zmsg_addstr(msg, param[0].stringValue().c_str());
        ZMsg z(msg, false);
        // remove first param and do it as we know
        ZParameters params(param);
        params.erase(params.begin()+1);
        z.append_picture(params);
        return _send (msg);
    }

    static Php::Class<MalamuteProducer> php_register() {
        Php::Class<MalamuteProducer> o("Producer");
        o.method("__construct", &MalamuteProducer::__construct, {
            Php::ByVal("endpoint", Php::Type::String, true),
            Php::ByVal("stream", Php::Type::String, true)
        });
        o.method("run", &MalamuteProducer::run, {
            Php::ByVal("endpoint", Php::Type::String, true),
            Php::ByVal("stream", Php::Type::String, true),
            Php::ByVal("subject", Php::Type::String, true),
            Php::ByVal("callback", Php::Type::Callable, true)
        });

        o.method("send", &MalamuteProducer::send, {
            Php::ByVal("subject", Php::Type::String, true),
            Php::ByVal("data", Php::Type::String, true)
        });
        o.method("send_string", &MalamuteProducer::send_string, {
            Php::ByVal("subject", Php::Type::String, true),
            Php::ByVal("data", Php::Type::String, true)
        });
        o.method("send_picture", &MalamuteProducer::send_picture, {
            Php::ByVal("subject", Php::Type::String, true),
            Php::ByVal("picture", Php::Type::String, true),
            Php::ByVal("data", Php::Type::String, true)
        });

        // IZSocket intf support
        o.method("get_fd", &MalamuteProducer::get_fd);
        o.method("get_socket", &MalamuteProducer::_get_socket);

        return o;
    }

};
