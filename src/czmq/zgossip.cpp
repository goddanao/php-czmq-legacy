#include "../../include/czmq/zgossip.h"

void ZGossip::__construct(Php::Parameters &param) {
	set_handle(zactor_new(zgossip, NULL), true, "zactor");
}

void ZGossip::set_verbose(Php::Parameters &param) {
    zstr_send (zgossip_handle(), "VERBOSE");
}

Php::Value ZGossip::bind(Php::Parameters &param) {
    Php::Value result;
    zstr_sendx (zgossip_handle(), "BIND", param[0].stringValue().c_str(), NULL);
    zstr_sendx (zgossip_handle(), "PORT", NULL);
    char *command, *port_str;
    zstr_recvx (zgossip_handle(), &command, &port_str, NULL);
    if (streq (command, "PORT") && port_str != NULL) {
        std::string port(port_str);
        result = port;
    }
    if(command)
        free(command);
    if(port_str)
        free(port_str);
    return result.isNull() ? nullptr : result;
}

void ZGossip::connect(Php::Parameters &param) {
    zstr_sendx (zgossip_handle(), "CONNECT", param[0].stringValue().c_str(), NULL);
}

void ZGossip::configure(Php::Parameters &param) {
    zstr_sendx (zgossip_handle(), "LOAD", param[0].stringValue().c_str(), NULL);
}

void ZGossip::set(Php::Parameters &param) {
    zstr_sendx (zgossip_handle(), "SET", param[0].stringValue().c_str(), param[1].stringValue().c_str(), NULL);
}

void ZGossip::publish(Php::Parameters &param) {
    zstr_sendx (zgossip_handle(), "PUBLISH", param[0].stringValue().c_str(), param[1].stringValue().c_str(), NULL);
}

Php::Value ZGossip::count() {
    zstr_sendx (zgossip_handle(), "STATUS", NULL);
    char *command, *status;
    zstr_recvx (zgossip_handle(), &command, &status, NULL);
    assert (streq (command, "STATUS"));
    Php::Value result = status;
    free(command);
    free(status);
    return result;
}