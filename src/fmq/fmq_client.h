#pragma once

#include "../common.h"
#include "../czmq/zmsg.h"

class FmqClient   : public ZHandle, public Php::Base {
private:
    std::string _endpoint   = "";
    std::string _local_dir  = "";
    int _timeout = 0;
    bool _connected = false;
public:

    FmqClient() : ZHandle(), Php::Base() {}
    FmqClient(mlm_client_t *handle, bool owned) : ZHandle(handle, owned, "fmq_client"), Php::Base() {}
    fmq_client_t *fmq_client_handle() const { return (fmq_client_t *) get_handle(); }

	void __construct(Php::Parameters &param) {
		fmq_client_t *client = fmq_client_new();
		if(!client)
			throw Php::Exception("Internal Error: Can't create FMQ Client.");

		_endpoint   = (param.size() > 0) ? param[0].stringValue() : "";
		_local_dir  = (param.size() > 1) ? param[1].stringValue() : "";
		_timeout  = (param.size() > 2) ? param[2].numericValue() : 0;

		set_handle(client, true, "fmq_client");

		connect();
	}

	void set_timeout(Php::Parameters &param) {
        _timeout = param[0].numericValue();
    }

	void subscribe(Php::Parameters &param) {
	    connect();
        fmq_client_subscribe(fmq_client_handle(), param[0].stringValue().c_str());
    }

    void connect() {
        if(_connected)
            return;

        int rc = fmq_client_connect(fmq_client_handle(), _endpoint.c_str(), _timeout);
        if(rc != -1)
            rc = fmq_client_set_inbox(fmq_client_handle(), _local_dir.c_str());
        if(rc == -1)
            throw Php::Exception("Internal Error: Can't create FileMQ Client.");
        _connected = true;

    }

    void run(Php::Parameters &param){

        connect();

        zsock_t *client = fmq_client_msgpipe (fmq_client_handle());
        zpoller_t *poller = zpoller_new (client, NULL);
        Php::Value result;
        while(!zsys_interrupted && !(result.isBool() && result == false)) {
            zsock_t *which = (zsock_t *) zpoller_wait (poller, 1000);
            if (which == client) {
                zsys_info("messaggio in arrivo da fmq .... client ...");
//                zmsg_t *request = mlm_client_recv (mlm_consumer_handle());
//                Php::Object zmsg("ZMsg", new ZMsg(request, true));
//                result = param[1](zmsg, header());
            }
        }
        zpoller_destroy(&poller);
    }

    static Php::Class<FmqClient> php_register() {
        Php::Class<FmqClient> o("Client");
        o.method("__construct", &FmqClient::__construct, {
            Php::ByVal("endpoint", Php::Type::String, true),
            Php::ByVal("local_path", Php::Type::String, true),
            Php::ByVal("timeout", Php::Type::Numeric, false)
        });
        o.method("set_timeout", &FmqClient::set_timeout, {
            Php::ByVal("timeout", Php::Type::Numeric, true)
        });
        o.method("connect", &FmqClient::connect);
        o.method("subscribe", &FmqClient::subscribe, {
            Php::ByVal("remote_path", Php::Type::String, true)
        });
        o.method("run", &FmqClient::run, {
            Php::ByVal("callback", Php::Type::Callable, true)
        });
        return o;

        return o;
    }

};
