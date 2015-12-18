#pragma once

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

    static Php::Value libzyre_version() {
        int major, minor, patch;
        zyre_version (&major, &minor, &patch);
        return std::to_string(major) + "." + std::to_string(minor) + "." + std::to_string(patch);
    }

#ifdef MALAMUTE_VERSION_MAJOR

    static Php::Value libmlm_version() {
        int major = MALAMUTE_VERSION_MAJOR, minor = MALAMUTE_VERSION_MINOR, patch = MALAMUTE_VERSION_PATCH;
        return std::to_string(major) + "." + std::to_string(minor) + "." + std::to_string(patch);
    }

#endif

    static Php::Value libmdp_version() {
        int major = MAJORDOMO_VERSION_MAJOR, minor = MAJORDOMO_VERSION_MINOR, patch = MAJORDOMO_VERSION_PATCH;
        return std::to_string(major) + "." + std::to_string(minor) + "." + std::to_string(patch);
    }

    static Php::Value libfmq_version() {
        int major = FILEMQ_VERSION_MAJOR, minor = FILEMQ_VERSION_MINOR, patch = FILEMQ_VERSION_PATCH;
        return std::to_string(major) + "." + std::to_string(minor) + "." + std::to_string(patch);
    }

    static Php::Value libmsgpack_version() {
        int major = MSGPACK_VERSION_MAJOR, minor = MSGPACK_VERSION_MINOR, patch = MSGPACK_VERSION_REVISION;
        return std::to_string(major) + "." + std::to_string(minor) + "." + std::to_string(patch);
    }

    static Php::Value hostname() {
        Php::Value result;
        char *hostname = zsys_hostname();
        result = hostname;
        zstr_free(&hostname);
        return result;
    }

    static std::string getMACAddress(const char * _iface) {
        unsigned char MAC[6];
        int fd = socket(AF_INET, SOCK_DGRAM, 0);
        struct ifreq ifr;
        ifr.ifr_addr.sa_family = AF_INET;
        strncpy(ifr.ifr_name , _iface , IFNAMSIZ-1);
        ioctl(fd, SIOCGIFHWADDR, &ifr);
        for(unsigned int i=0;i<6;i++)
            MAC[i] = ifr.ifr_hwaddr.sa_data[i];
        ioctl(fd, SIOCGIFMTU, &ifr);
        close(fd);

        const char* format = "%.2x:%.2x:%.2x:%.2x:%.2x:%.2x";
        size_t size = snprintf( nullptr, 0, format, MAC[0],MAC[1],MAC[2],MAC[3],MAC[4],MAC[5]) + 1; // Extra space for '\0'
        std::unique_ptr<char[]> buf( new char[ size ] );
        snprintf( buf.get(), size, format, MAC[0],MAC[1],MAC[2],MAC[3],MAC[4],MAC[5]);
        return std::string( buf.get(), buf.get() + size - 1 ); // We don't want the '\0' inside
    }

    static bool getCanBroadcast(const char * _iface) {
        int fd = socket(AF_INET, SOCK_DGRAM, 0);
        struct ifreq ifr;
        ifr.ifr_addr.sa_family = AF_INET;
        strncpy(ifr.ifr_name , _iface , IFNAMSIZ-1);
        if (ioctl(fd, SIOCGIFFLAGS, &ifr) < 0) {
            close(fd);
            throw Php::Exception("Zsys error while accessing socket flags.");
        }
        close(fd);
        return (ifr.ifr_flags & IFF_BROADCAST);
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
            res["can_broadcast"] = getCanBroadcast(name);
            res["mac"] = getMACAddress(name);
            result[idx++] = res;
            name = ziflist_next (iflist);
        }

        ziflist_destroy (&iflist);

        return result;
    }

    static void set_io_threads(Php::Parameters &param) { zsys_set_io_threads(param[0].numericValue()); }
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

    static Php::Value uuid(Php::Parameters &param) {
        return ZUtils::uuid();
    }

    static  Php::Value get_available_socket_type() {
        Php::Value result;
        int idx = 0;
        result[idx++] = "pub";
        result[idx++] = "sub";
        result[idx++] = "req";
        result[idx++] = "rep";
        result[idx++] = "dealer";
        result[idx++] = "router";
        result[idx++] = "push";
        result[idx++] = "pull";
        result[idx++] = "xpub";
        result[idx++] = "xsub";
        result[idx++] = "pair";
        result[idx++] = "stream";

        #ifdef ZMQ_SERVER
            result[idx++] = "server";
            result[idx++] = "client";
        #endif

        return result;
    }

    // IPV6
    #if (CZMQ_VERSION >= CZMQ_MAKE_VERSION(3,0,3))
        static  Php::Value get_ipv6() { return zsys_ipv6(); }
        static  void set_ipv6_address(Php::Parameters &param) { zsys_set_ipv6_address(param[0].stringValue().c_str()); }
        static  Php::Value get_ipv6_address() { return zsys_ipv6_address(); }
        static  void set_ipv6_mcast_address(Php::Parameters &param) { zsys_set_ipv6_mcast_address(param[0].stringValue().c_str()); }
        static  Php::Value get_ipv6_mcast_address(Php::Parameters &param) { return zsys_ipv6_mcast_address(); }
    #endif

    static Php::Class<ZSys> php_register() {

        Php::Class<ZSys> o("ZSys", Php::Public | Php::Final);

        o.method("set_io_threads", &ZSys::set_io_threads, {
            Php::ByVal("threads", Php::Type::Numeric, true)
        });
        o.method("set_ipv6", &ZSys::set_ipv6, {
            Php::ByVal("enable", Php::Type::Bool, true)
        });

        o.method("set_default_linger", &ZSys::set_default_linger, { Php::ByVal("linger", Php::Type::Numeric, true) });
        o.method("set_default_sndhwm", &ZSys::set_default_sndhwm, { Php::ByVal("sndhwm", Php::Type::Numeric, true) });
        o.method("set_default_rcvhwm", &ZSys::set_default_rcvhwm, { Php::ByVal("rcvhwm", Php::Type::Numeric, true) });
        o.method("set_pipehwm", &ZSys::set_pipehwm, { Php::ByVal("pipehwm", Php::Type::Numeric, true) });
        o.method("get_pipehwm", &ZSys::get_pipehwm);

        o.method("has_curve", &ZSys::has_curve);
        o.method("get_socket_limit", &ZSys::get_socket_limit);
        o.method("set_max_sockets", &ZSys::set_max_sockets, { Php::ByVal("max_sockets", Php::Type::Numeric, true) });

        o.method("hostname", &ZSys::hostname);
        o.method("set_interface", &ZSys::set_interface, { Php::ByVal("interface", Php::Type::String, true) });
        o.method("get_interface", &ZSys::get_interface);
        o.method("list_interfaces", &ZSys::list_interfaces);

        o.method("get_available_socket_type", &ZSys::get_available_socket_type);

        o.method("set_log_ident", &ZSys::set_log_ident, { Php::ByVal("log_ident", Php::Type::String, true) });
        o.method("set_log_endpoint", &ZSys::set_log_endpoint, { Php::ByVal("log_endpoint", Php::Type::String, true) });
        o.method("set_log_system", &ZSys::set_log_system, { Php::ByVal("enable", Php::Type::Bool, true) });

        o.method("libzmq_version", &ZSys::libzmq_version);
        o.method("libczmq_version", &ZSys::libczmq_version);
        o.method("libzyre_version", &ZSys::libzyre_version);
        o.method("libmdp_version", &ZSys::libmdp_version);
        o.method("libfmq_version", &ZSys::libfmq_version);
        o.method("libmsgpack_version", &ZSys::libmsgpack_version);


        #ifdef MALAMUTE_VERSION_MAJOR

            o.method("libmlm_version", &ZSys::libmlm_version);

        #endif

        // UUID
        o.method("uuid", &ZSys::uuid);


        // Logging ...
        o.method("info", &ZSys::info, { Php::ByVal("message", Php::Type::String, true) });
        o.method("debug", &ZSys::debug, { Php::ByVal("message", Php::Type::String, true) });
        o.method("warning", &ZSys::warning, { Php::ByVal("message", Php::Type::String, true) });
        o.method("error", &ZSys::error, { Php::ByVal("message", Php::Type::String, true) });

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

    #if (ZMQ_VERSION >= ZMQ_MAKE_VERSION(4,2,0))

        o.constant("SOCKET_SERVER", "server");
        o.constant("SOCKET_CLIENT", "client");

   #endif


        // Const - Event Type
        o.constant("EVENT_CLOSED", ZUtils::sprintf("0x%08x", ZMQ_EVENT_CLOSED));
        o.constant("EVENT_CONNECTED", ZUtils::sprintf("0x%08x", ZMQ_EVENT_CONNECTED));
        o.constant("EVENT_CONNECT_DELAYED", ZUtils::sprintf("0x%08x", ZMQ_EVENT_CONNECT_DELAYED));
        o.constant("EVENT_CONNECT_RETRIED", ZUtils::sprintf("0x%08x", ZMQ_EVENT_CONNECT_RETRIED));
        o.constant("EVENT_LISTENING", ZUtils::sprintf("0x%08x", ZMQ_EVENT_LISTENING));
        o.constant("EVENT_BIND_FAILED", ZUtils::sprintf("0x%08x", ZMQ_EVENT_BIND_FAILED));
        o.constant("EVENT_ACCEPTED", ZUtils::sprintf("0x%08x", ZMQ_EVENT_ACCEPTED));
        o.constant("EVENT_ACCEPT_FAILED", ZUtils::sprintf("0x%08x", ZMQ_EVENT_ACCEPT_FAILED));
        o.constant("EVENT_CLOSE_FAILED", ZUtils::sprintf("0x%08x", ZMQ_EVENT_CLOSE_FAILED));
        o.constant("EVENT_DISCONNECTED", ZUtils::sprintf("0x%08x", ZMQ_EVENT_DISCONNECTED));
        o.constant("EVENT_MONITOR_STOPPED", ZUtils::sprintf("0x%08x", ZMQ_EVENT_MONITOR_STOPPED));
        o.constant("EVENT_ALL", ZUtils::sprintf("0x%08x", ZMQ_EVENT_ALL));

        // Const - Poll Type
        o.constant("POLL_WAIT_FOREVER", -1);
        o.constant("POLL_NONE", 0);
        o.constant("POLL_IN", ZMQ_POLLIN);
        o.constant("POLL_OUT", ZMQ_POLLOUT);
        o.constant("POLL_ERR", ZMQ_POLLERR);

    #ifdef ZMQ_POLLPRI
        o.constant("POLL_PRI", ZMQ_POLLPRI);
    #endif

    // IPV6
    #if (CZMQ_VERSION >= CZMQ_MAKE_VERSION(3,0,3))
        o.method("get_ipv6", &ZSys::get_ipv6);
        o.method("get_ipv6_address", &ZSys::get_ipv6_address);
        o.method("set_ipv6_address", &ZSys::set_ipv6_address, { Php::ByVal("address", Php::Type::String, true) });
        o.method("get_ipv6_mcast_address", &ZSys::get_ipv6_mcast_address);
        o.method("set_ipv6_mcast_address", &ZSys::set_ipv6_mcast_address, { Php::ByVal("address", Php::Type::String, true) });
    #endif

        return o;

    }

};