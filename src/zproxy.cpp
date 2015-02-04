#include "../include/zproxy.h"

void ZProxy::__construct(Php::Parameters &param) {
	set_handle(zactor_new(zproxy, NULL), true, "zactor");
}

void ZProxy::pause() {
	zstr_sendx (zproxy_handle(), "PAUSE", NULL);
	zsock_wait (zproxy_handle());
}

void ZProxy::resume() {
	zstr_sendx (zproxy_handle(), "RESUME", NULL);
	zsock_wait (zproxy_handle());
}

void ZProxy::set_verbose(Php::Parameters &param) {
	_verbose = param.size() > 0 ? param[0].boolValue() : true;
	if(!_verbose)
		return;
	zstr_sendx (zproxy_handle(), "VERBOSE", NULL);
	zsock_wait (zproxy_handle());
}

void ZProxy::set_frontend(Php::Parameters &param) {
	if(param.size() < 2)
		return;
	std::string socket_type = toUpper(param[0].stringValue());
	std::string socket_endpoints = param[1];
	zstr_sendx(zproxy_handle(), "FRONTEND", socket_type.c_str(), socket_endpoints.c_str(), NULL);
	zsock_wait(zproxy_handle());
}

void ZProxy::set_backend(Php::Parameters &param) {
	if(param.size() < 2)
		return;
	std::string socket_type = toUpper(param[0]);
	std::string socket_endpoints = param[1];
	zstr_sendx(zproxy_handle(), "BACKEND", socket_type.c_str(), socket_endpoints.c_str(), NULL);
	zsock_wait(zproxy_handle());
}

void ZProxy::set_capture(Php::Parameters &param) {
	if(param.size() < 1)
		return;
	std::string socket_endpoints = param[0];
	zstr_sendx(zproxy_handle(), "CAPTURE", socket_endpoints.c_str(), NULL);
	zsock_wait(zproxy_handle());
}