#pragma once

#include "../common.h"
#include "../czmq/zmsg.h"

class FileMqClient   : public ZActor, public Php::Base {
private:
    static void *new_actor(Php::Parameters &param, zpoller_t *poller) {

        std::string _endpoint   = (param.size() > 0) ? param[0].stringValue() : "";
        std::string _local_dir  = (param.size() > 1) ? param[1].stringValue() : "";
        std::string _remote_dir = (param.size() > 2 && param[2].isString()) ? param[2].stringValue() : "";
        int _timeout            = (param.size() == 3 && param[2].isNumeric()) ? param[2].numericValue() : ((param.size() == 4 && param[3].isNumeric()) ? param[3].numericValue() : 0);

        fmq_client_t *client = fmq_client_new();

        int rc = fmq_client_connect(client, _endpoint.c_str(), _timeout);
        if(rc != -1)
            rc = fmq_client_set_inbox(client, _local_dir.c_str());
        if(rc != -1 && _remote_dir != "")
            rc = fmq_client_subscribe(client, _remote_dir.c_str());
        if(rc == -1)
            throw Php::Exception("Internal Error: Can't create FileMQ Client.");

        if(poller)
            zpoller_add(poller, fmq_client_msgpipe(client));

        return client;
    }

public:

    FileMqClient() : ZActor("fmq_client", &FileMqClient::new_actor), Php::Base() { }
    fmq_client_t *fmq_client_handle() const { return (fmq_client_t *) get_handle(); }

	Php::Value subscribe(Php::Parameters &param) {
        return fmq_client_subscribe(fmq_client_handle(), param[0].stringValue().c_str()) == 0;
    }

    static void run(Php::Parameters &param) {
        _run(param, &FileMqClient::new_actor,
        [](void *actor){
            fmq_client_destroy((fmq_client_t **) &actor);
        });
    }

    static Php::Class<FileMqClient> php_register() {
        Php::Class<FileMqClient> o("Client");
        o.method("__construct", &FileMqClient::__construct, {
            Php::ByVal("endpoint", Php::Type::String, true),
            Php::ByVal("local_path", Php::Type::String, true),
            Php::ByVal("timeout", Php::Type::Numeric, false)
        });
        o.method("run", &FileMqClient::run, {
            Php::ByVal("endpoint", Php::Type::String, true),
            Php::ByVal("local_path", Php::Type::String, true),
            Php::ByVal("remote_path", Php::Type::String, true),
            Php::ByVal("timeout", Php::Type::Numeric, false)
        });
        o.method("subscribe", &FileMqClient::subscribe, {
            Php::ByVal("remote_path", Php::Type::String, true)
        });

        // Send / Recv
        ZHandle::register_recv((Php::Class<FileMqClient> *) &o);
        ZHandle::register_send((Php::Class<FileMqClient> *) &o);

        // IZSocket intf support
        ZHandle::register_izsocket((Php::Class<FileMqClient> *) &o);

        return o;
    }

};
