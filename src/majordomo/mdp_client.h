#pragma once

#include "../common.h"
#include "../czmq/zmsg.h"

class MajordomoClient : public ZHandle, public Php::Base {
private:
    bool _verbose = false;
    int  _timeout = 30000;      //  default 30s timeout
    std::string _broker_endpoint;

public:

    MajordomoClient() : ZHandle(), Php::Base() {};
    MajordomoClient(mdp_client_t *handle, bool owned) : ZHandle(handle, owned, "mdp_client"), Php::Base() {}
    mdp_client_t *mdpclient_handle() const { return (mdp_client_t *) get_handle(); }

    void __construct(Php::Parameters &param) {
        _broker_endpoint = param[0].stringValue();
        set_handle(mdp_client_new(_broker_endpoint.c_str()), true, "mdp_client");
    }

    void set_verbose() {
        mdp_client_set_verbose(mdpclient_handle());
    }

    Php::Value recv() {
        char *command;
        zmsg_t *body;
        int rc = zsock_recv(get_socket(), "sm", &command, &body);
        if(rc == 0) {
            zstr_free(&command);
            return Php::Object("ZMsg", new ZMsg(body, true));
        }
        return nullptr;
    }

	Php::Value call_async(Php::Parameters &param){
		if(param.size() == 0)
			throw Php::Exception("MajordomoClient call need service name and params..");

        zmsg_t *zmsg;

        if(param.size() > 1) {
            Php::Value p(param[1]);
            zmsg = ZMsg::msg_from_param(&p);
        }
		else
		    zmsg = zmsg_new();

        int rc = mdp_client_request(mdpclient_handle(),  param[0].stringValue().c_str(), &zmsg);
        return (rc == 0);
	}

	Php::Value call(Php::Parameters &param){
	    if(!call_async(param)) {
            return nullptr;
        }
        return recv();
    }

    static Php::Class<MajordomoClient> php_register() {
        Php::Class<MajordomoClient> o("MajordomoClient");
        o.method("__construct", &MajordomoClient::__construct, {
            Php::ByVal("broker_endpoint", Php::Type::String, true)
        });
        o.method("set_verbose", &MajordomoClient::set_verbose);
        o.method("recv", &MajordomoClient::recv);
        o.method("call", &MajordomoClient::call, {
            Php::ByVal("service_name", Php::Type::String, true)
        });
        o.method("call_async", &MajordomoClient::call_async, {
            Php::ByVal("service_name", Php::Type::String, true)
        });
        return o;
    }

};