#include "../../include/majordomo/mdp_broker.h"

void MajordomoBroker::__construct(Php::Parameters &param) {
	if(param.size() > 0)
		_verbose = param[0].boolValue();
	zactor_t *broker = zactor_new(zmdpbroker, NULL);
	if(broker)
		set_handle(broker, true, "zactor");
}

Php::Value MajordomoBroker::bind(Php::Parameters &param) {
	if(param.size() == 0)
		throw Php::Exception("Majordomo Broker can't bind endpoint.");
	zstr_sendx (zmdpbroker_handle(), "BIND", param[0].stringValue().c_str(), NULL);
	// zsock_wait (broker);
	return true;
}

void MajordomoBroker::pause() {
	zstr_sendx (zmdpbroker_handle(), "PAUSE", NULL);
	zsock_wait (zmdpbroker_handle());
}

void MajordomoBroker::stop() {
	_stopped = true;
}

void MajordomoBroker::resume() {
	zstr_sendx (zmdpbroker_handle(), "RESUME", NULL);
	zsock_wait (zmdpbroker_handle());
}

void MajordomoBroker::set_verbose(Php::Parameters &param) {
	_verbose = true;
	zstr_sendx (zmdpbroker_handle(), "VERBOSE", NULL);
	zsock_wait (zmdpbroker_handle());
}

void MajordomoBroker::set_capture(Php::Parameters &param) {
	if(param.size() < 1)
		return;
	std::string socket_endpoints = param[0];
	zstr_sendx(zmdpbroker_handle(), "CAPTURE", socket_endpoints.c_str(), NULL);
	zsock_wait(zmdpbroker_handle());
}

Php::Value MajordomoBroker::get_status() {

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

void MajordomoBroker::on_idle(Php::Parameters &param) {
   	if(param.size()>0 && param[0].isCallable())
    	on_idle_callback = param[0];
   	else
		on_idle_callback = nullptr;
}

void MajordomoBroker::on_tick(Php::Parameters &param) {
	if(param.size()>0 && param[0].isCallable())
    	on_tick_callback = param[0];
    else
    	on_tick_callback = nullptr;
}

void MajordomoBroker::run(Php::Parameters &param) {
	_stopped = false;
	while(!_stopped) {
		char *event, *data;
		int result = zstr_recvx (zmdpbroker_handle(), &event, &data, NULL);
		if(result != -1) {
			if(streq(event, "IDLE") && on_idle_callback.isCallable())
				on_idle_callback(this);
			if(streq(event, "TICK") && on_tick_callback.isCallable())
				on_tick_callback(this);
            zstr_free(&event);
			zstr_free(&data);
		} else {
			break;
		}
	}
}