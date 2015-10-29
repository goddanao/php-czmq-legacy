#pragma once

#include "zcontext.h"

class ZSys : public Php::Base {
public:

    static Php::Value libzmq_version() {
        int major, minor, patch;
        zmq_version (&major, &minor, &patch);
        return std::to_string(major) + "." + std::to_string(minor) + "." + std::to_string(patch);
    }

    static Php::Value libczmq_version() {
        int major, minor, patch;
        zsys_version (&major, &minor, &patch);
        return std::to_string(major) + "." + std::to_string(minor) + "." + std::to_string(patch);
    }

//    static Php::Value libzyre_version() {
//        int major, minor, patch;
//        zyre_version (&major, &minor, &patch);
//        return std::to_string(major) + "." + std::to_string(minor) + "." + std::to_string(patch);
//    }

    static Php::Value hostname() {
        Php::Value result;
        char *hostname = zsys_hostname();
        result = hostname;
        zstr_free(&hostname);
        return result;
    }

    static Php::Value list_interfaces() {
        Php::Value result;

        ziflist_t *iflist = ziflist_new ();
        assert (iflist);

        int idx = 0;
        const char *name = ziflist_first (iflist);

        while (name) {
            Php::Value res;
            res["name"] = name;
            res["address"] = ziflist_address (iflist);
            res["netmask"] = ziflist_netmask (iflist);
            res["broadcast"] = ziflist_broadcast (iflist);
            result[idx++] = res;
            name = ziflist_next (iflist);
        }

        ziflist_destroy (&iflist);

        return result;
    }

    static void set_io_threads(Php::Parameters &param) { zsys_set_max_sockets(param[0].numericValue()); }
    static void set_ipv6(Php::Parameters &param) { zsys_set_ipv6(param[0].boolValue() ? 1 : 0); }

    static void set_interface(Php::Parameters &param) { zsys_set_interface(param[0].stringValue().c_str()); }
    static Php::Value get_interface() { return zsys_interface(); }

    static void set_default_linger(Php::Parameters &param) { zsys_set_linger(param[0].numericValue()); }
    static void set_default_sndhwm(Php::Parameters &param) { zsys_set_sndhwm(param[0].numericValue()); }
    static void set_default_rcvhwm(Php::Parameters &param) { zsys_set_rcvhwm(param[0].numericValue()); }
    static void set_pipehwm(Php::Parameters &param) { zsys_set_pipehwm(param[0].numericValue()); }
    static Php::Value get_pipehwm() { return (int) zsys_pipehwm(); }

    static void set_log_ident(Php::Parameters &param) { zsys_set_logident(param[0].stringValue().c_str()); }
    static void set_log_endpoint(Php::Parameters &param) { zsys_set_logsender(param[0].stringValue().c_str()); }
    static void set_log_system(Php::Parameters &param) { zsys_set_logsystem(param[0].boolValue()); }

    static Php::Value has_curve() { return zsys_has_curve(); }
    static Php::Value get_socket_limit() { return (int) zsys_socket_limit(); }
    static void set_max_sockets(Php::Parameters &param) { zsys_set_max_sockets(param[0].numericValue()); }

    static Php::Value context() { return Php::Object("ZContext", new ZContext(zsys_init(), false)); }

    static Php::Value is_interrupted() { return zsys_interrupted; }

    static void info(Php::Parameters &param) {
        if(param.size()>0)
            zsys_info(param[0].stringValue().c_str());
    }

    static void debug(Php::Parameters &param) {
        if(param.size()>0)
            zsys_debug(param[0].stringValue().c_str());
    }

    static void warning(Php::Parameters &param) {
        if(param.size()>0)
            zsys_warning(param[0].stringValue().c_str());
    }

    static void error(Php::Parameters &param) {
        if(param.size()>0)
            zsys_error(param[0].stringValue().c_str());
    }

    static Php::Class<ZSys> php_register() {

        Php::Class<ZSys> o("ZSys");

        // Static methods
        o.method("Context", &ZSys::context);
        o.method("is_interrupted", &ZContext::is_interrupted);

        o.method("set_io_threads", &ZSys::set_io_threads);
        o.method("set_ipv6", &ZSys::set_ipv6);

        o.method("set_default_linger", &ZSys::set_default_linger);
        o.method("set_default_sndhwm", &ZSys::set_default_sndhwm);
        o.method("set_default_rcvhwm", &ZSys::set_default_rcvhwm);
        o.method("set_pipehwm", &ZSys::set_pipehwm);
        o.method("get_pipehwm", &ZSys::get_pipehwm);

        o.method("has_curve", &ZSys::has_curve);
        o.method("get_socket_limit", &ZSys::get_socket_limit);
        o.method("set_max_sockets", &ZSys::set_max_sockets);

        o.method("hostname", &ZSys::hostname);
        o.method("set_interface", &ZSys::set_interface);
        o.method("get_interface", &ZSys::get_interface);
        o.method("list_interfaces", &ZSys::list_interfaces);

        o.method("set_log_ident", &ZSys::set_log_ident);
        o.method("set_log_endpoint", &ZSys::set_log_endpoint);
        o.method("set_log_system", &ZSys::set_log_system);

        o.method("libzmq_version", &ZSys::libzmq_version);
        o.method("libczmq_version", &ZSys::libczmq_version);
        // o.method("libzyre_version", &ZSys::libzyre_version);

        // Logging ...
        o.method("info", &ZSys::info);
        o.method("debug", &ZSys::debug);
        o.method("warning", &ZSys::warning);
        o.method("error", &ZSys::error);

        // Const - Socket Type
        o.constant("SOCKET_PUB", "pub");
        o.constant("SOCKET_SUB", "sub");
        o.constant("SOCKET_REP", "rep");
        o.constant("SOCKET_REQ", "req");
        o.constant("SOCKET_DEALER", "dealer");
        o.constant("SOCKET_ROUTER", "router");
        o.constant("SOCKET_PUSH", "push");
        o.constant("SOCKET_PULL", "pull");
        o.constant("SOCKET_XPUB", "xpub");
        o.constant("SOCKET_XSUB", "xsub");
        o.constant("SOCKET_XREP", "xrep");
        o.constant("SOCKET_XREQ", "xreq");
        o.constant("SOCKET_PAIR", "pair");
        o.constant("SOCKET_STREAM", "stream");

        // Const - Event Type
        o.constant("EVENT_CLOSED", ZMQ_EVENT_CLOSED);
        o.constant("EVENT_CONNECTED", ZMQ_EVENT_CONNECTED);
        o.constant("EVENT_CONNECT_DELAYED", ZMQ_EVENT_CONNECT_DELAYED);
        o.constant("EVENT_CONNECT_RETRIED", ZMQ_EVENT_CONNECT_RETRIED);
        o.constant("EVENT_LISTENING", ZMQ_EVENT_LISTENING);
        o.constant("EVENT_BIND_FAILED", ZMQ_EVENT_BIND_FAILED);
        o.constant("EVENT_ACCEPTED", ZMQ_EVENT_ACCEPTED);
        o.constant("EVENT_ACCEPT_FAILED", ZMQ_EVENT_ACCEPT_FAILED);
        o.constant("EVENT_CLOSE_FAILED", ZMQ_EVENT_CLOSE_FAILED);
        o.constant("EVENT_DISCONNECTED", ZMQ_EVENT_DISCONNECTED);
        o.constant("EVENT_MONITOR_STOPPED", ZMQ_EVENT_MONITOR_STOPPED);
        o.constant("EVENT_ALL", ZMQ_EVENT_ALL);

        // Const - Poll Type
        o.constant("POLL_NONE", 0);
        o.constant("POLL_IN", ZMQ_POLLIN);
        o.constant("POLL_OUT", ZMQ_POLLOUT);
        o.constant("POLL_ERR", ZMQ_POLLERR);

        #ifdef ZMQ_POLLPRI
        o.constant("POLL_PRI", ZMQ_POLLPRI);
        #endif

        return o;

    }

};