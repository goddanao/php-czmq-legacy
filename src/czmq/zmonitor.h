#pragma once

#include "../common.h"

class ZMonitor : public ZHandle, public Php::Base {
private:
    bool _stopped = false;

public:

    ZMonitor() : ZHandle(), Php::Base() {}
    zactor_t *zmonitor_handle() const { return (zactor_t *) get_handle(); }

    void __construct(Php::Parameters &param) {
        ZHandle  *zh = dynamic_cast<ZHandle *> (param[0].implementation());
        if(zh) {
            zsock_t *socket = (zsock_t*) zh->get_socket();
            if(socket == nullptr)
                throw Php::Exception("ZMonitor need a socket to monitor.");

            set_handle(zactor_new(zmonitor, socket), true, "zactor");
        }
    }

    void set_verbose(Php::Parameters &param) {
        zstr_send (zmonitor_handle(), "VERBOSE");
    }

    void listen(Php::Parameters &param) {
        zstr_sendx (zmonitor_handle(), "LISTEN", param[0].stringValue().c_str(), NULL);
    }

    void start() {
        zstr_send (zmonitor_handle(), "START");
        zsock_wait(zmonitor_handle());
    }

    static Php::Class<ZMonitor> php_register() {
        Php::Class<ZMonitor> o("ZMonitor");
        o.method("__construct", &ZMonitor::__construct, {
            Php::ByRef("socket", "IZSocket", false, true)
        });
        o.method("set_verbose", &ZMonitor::set_verbose);
        o.method("listen", &ZMonitor::listen, {
            Php::ByVal("event", Php::Type::String, true)
        });
        o.method("start", &ZMonitor::start);
        o.method("recv", &ZMonitor::recv);

        o.constant("EVT_CONNECTED", "CONNECTED");
        o.constant("EVT_CONNECT_DELAYED", "CONNECT_DELAYED");
        o.constant("EVT_CONNECT_RETRIED", "CONNECT_RETRIED");
        o.constant("EVT_LISTENING", "LISTENING");
        o.constant("EVT_BIND_FAILED", "BIND_FAILED");
        o.constant("EVT_ACCEPTED", "ACCEPTED");
        o.constant("EVT_ACCEPT_FAILED", "ACCEPT_FAILED");
        o.constant("EVT_CLOSED", "CLOSED");
        o.constant("EVT_CLOSE_FAILED", "CLOSE_FAILED");
        o.constant("EVT_DISCONNECTED", "DISCONNECTED");
        o.constant("EVT_MONITOR_STOPPED", "MONITOR_STOPPED");
        o.constant("EVT_ALL", "ALL");

        // IZSocket intf support
        o.method("get_fd", &ZMonitor::get_fd);
        o.method("get_socket", &ZMonitor::_get_socket);

        return o;
    }

};