#pragma once

#include "../../common.h"
#include "../../czmq/zloop.h"
#include "zmdp_common.h"
#include "zmdp_broker.h"

class MajordomoBrokerV1 : public ZHandle, public Php::Base {
private:
    bool _verbose = false;
public:
    MajordomoBrokerV1() : ZHandle(), Php::Base() {}
    zactor_t *zmdpbroker_handle() const { return (zactor_t *) get_handle(); }

	void __construct(Php::Parameters &param) {
		if(param.size() > 0)
			_verbose = param[0].boolValue();
		zactor_t *broker = zactor_new(zmdpbroker, NULL);
		if(broker)
			set_handle(broker, true, "mdp_broker_v1");
	}

	Php::Value bind(Php::Parameters &param) {
		if(param.size() == 0)
			throw Php::Exception("Majordomo Broker can't bind endpoint.");
		zstr_sendx (zmdpbroker_handle(), "BIND", param[0].stringValue().c_str(), NULL);
		zsock_wait (zmdpbroker_handle());
		return true;
	}

	void set_verbose(Php::Parameters &param) {
		_verbose = true;
		zstr_sendx (zmdpbroker_handle(), "VERBOSE", NULL);
		zsock_wait (zmdpbroker_handle());
	}

	void set_capture(Php::Parameters &param) {
		if(param.size() < 1)
			return;
		std::string socket_endpoints = param[0];
		zstr_sendx(zmdpbroker_handle(), "CAPTURE", socket_endpoints.c_str(), NULL);
		zsock_wait(zmdpbroker_handle());
	}

	Php::Value get_status() {

		Php::Value result;

		zstr_sendx(zmdpbroker_handle(), "STATUS", NULL);
		zsock_wait(zmdpbroker_handle());

		zhash_t *services= NULL;
		zhash_t *workers = NULL;
		zlist_t *waiting = NULL;
		zsock_recv(zmdpbroker_handle(), "ppp", &services, &workers, &waiting);
		zsock_wait(zmdpbroker_handle());

		if(services != NULL)	{

			zlist_t *keys = zhash_keys(services);
			if(keys != NULL) {
				char *item = (char *) zlist_first(keys);
				int service_idx = 0;

				while(item) {
					service_t *svc = (service_t *) zhash_lookup(services, item);
					if(svc != NULL) {
						std::string idx = item;
						result["services"][idx]["workers"] = (int) svc->workers;
						result["services"][idx]["requests"] = (int) zlist_size(svc->requests);
						result["services"][idx]["waiting"] = (int) zlist_size(svc->waiting);
						result["services"][idx]["blacklist"] = (int) zlist_size(svc->blacklist);
						service_idx++;
					}
					item = (char *) zlist_next(keys);
				}
				zlist_destroy(&keys);
			}

			return result;
		}
		else
			return nullptr;
	}

     static Php::Class<MajordomoBrokerV1> php_register() {
        Php::Class<MajordomoBrokerV1> o("Broker");
        o.method("__construct", &MajordomoBrokerV1::__construct);
        o.method("bind", &MajordomoBrokerV1::bind);
        o.method("set_verbose", &MajordomoBrokerV1::set_verbose);
        o.method("get_status", &MajordomoBrokerV1::get_status);
        o.method("set_capture", &MajordomoBrokerV1::set_capture, {
            Php::ByVal("socket_endpoint", Php::Type::String, true)
        });

        // IZSocket intf support
		o.method("get_socket", &MajordomoBrokerV1::_get_socket);
		o.method("get_fd", &MajordomoBrokerV1::_get_fd);

        return o;
    }
};