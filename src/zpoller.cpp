#include "../include/zpoller.h"

void ZPoller::__construct(Php::Parameters &param) {
	set_handle(zpoller_new(NULL), true, "zactor");
	if(param.size() >= 0)
		add(param);
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

	if(param.size() > 0)
		socket_callback = param[0];

	_stopped = false;

	while(!_stopped) {
		void *socket = zpoller_wait(zpoller_handle(), 1000);
		if(zpoller_terminated(zpoller_handle()))
			break;
		else
		if(zpoller_expired(zpoller_handle())) {
			if(idle_callback != NULL)
        		idle_callback(this);
        }
        else
		if(socket != NULL && socket_callback != NULL) {
			socket_callback(pollers[socket], this);
		}
	}

}

void ZPoller::on_idle(Php::Parameters &param) {
	if(param.size() > 0)
		idle_callback = param[0];
	else
		idle_callback = NULL;
}

Php::Value ZPoller::expired() {
	return zpoller_expired(zpoller_handle());
}

Php::Value ZPoller::terminated() {
	return zpoller_terminated(zpoller_handle());
}