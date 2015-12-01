#pragma once

#if (ZMQ_VERSION >= ZMQ_MAKE_VERSION(4,2,0))

#include "mlm_client.h"

class MalamuteWorker   : public ZHandle, public Php::Base {
private:
    std::string _endpoint = "";
    std::string _address  = "";
    std::string _pattern  = "";
    int _timeout = 0;
public:

    MalamuteWorker() : ZHandle(), Php::Base() {}
    MalamuteWorker(mlm_client_t *handle, bool owned) : ZHandle(handle, owned, "mlm_client"), Php::Base() {}
    mlm_client_t *mlm_worker_handle() const { return (mlm_client_t *) get_handle(); }

	void __construct(Php::Parameters &param) {
		mlm_client_t *client = mlm_client_new();
		if(!client)
			throw Php::Exception("Internal Error: Can't create Malamute Worker.");

		_endpoint = (param.size() > 0) ? param[0].stringValue() : "";
		_address  = (param.size() > 1) ? param[1].stringValue() : "";
		_pattern  = (param.size() > 2) ? param[2].stringValue() : "";

		set_handle(client, true, "mlm_client");
	}

	void set_timeout(Php::Parameters &param) {
	    _timeout = param[0].numericValue();
	}

    void run(Php::Parameters &param){

        int rc = mlm_client_connect(mlm_worker_handle(), _endpoint.c_str(), _timeout, (_pattern != "") ? "" : _address.c_str());
        if(rc != -1 && (_pattern != "")) {
            rc = mlm_client_set_worker(mlm_worker_handle(), _address.c_str(), _pattern.c_str());
        }
        if(rc == -1)
            throw Php::Exception("Internal Error: Can't create Malamute Worker.");

        zsock_t *client = mlm_client_msgpipe (mlm_worker_handle());
        zpoller_t *poller = zpoller_new (client, NULL);
        Php::Value result;
        while(!zsys_interrupted && !(result.isBool() && result == false)) {
            zsock_t *which = (zsock_t *) zpoller_wait (poller, 1000);
            if (which == client) {
                zmsg_t *request = mlm_client_recv (mlm_worker_handle());
                std::string sender(mlm_client_sender(mlm_worker_handle()));

                Php::Object zmsg("ZMsg", new ZMsg(request, true));
                result = param[0](zmsg, header());

                if(sender != "") {
                    zmsg_t *reply = ZUtils::phpvalue_to_zmsg(result);
                    mlm_client_sendto(mlm_worker_handle(), sender.c_str(), _address.c_str(), mlm_client_subject(mlm_worker_handle()), _timeout, &reply);
                }
            }
        }
        zpoller_destroy(&poller);
    }


	Php::Value header() {
		Php::Value result;
		result["command"]  = mlm_client_command(mlm_worker_handle());
		result["status"]   = mlm_client_status(mlm_worker_handle());
		result["reason"]   = mlm_client_reason(mlm_worker_handle());
		result["address"]  = mlm_client_address(mlm_worker_handle());
		result["sender"]   = mlm_client_sender(mlm_worker_handle());
		result["subject"]  = mlm_client_subject(mlm_worker_handle());
		result["tracker"]  = mlm_client_tracker(mlm_worker_handle());
		return result;
	}

    Php::Value get_client() { return Php::Object("Malamute\\Client", new MalamuteClient((mlm_client_t *) get_handle(), false)); }

    static Php::Class<MalamuteWorker> php_register() {
        Php::Class<MalamuteWorker> o("Worker");
        o.method("__construct", &MalamuteWorker::__construct, {
            Php::ByVal("endpoint", Php::Type::String, true),
            Php::ByVal("address", Php::Type::String, true),
            Php::ByVal("pattern", Php::Type::String, false)
        });
        o.method("set_timeout", &MalamuteWorker::set_timeout, {
            Php::ByVal("timeout", Php::Type::Numeric, true)
        });
        o.method("run", &MalamuteWorker::run, {
            Php::ByVal("callback", Php::Type::Callable, true)
        });

        o.method("get_client", &MalamuteWorker::get_client);

        // IZSocket intf support
        o.method("get_fd", &MalamuteWorker::get_fd);
        o.method("get_socket", &MalamuteWorker::_get_socket);

        return o;
    }

};

#endif