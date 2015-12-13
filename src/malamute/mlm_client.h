#pragma once

#include "../common.h"
#include "../czmq/zmsg.h"

class MalamuteClient   : public ZActor, public Php::Base {
private:

    static void *new_actor(Php::Parameters &param, zpoller_t *poller) {
        mlm_client_t *client = mlm_client_new();

        if(client) {
            std::string _endpoint = (param.size() > 0) ? param[0].stringValue() : "";
            std::string _address  = (param.size() > 1) ? param[1].stringValue() : ZUtils::uuid();
            std::string _username = (param.size() > 2) ? param[2].stringValue() : "";
            std::string _password = (param.size() > 3) ? param[3].stringValue() : "";
            int rc = 0;

            if(_username != "")
                rc = mlm_client_set_plain_auth(client, _username.c_str(), _password.c_str());

            if(rc == 0)
                rc = mlm_client_connect(client, _endpoint.c_str(), 0, _address.c_str());
            if(rc == -1)
                throw Php::Exception("Internal Error: Can't create Malamute Consumer.");

            if(poller)
                zpoller_add(poller, mlm_client_msgpipe(client));
        }
        return client;
    }

public:

    MalamuteClient() : ZActor(&MalamuteClient::new_actor), Php::Base() { _type = "mlm_client"; }
    MalamuteClient(mlm_client_t *handle, bool owned) : ZActor(handle, owned, &MalamuteClient::new_actor), Php::Base() { _type = "mlm_client"; }
    mlm_client_t *mlm_client_handle() const { return (mlm_client_t *) get_handle(); }

    zmsg_t *_recv() override {
       return mlm_client_recv (mlm_client_handle());
    }

    bool _send(zmsg_t *msg) override {
        return false;
    }

	static Php::Value _headers(mlm_client_t *client, std::string _header = "") {
        Php::Value result;
        result["connected"]  = mlm_client_connected(client);
        result["command"]    = mlm_client_command(client);
        result["status"]     = mlm_client_status(client);
        result["reason"]     = mlm_client_reason(client);
        result["address"]    = mlm_client_address(client);
        result["sender"]     = mlm_client_sender(client);
        result["subject"]    = mlm_client_subject(client);
        result["tracker"]    = mlm_client_tracker(client);
        if(_header != "")
            return result[_header];
        return result;

    }

    Php::Value headers(Php::Parameters &param) {
        return _headers(mlm_client_handle(), param.size() > 0 ? param[0].stringValue() : "");
    }

	Php::Value content(Php::Parameters &param) {
		zmsg_t *msg = mlm_client_content(mlm_client_handle());
		if(!msg)
			return nullptr;
		return Php::Object("ZMsg", new ZMsg(msg, true));
	}

    Php::Value call(Php::Parameters &param) {
        bool success = call_async(param);
        if(success) {
            zmsg_t *res;
            res = mlm_client_recv (mlm_client_handle());
            if(res)
                return Php::Object("ZMsg", new ZMsg(res, true));
        }
        return nullptr;
    }

    Php::Value call_async(Php::Parameters &param) {
        std::vector<std::string> parts = ZUtils::explode(param[0].stringValue(), '.');
        if(parts.size() == 0)
            return nullptr;

        zmsg_t *msg = ZUtils::params_to_zmsg(param, 1);
        int rc;
        // send mailbox
        if(parts.size() == 1) {
            rc = mlm_client_sendto(mlm_client_handle(), param[0].stringValue().c_str(), "", "", 0, &msg);
        } else {
            std::string _address  = parts[0];
            std::string _subject  = "";

            for(int idx = 1; idx < parts.size(); idx++)
                _subject = (_subject + (_subject != "" ? "." : "") + parts[idx]);

            rc = mlm_client_sendfor(mlm_client_handle(), _address.c_str(), _subject.c_str(), "", 0, &msg);
        }
        return rc == 0;
    }

    static Php::Class<MalamuteClient> php_register() {
        Php::Class<MalamuteClient> o("Client");
        o.method("__construct", &MalamuteClient::__construct, {
            Php::ByVal("endpoint", Php::Type::String, true),
            Php::ByVal("address", Php::Type::String, false),
            Php::ByVal("username", Php::Type::String, false),
            Php::ByVal("password", Php::Type::String, false)
        });

        o.method("call_async", &MalamuteClient::call_async, {
            Php::ByVal("service", Php::Type::String, true),
            Php::ByVal("data", Php::Type::String, true)
        });

        o.method("call", &MalamuteClient::call, {
            Php::ByVal("service", Php::Type::String, true),
            Php::ByVal("data", Php::Type::String, true)
        });

        o.method("headers", &MalamuteClient::headers);
        o.method("content", &MalamuteClient::content);

        o.method("recv", &MalamuteClient::recv);
        o.method("recv_string", &MalamuteClient::recv_string);
        o.method("recv_picture", &MalamuteClient::recv_picture, {
            Php::ByVal("picture", Php::Type::String, true)
        });

        // IZSocket intf support
        o.method("get_fd", &MalamuteClient::get_fd);
        o.method("get_socket", &MalamuteClient::_get_socket);


        return o;
    }

};
