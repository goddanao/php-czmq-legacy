#pragma once

#include "mlm_client.h"

class MalamuteConsumer   : public ZHandle, public Php::Base {
private:
    std::string _endpoint = "";
    std::string _stream  = "";
    int _timeout = 0;

public:

    MalamuteConsumer() : ZHandle(), Php::Base() {}
    MalamuteConsumer(mlm_client_t *handle, bool owned) : ZHandle(handle, owned, "mlm_client"), Php::Base() {}
    mlm_client_t *mlm_consumer_handle() const { return (mlm_client_t *) get_handle(); }

	void __construct(Php::Parameters &param) {
        mlm_client_t *client = mlm_client_new();
		if(!client)
			throw Php::Exception("Internal Error: Can't create Malamute Consumer.");

		_endpoint = (param.size() > 0) ? param[0].stringValue() : "";
		_stream  = (param.size() > 1) ? param[1].stringValue() : "";

        set_handle(client, true, "mlm_client");
	}

	void set_timeout(Php::Parameters &param) {
	    _timeout = param[0].numericValue();
	}

    void run(Php::Parameters &param){

        int rc = mlm_client_connect(mlm_consumer_handle(), _endpoint.c_str(), _timeout, "");
        if(rc != -1)
            rc = mlm_client_set_consumer(mlm_consumer_handle(), _stream.c_str(), param[0].stringValue().c_str());
        if(rc == -1)
            throw Php::Exception("Internal Error: Can't create Malamute Consumer.");

        zsock_t *client = mlm_client_msgpipe (mlm_consumer_handle());
        zpoller_t *poller = zpoller_new (client, NULL);
        Php::Value result;
        while(!zsys_interrupted && !(result.isBool() && result == false)) {
            zsock_t *which = (zsock_t *) zpoller_wait (poller, 1000);
            if (which == client) {
                zmsg_t *request = mlm_client_recv (mlm_consumer_handle());
                Php::Object zmsg("ZMsg", new ZMsg(request, true));
                result = param[1](zmsg, this);
            }
        }
        zpoller_destroy(&poller);
    }

    Php::Value header(Php::Parameters &param) {
        Php::Value result;
        result["command"]  = mlm_client_command(mlm_consumer_handle());
        result["status"]   = mlm_client_status(mlm_consumer_handle());
        result["reason"]   = mlm_client_reason(mlm_consumer_handle());
        result["address"]  = mlm_client_address(mlm_consumer_handle());
        result["sender"]   = mlm_client_sender(mlm_consumer_handle());
        result["subject"]  = mlm_client_subject(mlm_consumer_handle());
        result["tracker"]  = mlm_client_tracker(mlm_consumer_handle());
        return (param.size() > 0) ? result[param[0].stringValue()] : result;
    }

    Php::Value get_client() { return Php::Object("Malamute\\Client", new MalamuteClient((mlm_client_t *) get_handle(), false)); }

    static Php::Class<MalamuteConsumer> php_register() {
        Php::Class<MalamuteConsumer> o("Consumer");
        o.method("__construct", &MalamuteConsumer::__construct, {
            Php::ByVal("endpoint", Php::Type::String, true),
            Php::ByVal("stream", Php::Type::String, true)
        });
        o.method("set_timeout", &MalamuteConsumer::set_timeout, {
            Php::ByVal("timeout", Php::Type::Numeric, true)
        });
        o.method("header", &MalamuteConsumer::header, {
            Php::ByVal("header", Php::Type::String, false)
        });
        o.method("run", &MalamuteConsumer::run, {
            Php::ByVal("pattern", Php::Type::String, true),
            Php::ByVal("callback", Php::Type::Callable, true)
        });

        o.method("get_client", &MalamuteConsumer::get_client);


        // IZSocket intf support
        o.method("get_fd", &MalamuteConsumer::get_fd);
        o.method("get_socket", &MalamuteConsumer::_get_socket);


        return o;
    }

};
