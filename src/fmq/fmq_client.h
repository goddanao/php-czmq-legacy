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

    FileMqClient() : ZActor(&FileMqClient::new_actor), Php::Base() { _type = "fmq_client"; }
    fmq_client_t *fmq_client_handle() const { return (fmq_client_t *) get_handle(); }

	Php::Value subscribe(Php::Parameters &param) {
        return fmq_client_subscribe(fmq_client_handle(), param[0].stringValue().c_str()) == 0;
    }

    static void run(Php::Parameters &param) {
        _run(&FileMqClient::new_actor,
        [](void *actor){
            fmq_client_destroy((fmq_client_t **) &actor);
        },
        [param](void *actor, void *socket){
            char *command;
            zframe_t *address;
            zmsg_t *body;
            int rc = zsock_recv(socket, "sfm", &command, &address, &body);
            if(rc == 0) {
                zstr_free(&command);
                Php::Value result = param[2](Php::Object("ZMsg", new ZMsg(body, true)));
                zmsg_t *zmsg = ZUtils::phpvalue_to_zmsg(result);
                mdp_worker_send_final((mdp_worker_t*) actor, &address, &zmsg);
            }
            return true;
        },
        param);
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

        o.method("send", &FileMqClient::send, {
            Php::ByVal("data", Php::Type::String, true)
        });
        o.method("recv", &FileMqClient::recv);
        o.method("send_string", &FileMqClient::send_string, {
            Php::ByVal("data", Php::Type::String, true)
        });
        o.method("recv_string", &FileMqClient::recv_string);
        o.method("send_picture", &FileMqClient::send_picture, {
            Php::ByVal("picture", Php::Type::String, true)
        });
        o.method("recv_picture", &FileMqClient::recv_picture, {
            Php::ByVal("picture", Php::Type::String, true)
        });

        // IZSocket intf support
        o.method("get_fd", &FileMqClient::get_fd);
        o.method("get_socket", &FileMqClient::_get_socket);


        return o;
    }

};
