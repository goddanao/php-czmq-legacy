#include "../../include/czmq/zpoller.h"

void ZPoller::__construct(Php::Parameters &param) {
	zpoller_t *poller = zpoller_new(NULL);
	if(poller) {
		set_handle(poller, true, "zpoller");
		if(param.size() >= 0)
			add(param);
	} else
		throw Php::Exception("Can't create ZPoller");
}

void ZPoller::set_verbose(Php::Parameters &param) {
	_verbose = param.size() > 0 ? param[0].boolValue() : true;
}

void ZPoller::add(Php::Parameters &param) {
	for (auto &p : param) {
		if(p.isArray()) {
			for (auto &pvalue : p)
				_add(pvalue.second);
		} else {
			_add(p);
		}
	}
}

void ZPoller::remove(Php::Parameters &param) {
	for (auto &p : param) {
		if(p.isArray()) {
			for (auto &pvalue : p)
				_remove(pvalue.second);
		} else {
			_remove(p);
		}
	}
}

void ZPoller::_add(Php::Value p) {
	if(p.isObject()) {
		ZHandle *zhandle = dynamic_cast<ZHandle *>(p.implementation());
		if(zhandle != NULL) {
			zpoller_add(zpoller_handle(), zhandle->get_socket());
			std::pair<void *, Php::Value> el = {zhandle->get_socket(), p};
			pollers.insert(el);
		} else {
			throw Php::Exception("ZPoller add need a ZHandle");
		}
	}
}

void ZPoller::_remove(Php::Value p) {
	if(p.isObject()) {
		ZHandle *zhandle = dynamic_cast<ZHandle*>(p.implementation());
		if(zhandle != NULL) {
			zpoller_remove(zpoller_handle(), zhandle->get_socket());
			pollers.erase(zhandle->get_handle());
		} else {
			throw Php::Exception("ZPoller remove need a ZHandle");
		}
	}
}


void ZPoller::stop() {
	_stopped = true;
}

void ZPoller::start(Php::Parameters &param) {

	_stopped = false;

	while(!_stopped) {
		void *socket = zpoller_wait(zpoller_handle(), 1000);
		if(zpoller_terminated(zpoller_handle()))
			break;
		else
		if(zpoller_expired(zpoller_handle())) {
			if(idle_callback.isCallable()) {
        		idle_callback(this);
			}
        }
        else
		if(socket != NULL && (param.size() > 0 && param[0].isCallable())) {
			param[0](pollers[socket], this);
		}
	}

}

void ZPoller::on_idle(Php::Parameters &param) {
	if(param.size() > 0 && param[0].isCallable()) {
		idle_callback = param[0];
	}
	else {
		idle_callback = NULL;
	}
}

Php::Value ZPoller::expired() {
	return zpoller_expired(zpoller_handle());
}

Php::Value ZPoller::terminated() {
	return zpoller_terminated(zpoller_handle());
}