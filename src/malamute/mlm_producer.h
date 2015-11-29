#pragma once

#if (ZMQ_VERSION >= ZMQ_MAKE_VERSION(4,2,0))

#include "mlm_client.h"

class MalamuteProducer   : public ZHandle, public Php::Base {
private:
    std::string _endpoint = "";
    std::string _stream  = "";
    int _timeout = 0;
public:

    MalamuteProducer() : ZHandle(), Php::Base() {}
    MalamuteProducer(mlm_client_t *handle, bool owned) : ZHandle(handle, owned, "mlm_client"), Php::Base() {}
    mlm_client_t *mlm_producer_handle() const { return (mlm_client_t *) get_handle(); }

	void __construct(Php::Parameters &param) {
		mlm_client_t *client = mlm_client_new();
		if(!client)
			throw Php::Exception("Internal Error: Can't create Malamute Producer.");

		_endpoint = (param.size() > 0) ? param[0].stringValue() : "";
		_stream  = (param.size() > 1) ? param[1].stringValue() : "";

		set_handle(client, true, "mlm_client");
	}

	void set_timeout(Php::Parameters &param) {
	    _timeout = param[0].numericValue();
	}

    void run(Php::Parameters &param){

        int rc = mlm_client_connect(mlm_producer_handle(), _endpoint.c_str(), _timeout, "");
        if(rc != -1)
            rc = mlm_client_set_producer(mlm_producer_handle(), _stream.c_str());
        else
            throw Php::Exception("Internal Error: Can't create Malamute Producer.");

        Php::Value result = param[1]();
        while(!(result.isBool() && result == false)) {
            zmsg_t *reply = ZMsg::msg_from_param(&result);
            mlm_client_send(mlm_producer_handle(), param[0].stringValue().c_str(), &reply);
            result = param[1]();
        }
    }

    Php::Value get_client() { return Php::Object("Malamute\\Client", new MalamuteClient((mlm_client_t *) get_handle(), false)); }

    static Php::Class<MalamuteProducer> php_register() {
        Php::Class<MalamuteProducer> o("Producer");
        o.method("__construct", &MalamuteProducer::__construct, {
            Php::ByVal("endpoint", Php::Type::String, true),
            Php::ByVal("stream", Php::Type::String, true)
        });
        o.method("set_timeout", &MalamuteProducer::set_timeout, {
            Php::ByVal("timeout", Php::Type::Numeric, true)
        });
        o.method("run", &MalamuteProducer::run, {
            Php::ByVal("subject", Php::Type::String, true),
            Php::ByVal("callback", Php::Type::Callable, true)
        });

        o.method("get_client", &MalamuteProducer::get_client);

        // IZSocket intf support
        o.method("get_fd", &MalamuteProducer::get_fd);
        o.method("get_socket", &MalamuteProducer::_get_socket);

        return o;
    }

};

#endif