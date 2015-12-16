#pragma once

#include "../czmq/zmsg.h"

class MajordomoClientV2 : public ZHandle, public Php::Base {
private:
    bool _verbose = false;
    int  _timeout = 30000;      //  default 30s timeout
    std::string _broker_endpoint;

public:

    MajordomoClientV2() : ZHandle(), Php::Base() {};
    MajordomoClientV2(mdp_client_t *handle, bool owned) : ZHandle(handle, owned, "mdp_client_v2"), Php::Base() {}
    mdp_client_t *mdpclient_handle() const { return (mdp_client_t *) get_handle(); }

    void __construct(Php::Parameters &param) {
        _broker_endpoint = param[0].stringValue();
        set_handle(mdp_client_new(_broker_endpoint.c_str()), true, "mdp_client_v2");
    }

    void set_verbose() {
        mdp_client_set_verbose(mdpclient_handle());
    }

    zmsg_t *_recv() override {
        char *command;
        zmsg_t *body;
        int rc = zsock_recv(get_socket(), "sm", &command, &body);
        if(rc == 0) {
            zstr_free(&command);
            return body;
        }
        return nullptr;
    }

	Php::Value call_async(Php::Parameters &param){
		if(param.size() == 0)
			throw Php::Exception("MajordomoClient call need service name and params..");

        zmsg_t *zmsg = ZUtils::params_to_zmsg(param, 1);
        int rc = mdp_client_request(mdpclient_handle(),  param[0].stringValue().c_str(), &zmsg);
        return (rc == 0);
	}

	Php::Value call(Php::Parameters &param){
	    if(!call_async(param)) {
            return nullptr;
        }
        return recv(param);
    }

    static Php::Class<MajordomoClientV2> php_register() {
        Php::Class<MajordomoClientV2> o("Client");
        o.method("__construct", &MajordomoClientV2::__construct, {
            Php::ByVal("broker_endpoint", Php::Type::String, true)
        });
        o.method("set_verbose", &MajordomoClientV2::set_verbose);
        o.method("call", &MajordomoClientV2::call, {
            Php::ByVal("service_name", Php::Type::String, true)
        });
        o.method("call_async", &MajordomoClientV2::call_async, {
            Php::ByVal("service_name", Php::Type::String, true)
        });

        // Send / Recv
        ZHandle::register_recv((Php::Class<MajordomoClientV2> *) &o);
        ZHandle::register_send((Php::Class<MajordomoClientV2> *) &o);

        // IZSocket intf support
        ZHandle::register_izsocket((Php::Class<MajordomoClientV2> *) &o);

        return o;
    }

};