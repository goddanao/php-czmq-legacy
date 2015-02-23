#include "../../include/malamute/malamute_broker.h"

void MalamuteBroker::__construct(Php::Parameters &param) {
	void *args = (param.size() == 0) ? nullptr : (void *) param[0].stringValue().c_str();
	set_handle(zactor_new (mlm_server, args), true, "zactor");
}

void MalamuteBroker::set_verbose(Php::Parameters &param) {
	verbose = true;
	zstr_sendx (mlm_broker_handle(), "VERBOSE", NULL);
}

void MalamuteBroker::load_config(Php::Parameters &param) {
	if(param.size() == 0)
		throw Php::Exception("Please specify a config file to load.");
	zstr_sendx (mlm_broker_handle(), "LOAD", param[0].stringValue().c_str(), NULL);
}

void MalamuteBroker::set_config(Php::Parameters &param) {
	if(param.size() != 2)
		throw Php::Exception("Please specify a key and a value for config.");
	zstr_sendx (mlm_broker_handle(), "SET", param[0].stringValue().c_str(), param[1].stringValue().c_str(), NULL);
}

void MalamuteBroker::save_config(Php::Parameters &param) {
	if(param.size() == 0)
		throw Php::Exception("Please specify a config file to save.");
	zstr_sendx (mlm_broker_handle(), "SAVE", param[0].stringValue().c_str(), NULL);
}

Php::Value MalamuteBroker::bind(Php::Parameters &param) {
	if(param.size() == 0)
		throw Php::Exception("Malamute Broker can't bind endpoint.");

	zstr_sendx (mlm_broker_handle(), "BIND", param[0].stringValue().c_str(), NULL);

	char *command, *port_str;
	zstr_sendx (mlm_broker_handle(), "PORT", NULL);
	zstr_recvx (mlm_broker_handle(), &command, &port_str, NULL);
	if(streq(command, "PORT")) {
		Php::Value result = port_str;
		free(command);
		free(port_str);
		return result;
	}

	return true;
}

Php::Value MalamuteBroker::get_status() {
//
//	Php::Value result;
//
//	zstr_sendx(mlm_broker_handle(), "STATUS", NULL);
//	zsock_wait(mlm_broker_handle());
//
//    zhash_t *services= NULL;
//    zhash_t *workers = NULL;
//    zlist_t *waiting = NULL;
//	zsock_recv(mlm_broker_handle(), "ppp", &services, &workers, &waiting);
//	zsock_wait(mlm_broker_handle());
//
//	if(services != NULL)	{
//
//		zlist_t *keys = zhash_keys(services);
//		if(keys != NULL) {
//			char *item = (char *) zlist_first(keys);
//			int service_idx = 0;
//
//			while(item) {
//				service_t *svc = (service_t *) zhash_lookup(services, item);
//				if(svc != NULL) {
//					std::string idx = item;
//					result["services"][idx]["workers"] = (int) svc->workers;
//					result["services"][idx]["requests"] = (int) zlist_size(svc->requests);
//					result["services"][idx]["waiting"] = (int) zlist_size(svc->waiting);
//					result["services"][idx]["blacklist"] = (int) zlist_size(svc->blacklist);
//					service_idx++;
//				}
//				item = (char *) zlist_next(keys);
//			}
//			zlist_destroy(&keys);
//		}
//
//		return result;
//	}
//	else
		return nullptr;
}

void MalamuteBroker::on_idle(Php::Parameters &param) {
   if(param.size()>0 && param[0].isCallable())
    	on_idle_callback = param[0];
}

void MalamuteBroker::on_tick(Php::Parameters &param) {
   if(param.size()>0 && param[0].isCallable())
    	on_tick_callback = param[0];
}

void MalamuteBroker::stop() {
	stopped = true;
}

void MalamuteBroker::run(Php::Parameters &param) {
    int64_t stop_after = -1;
    int64_t started = zclock_time();

    if(param.size()>0 && param[0].isNumeric())
        stop_after = param[0].numericValue();

	stopped = false;

	zpoller_t *poller = zpoller_new(mlm_broker_handle(), NULL);

	while(!stopped) {

	    if(stop_after != -1 && ((zclock_time() - started) > stop_after))
	        break;

	    void *socket = zpoller_wait(poller, 1000);
	    if(socket) {
            char *event, *data;
            int result = zstr_recvx (socket, &event, &data, NULL);
            if(result != -1) {
                zsys_info("mlmbroker: %s -> %s", event, data);




                zstr_free(&event);
                zstr_free(&data);
            }
        }
        else
		if(zpoller_expired(poller)) {
	        if(on_tick_callback.isCallable())
                on_tick_callback(this);
            // zsys_info("mlmbroker: TICK");
//            if(on_idle_callback.isCallable())
//                on_idle_callback(this);
		}
		else
		if(zpoller_terminated(poller)) {
			break;
		}
	}

	zpoller_destroy(&poller);
}