#include "../include/zauth.h"

void ZAuth::__construct(Php::Parameters &param) {
	set_handle(zactor_new(zauth, NULL), true, "zactor");
}

void ZAuth::set_verbose() {
    zstr_send (zauth_handle(), "VERBOSE");
    zsock_wait(zauth_handle());
}

void ZAuth::allow(Php::Parameters &param) {
	zstr_sendx (zauth_handle(), "ALLOW", param[0].stringValue().c_str(), NULL);
	zsock_wait (zauth_handle());
}

void ZAuth::deny(Php::Parameters &param) {
	zstr_sendx (zauth_handle(), "DENY", param[0].stringValue().c_str(), NULL);
	zsock_wait (zauth_handle());
}

void ZAuth::configure(Php::Parameters &param) {
	if(param.size() == 0)
		return;

	std::string mode = param[0]; // PLAIN CURVE GSSAPI
	if(mode == "PLAIN") {
		if(param.size() < 2) {
			throw Php::Exception("Auth mode PLAIN requires a config filename.");
		}
		std::string filename = param[1];
		zstr_sendx (zauth_handle(), "PLAIN", (void *) filename.c_str(), NULL);
		zsock_wait (zauth_handle());
	}
	else
	if(mode == "CURVE") {
		if(param.size() < 2) {
			throw Php::Exception("Auth mode CURVE requires a directory storing client keys.");
		}
		std::string directory = param[1];
		zstr_sendx (zauth_handle(), "CURVE", (void *) directory.c_str(), NULL);
		zsock_wait (zauth_handle());
	}
	else
	if(mode == "GSSAPI") {
		zstr_sendx (zauth_handle(), "GSSAPI", NULL);
		zsock_wait (zauth_handle());
	}
	else {
		throw Php::Exception("Auth mode not supported.");
	}
}
