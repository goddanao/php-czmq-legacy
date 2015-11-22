#pragma once

#include "../common.h"
#include "../czmq/zmsg.h"

class FileMqClient   : public ZHandle, public Php::Base {
private:
    std::string _endpoint   = "";
    std::string _local_dir  = "";
    int _timeout = 0;
    bool _connected = false;
public:

    FileMqClient() : ZHandle(), Php::Base() {}
    FileMqClient(mlm_client_t *handle, bool owned) : ZHandle(handle, owned, "fmq_client"), Php::Base() {}
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

    Php::Value recv(Php::Parameters &param) {
        zmsg_t *msg = zmsg_recv (get_socket());
        if(!msg)
            return nullptr;
        return Php::Object("ZMsg", new ZMsg(msg, true));
    }

    static Php::Class<FileMqClient> php_register() {
        Php::Class<FileMqClient> o("Client");
        o.method("__construct", &FileMqClient::__construct, {
            Php::ByVal("endpoint", Php::Type::String, true),
            Php::ByVal("local_path", Php::Type::String, true),
            Php::ByVal("timeout", Php::Type::Numeric, false)
        });
        o.method("set_timeout", &FileMqClient::set_timeout, {
            Php::ByVal("timeout", Php::Type::Numeric, true)
        });
        o.method("connect", &FileMqClient::connect);
        o.method("subscribe", &FileMqClient::subscribe, {
            Php::ByVal("remote_path", Php::Type::String, true)
        });
        o.method("recv", &FileMqClient::recv);

        // IZSocket intf support
        o.method("get_socket", &FileMqClient::_get_socket);
        o.method("get_fd", &FileMqClient::_get_fd);


        return o;
    }

};
