#pragma once

#include "zmsg.h"

class ZSocket  : public ZHandle, public Php::Base {
private:
    bool _verbose = false;

public:
    ZSocket() : ZHandle(), Php::Base() {}
    ZSocket(zsock_t *handle, bool owned) : ZHandle(handle, owned, "zsock"), Php::Base() {}
    zsock_t *zsock_handle() const { return (zsock_t *) get_handle(); }

    void __construct(Php::Parameters &param) {

        if(!(param.size() > 0 && param[0].isString() && param[0] != ""))
           throw Php::Exception("Can't create socket");

       int type = -1;
       bool serverish = false;
       std::string name = ZUtils::toLower(param[0]);
       std::string endpoint = param.size() > 1 ? param[1].stringValue() : "";

       if(name == "pub")         { type = ZMQ_PUB; serverish = true; }
       else if(name == "sub")    type = ZMQ_SUB;
       else if(name == "req")    type = ZMQ_REQ;
       else if(name == "rep")    { type = ZMQ_REP; serverish = true; }
       else if(name == "dealer") type = ZMQ_DEALER;
       else if(name == "router") { type = ZMQ_ROUTER; serverish = true; }
       else if(name == "push")   type = ZMQ_PUSH;
       else if(name == "pull")   { type = ZMQ_PULL; serverish = true; }
       else if(name == "xpub")   { type = ZMQ_XPUB; serverish = true; }
       else if(name == "xsub")   type = ZMQ_XSUB;
       else if(name == "xreq")   type = ZMQ_DEALER;
       else if(name == "xrep")   { type = ZMQ_ROUTER; serverish = true; }
       else if(name == "pair")   type = ZMQ_PAIR;
       else if(name == "stream") type = ZMQ_STREAM;

   #if (ZMQ_VERSION >= ZMQ_MAKE_VERSION(4,2,0))

       else if(name == "server") { type = ZMQ_SERVER; serverish = true; }
       else if(name == "client") type = ZMQ_CLIENT;

   #endif

       else
           throw Php::Exception("Can't create socket");

       zsock_t *sock = zsock_new (type);
       if (sock != nullptr) {
           if (zsock_attach (sock, endpoint.c_str(), serverish) == -1) {
               zsock_destroy (&sock);
               sock = nullptr;
           }
       }

       if(sock != nullptr)
           set_handle(sock, true, "zsock");
       else
           throw Php::Exception("Internal Error: Can't create socket.");
    }

    static Php::Value pub(Php::Parameters &param) {
        zsock_t *socket = zsock_new_pub(param.size()>0 ? param[0].stringValue().c_str() : NULL);
        if (socket != nullptr) return Php::Object("ZSocket", new ZSocket(socket, true));
        return nullptr;
    }

    static Php::Value sub(Php::Parameters &param) {
        zsock_t *socket = zsock_new_sub(param.size()>0 ? param[0].stringValue().c_str() : NULL, (param.size()>1 && !param[1].isNull()) ? param[1].stringValue().c_str() : NULL);
        if (socket != nullptr) return Php::Object("ZSocket", new ZSocket(socket, true));
        return nullptr;
    }

    static Php::Value rep(Php::Parameters &param) {
        zsock_t *socket = zsock_new_rep(param.size()>0 ? param[0].stringValue().c_str() : NULL);
        if (socket != nullptr) return Php::Object("ZSocket", new ZSocket(socket, true));
        return nullptr;
    }

    static Php::Value req(Php::Parameters &param) {
        zsock_t *socket = zsock_new_req(param.size()>0 ? param[0].stringValue().c_str() : NULL);
        if (socket != nullptr) return Php::Object("ZSocket", new ZSocket(socket, true));
        return nullptr;
    }

    static Php::Value dealer(Php::Parameters &param) {
        zsock_t *socket = zsock_new_dealer(param.size()>0 ? param[0].stringValue().c_str() : NULL);
        if (socket != nullptr) return Php::Object("ZSocket", new ZSocket(socket, true));
        return nullptr;
    }

    static Php::Value router(Php::Parameters &param) {
        zsock_t *socket = zsock_new_router(param.size()>0 ? param[0].stringValue().c_str() : NULL);
        if (socket != nullptr) return Php::Object("ZSocket", new ZSocket(socket, true));
        return nullptr;
    }

    static Php::Value push(Php::Parameters &param) {
        zsock_t *socket = zsock_new_push(param.size()>0 ? param[0].stringValue().c_str() : NULL);
        if (socket != nullptr) return Php::Object("ZSocket", new ZSocket(socket, true));
        return nullptr;
    }

    static Php::Value pull(Php::Parameters &param) {
        zsock_t *socket = zsock_new_pull(param.size()>0 ? param[0].stringValue().c_str() : NULL);
        if (socket != nullptr) return Php::Object("ZSocket", new ZSocket(socket, true));
        return nullptr;
    }

    static Php::Value xpub(Php::Parameters &param) {
        zsock_t *socket = zsock_new_xpub(param.size()>0 ? param[0].stringValue().c_str() : NULL);
        if (socket != nullptr) return Php::Object("ZSocket", new ZSocket(socket, true));
        return nullptr;
    }

    static Php::Value xsub(Php::Parameters &param) {
        zsock_t *socket = zsock_new_xsub(param.size()>0 ? param[0].stringValue().c_str() : NULL);
        if (socket != nullptr) return Php::Object("ZSocket", new ZSocket(socket, true));
        return nullptr;
    }

    static Php::Value xreq(Php::Parameters &param) {
        zsock_t *socket = zsock_new_dealer(param.size()>0 ? param[0].stringValue().c_str() : NULL);
        if (socket != nullptr) return Php::Object("ZSocket", new ZSocket(socket, true));
        return nullptr;
    }

    static Php::Value xrep(Php::Parameters &param) {
        zsock_t *socket = zsock_new_router(param.size()>0 ? param[0].stringValue().c_str() : NULL);
        if (socket != nullptr) return Php::Object("ZSocket", new ZSocket(socket, true));
        return nullptr;
    }

    static Php::Value pair(Php::Parameters &param) {
        zsock_t *socket = zsock_new_pair(param.size()>0 ? param[0].stringValue().c_str() : NULL);
        if (socket != nullptr) return Php::Object("ZSocket", new ZSocket(socket, true));
        return nullptr;
    }

    static Php::Value stream(Php::Parameters &param) {
        zsock_t *socket = zsock_new_stream(param.size()>0 ? param[0].stringValue().c_str() : NULL);
        if (socket != nullptr) return Php::Object("ZSocket", new ZSocket(socket, true));
        return nullptr;
    }

#if (ZMQ_VERSION >= ZMQ_MAKE_VERSION(4,2,0))

    static Php::Value server(Php::Parameters &param) {
        zsock_t *socket = zsock_new (ZMQ_SERVER);
        if (socket != nullptr) {
           if (zsock_attach (socket, param.size() > 0 ? param[0].stringValue().c_str() : NULL, true) == -1) {
               zsock_destroy (&socket);
               socket = nullptr;
           }
        }
        if (socket != nullptr) return Php::Object("ZSocket", new ZSocket(socket, true));
        return nullptr;
    }

    static Php::Value client(Php::Parameters &param) {
        zsock_t *socket = zsock_new (ZMQ_CLIENT);
        if (socket != nullptr) {
           if (zsock_attach (socket, param.size() > 0 ? param[0].stringValue().c_str() : NULL, false) == -1) {
               zsock_destroy (&socket);
               socket = nullptr;
           }
        }
        if (socket != nullptr) return Php::Object("ZSocket", new ZSocket(socket, true));
        return nullptr;
    }

#endif

//    static Php::Value __callStatic (const char *name, Php::Parameters &params) {
//
//        zsys_info("ECCOMI!!!!!!!!!!!!!!!!!!!!!!!!111");
//        return nullptr;
//
//        // the return value
//        std::string retval = std::string("__callStatic ") + name;
//
//        // loop through the parameters
//        for (auto &param : params)
//        {
//            // append parameter string value to return value
//            retval += " " + param.stringValue();
//        }
//
//        zsys_info(retval.c_str());
//        // done
//        return retval;
//    }

    void set_verbose (Php::Parameters &param) {
        _verbose = param.size() > 0 ? param[0].boolValue() : true;
    }

    void set_unbounded () {
        zsock_set_unbounded(zsock_handle());
    }

    Php::Value bind(Php::Parameters &param) {
        int result = zsock_bind(zsock_handle(), param[0].stringValue().c_str());
        return (result == -1 ? false : (result == 0 ? true : result));
    }

    Php::Value unbind(Php::Parameters &param) {
        return (zsock_unbind(zsock_handle(), param[0].stringValue().c_str()) == 0);
    }

    Php::Value connect(Php::Parameters &param) {
        return (zsock_connect(zsock_handle(), param[0].stringValue().c_str()) == 0);
    }

    Php::Value disconnect(Php::Parameters &param) {
        return (zsock_disconnect(zsock_handle(), param[0].stringValue().c_str()) == 0);
    }

    Php::Value signal(Php::Parameters &param) {
        byte status = (uint8_t) param[0].numericValue();
        return (zsock_signal(zsock_handle(), status) == 0);
    }

    Php::Value wait() {
        return (zsock_wait(zsock_handle()) == 0);
    }

    void flush() {
        zsock_flush(zsock_handle());
    }

    Php::Value get_socket_type();

    Php::Value get_options() {
        Php::Value result;

        #if (ZMQ_VERSION_MAJOR == 4)
            result["tos"] = get_tos();
            result["zap_domain"] = get_zap_domain();
            result["mechanism"] = get_mechanism();
            result["plain_server"] = get_plain_server();
            result["plain_username"] = get_plain_username();
            result["plain_password"] = get_plain_password();
            result["curve_server"] = get_curve_server();
            result["curve_publickey"] = get_curve_publickey();
            result["curve_secretkey"] = get_curve_secretkey();
            result["curve_serverkey"] = get_curve_serverkey();
            result["gssapi_server"] = get_gssapi_server();
            result["gssapi_plaintext"] = get_gssapi_plaintext();
            result["gssapi_principal"] = get_gssapi_principal();
            result["gssapi_service_principal"] = get_gssapi_service_principal();
            result["ipv6"] = get_ipv6();
            result["immediate"] = get_immediate();
        #endif
            result["ipv4only"] = get_ipv4only();
            result["type"] = get_socket_type();
            result["sndhwm"] = get_sndhwm();
            result["rcvhwm"] = get_rcvhwm();
            result["affinity"] = get_affinity();
            result["identity"] = get_identity();
            result["rate"] = get_rate();
            result["recovery_ivl"] = get_recovery_ivl();
            result["sndbuf"] = get_sndbuf();
            result["rcvbuf"] = get_rcvbuf();
            result["linger"] = get_linger();
            result["reconnect_ivl"] = get_reconnect_ivl();
            result["reconnect_ivl_max"] = get_reconnect_ivl_max();
            result["backlog"] = get_backlog();
            result["maxmsgsize"] = get_maxmsgsize();
            result["multicast_hops"] = get_multicast_hops();
            result["rcvtimeo"] = get_rcvtimeo();
            result["sndtimeo"] = get_sndtimeo();
            result["tcp_keepalive"] = get_tcp_keepalive();
            result["tcp_keepalive_idle"] = get_tcp_keepalive_idle();
            result["tcp_keepalive_cnt"] = get_tcp_keepalive_cnt();
            result["tcp_keepalive_intvl"] = get_tcp_keepalive_intvl();
            result["tcp_accept_filter"] = get_tcp_accept_filter();
            result["rcvmore"] = get_rcvmore();
            result["fd"] = get_fd();
            result["events"] = get_events();
            result["last_endpoint"] = get_last_endpoint();


        return result;
    }

    // Get Socket Options

#if (ZMQ_VERSION_MAJOR == 4)
    Php::Value get_tos() ;

    Php::Value get_zap_domain() ;

    Php::Value get_mechanism() ;

    Php::Value get_plain_server() ;

    Php::Value get_plain_username() ;

    Php::Value get_plain_password() ;

    Php::Value get_curve_server() ;

    Php::Value get_curve_publickey() ;

    Php::Value get_curve_secretkey() ;

    Php::Value get_curve_serverkey() ;

    Php::Value get_gssapi_server() ;

    Php::Value get_gssapi_plaintext() ;

    Php::Value get_gssapi_principal() ;

    Php::Value get_gssapi_service_principal() ;

    Php::Value get_ipv6() ;

    Php::Value get_immediate() ;

    Php::Value get_ipv4only() ;

    Php::Value get_sndhwm() ;

    Php::Value get_rcvhwm() ;

    Php::Value get_affinity() ;

    Php::Value get_identity() ;

    Php::Value get_rate() ;

    Php::Value get_recovery_ivl() ;

    Php::Value get_sndbuf() ;

    Php::Value get_rcvbuf() ;

    Php::Value get_linger() ;

    Php::Value get_reconnect_ivl() ;

    Php::Value get_reconnect_ivl_max() ;

    Php::Value get_backlog() ;

    Php::Value get_maxmsgsize() ;

    Php::Value get_multicast_hops() ;

    Php::Value get_rcvtimeo() ;

    Php::Value get_sndtimeo() ;

    Php::Value get_tcp_keepalive() ;

    Php::Value get_tcp_keepalive_idle() ;

    Php::Value get_tcp_keepalive_cnt() ;

    Php::Value get_tcp_keepalive_intvl() ;

    Php::Value get_tcp_accept_filter() ;

    Php::Value get_rcvmore() ;

    Php::Value get_fd() ;

    Php::Value get_events() ;

    Php::Value get_last_endpoint() ;

    Php::Value get_handshake_ivl() ;

    // Set Socket Options

    void set_tos(const Php::Value &value) ;

    void set_router_handover(const Php::Value &value) ;

    void set_router_mandatory(const Php::Value &value) ;

    void set_probe_router(const Php::Value &value) ;

    void set_req_relaxed(const Php::Value &value) ;

    void set_req_correlate(const Php::Value &value) ;

    void set_conflate(const Php::Value &value) ;

    void set_zap_domain(const Php::Value &value) ;

    void set_plain_server(const Php::Value &value) ;

    void set_plain_username(const Php::Value &value) ;

    void set_plain_password(const Php::Value &value) ;

    void set_curve_server(const Php::Value &value) ;

    void set_curve_publickey(const Php::Value &value) ;

    void set_curve_secretkey(const Php::Value &value) ;

    void set_curve_serverkey(const Php::Value &value) ;

    void set_gssapi_server(const Php::Value &value) ;

    void set_gssapi_plaintext(const Php::Value &value) ;

    void set_gssapi_principal(const Php::Value &value) ;

    void set_gssapi_service_principal(const Php::Value &value) ;

    void set_ipv6(const Php::Value &value) ;

    void set_immediate(const Php::Value &value) ;

    void set_router_raw(const Php::Value &value) ;

    void set_ipv4only(const Php::Value &value) ;

    void set_delay_attach_on_connect(const Php::Value &value) ;

    void set_sndhwm(const Php::Value &value) ;

    void set_rcvhwm(const Php::Value &value) ;

    void set_affinity(const Php::Value &value) ;

    void set_subscribe(Php::Parameters &param) ;

    void set_unsubscribe(Php::Parameters &param) ;

    void set_identity(const Php::Value &value) ;

    void set_rate(const Php::Value &value) ;

    void set_recovery_ivl(const Php::Value &value) ;

    void set_sndbuf(const Php::Value &value) ;

    void set_rcvbuf(const Php::Value &value) ;

    void set_linger(const Php::Value &value) ;

    void set_reconnect_ivl(const Php::Value &value) ;

    void set_reconnect_ivl_max(const Php::Value &value) ;

    void set_backlog(const Php::Value &value) ;

    void set_maxmsgsize(const Php::Value &value) ;

    void set_multicast_hops(const Php::Value &value) ;

    void set_rcvtimeo(const Php::Value &value) ;

    void set_sndtimeo(const Php::Value &value) ;

    void set_xpub_verbose(const Php::Value &value) ;

    void set_tcp_keepalive(const Php::Value &value) ;

    void set_tcp_keepalive_idle(const Php::Value &value) ;

    void set_tcp_keepalive_cnt(const Php::Value &value) ;

    void set_tcp_keepalive_intvl(const Php::Value &value) ;

    void set_tcp_accept_filter(const Php::Value &value) ;

    void set_connect_rid(const Php::Value &value) ;

    void set_handshake_ivl(const Php::Value &value) ;

#endif

    // Get Socket Options

#if (ZMQ_VERSION_MAJOR == 3)
    Php::Value get_ipv4only() ;

    Php::Value get_sndhwm() ;

    Php::Value get_rcvhwm() ;

    Php::Value get_affinity() ;

    Php::Value get_identity() ;

    Php::Value get_rate() ;

    Php::Value get_recovery_ivl() ;

    Php::Value get_sndbuf() ;

    Php::Value get_rcvbuf() ;

    Php::Value get_linger() ;

    Php::Value get_reconnect_ivl() ;

    Php::Value get_reconnect_ivl_max() ;

    Php::Value get_backlog() ;

    Php::Value get_maxmsgsize() ;

    Php::Value get_multicast_hops() ;

    Php::Value get_rcvtimeo() ;

    Php::Value get_sndtimeo() ;

    Php::Value get_tcp_keepalive() ;

    Php::Value get_tcp_keepalive_idle() ;

    Php::Value get_tcp_keepalive_cnt() ;

    Php::Value get_tcp_keepalive_intvl() ;

    Php::Value get_tcp_accept_filter() ;

    Php::Value get_rcvmore() ;

    Php::Value get_fd() ;

    Php::Value get_events() ;

    Php::Value get_last_endpoint() ;

    // Set Socket Options

    void set_router_raw(const Php::Value &value) ;

    void set_ipv4only(const Php::Value &value) ;

    void set_delay_attach_on_connect(const Php::Value &value) ;

    void set_sndhwm(const Php::Value &value) ;

    void set_rcvhwm(const Php::Value &value) ;

    void set_affinity(const Php::Value &value) ;

    void set_subscribe(Php::Parameters &param) ;

    void set_unsubscribe(Php::Parameters &param) ;

    void set_identity(const Php::Value &value) ;

    void set_rate(const Php::Value &value) ;

    void set_recovery_ivl(const Php::Value &value) ;

    void set_sndbuf(const Php::Value &value) ;

    void set_rcvbuf(const Php::Value &value) ;

    void set_linger(const Php::Value &value) ;

    void set_reconnect_ivl(const Php::Value &value) ;

    void set_reconnect_ivl_max(const Php::Value &value) ;

    void set_backlog(const Php::Value &value) ;

    void set_maxmsgsize(const Php::Value &value) ;

    void set_multicast_hops(const Php::Value &value) ;

    void set_rcvtimeo(const Php::Value &value) ;

    void set_sndtimeo(const Php::Value &value) ;

    void set_xpub_verbose(Php::Parameters &param) ;

    void set_tcp_keepalive(const Php::Value &value) ;

    void set_tcp_keepalive_idle(const Php::Value &value) ;

    void set_tcp_keepalive_cnt(const Php::Value &value) ;

    void set_tcp_keepalive_intvl(const Php::Value &value) ;

    void set_tcp_accept_filter(const Php::Value &value) ;

#endif

    Php::Value emptyFn(void) { return nullptr; }

    static Php::Class<ZSocket> php_register() {

        Php::Class<ZSocket> o("ZSocket");

        o.method("__construct", &ZSocket::__construct, {
    		Php::ByVal("type", Php::Type::String, true),
    		Php::ByVal("endpoint", Php::Type::String, false)
    	});
    	o.method("set_verbose", &ZSocket::set_verbose);
    	o.method("set_unbounded", &ZSocket::set_unbounded);
    	o.method("bind", &ZSocket::bind, {
    		Php::ByVal("endpoint", Php::Type::String, true)
    	});
    	o.method("unbind", &ZSocket::unbind, {
            Php::ByVal("endpoint", Php::Type::String, true)
        });
    	o.method("connect", &ZSocket::connect, {
    		Php::ByVal("endpoint", Php::Type::String, true)
    	});
    	o.method("disconnect", &ZSocket::disconnect, {
            Php::ByVal("endpoint", Php::Type::String, true)
        });
    	o.method("signal", &ZSocket::signal, {
            Php::ByVal("byte", Php::Type::Numeric, true)
        });
    	o.method("wait", &ZSocket::wait);
    	o.method("flush", &ZSocket::flush);

        //
        ZHandle::register_recv((Php::Class<ZSocket> *) &o);
        ZHandle::register_send((Php::Class<ZSocket> *) &o);

    	// static accessors
        o.method("pub", &ZSocket::pub, {
            Php::ByVal("endpoint", Php::Type::String, false)
        });
    	o.method("sub", &ZSocket::sub, {
            Php::ByVal("endpoint", Php::Type::String, false),
            Php::ByVal("topic", Php::Type::String, false)
        });
    	o.method("rep", &ZSocket::rep, {
            Php::ByVal("endpoint", Php::Type::String, false)
        });
    	o.method("req", &ZSocket::req, {
            Php::ByVal("endpoint", Php::Type::String, false)
        });
    	o.method("dealer", &ZSocket::dealer, {
            Php::ByVal("endpoint", Php::Type::String, false)
        });
    	o.method("router", &ZSocket::router, {
            Php::ByVal("endpoint", Php::Type::String, false)
        });
    	o.method("push", &ZSocket::push, {
            Php::ByVal("endpoint", Php::Type::String, false)
        });
    	o.method("pull", &ZSocket::pull, {
            Php::ByVal("endpoint", Php::Type::String, false)
        });
    	o.method("xpub", &ZSocket::xpub, {
            Php::ByVal("endpoint", Php::Type::String, false)
        });
    	o.method("xsub", &ZSocket::xsub, {
            Php::ByVal("endpoint", Php::Type::String, false)
        });
    	o.method("xreq", &ZSocket::xreq, {
            Php::ByVal("endpoint", Php::Type::String, false)
        });
    	o.method("xrep", &ZSocket::xrep, {
            Php::ByVal("endpoint", Php::Type::String, false)
        });
        o.method("pair", &ZSocket::pair, {
            Php::ByVal("endpoint", Php::Type::String, false)
        });
    	o.method("stream", &ZSocket::stream, {
            Php::ByVal("endpoint", Php::Type::String, false)
        });

    #if (ZMQ_VERSION >= ZMQ_MAKE_VERSION(4,2,0))

    	o.method("server", &ZSocket::server, {
            Php::ByVal("endpoint", Php::Type::String, false)
        });
    	o.method("client", &ZSocket::client, {
            Php::ByVal("endpoint", Php::Type::String, false)
        });

    #endif

    	// Options
        o.method("get_options", &ZSocket::get_options);

        // IZSocket intf support
        ZHandle::register_izsocket((Php::Class<ZSocket> *) &o);

        // Properties
        o.property("ipv4only", &ZSocket::get_ipv4only, &ZSocket::set_ipv4only);
        o.property("type", &ZSocket::get_socket_type);
        o.property("sndhwm", &ZSocket::get_sndhwm, &ZSocket::set_sndhwm);
        o.property("rcvhwm", &ZSocket::get_rcvhwm, &ZSocket::set_rcvhwm);
        o.property("affinity", &ZSocket::get_affinity, &ZSocket::set_affinity);
        o.property("identity", &ZSocket::get_identity, &ZSocket::set_identity);
        o.property("rate", &ZSocket::get_rate, &ZSocket::set_rate);
        o.property("recovery_ivl", &ZSocket::get_recovery_ivl, &ZSocket::set_recovery_ivl);
        o.property("sndbuf", &ZSocket::get_sndbuf, &ZSocket::set_sndbuf);
        o.property("rcvbuf", &ZSocket::get_rcvbuf, &ZSocket::set_rcvbuf);
        o.property("linger", &ZSocket::get_linger, &ZSocket::set_linger);
        o.property("reconnect_ivl", &ZSocket::get_reconnect_ivl, &ZSocket::set_reconnect_ivl);
        o.property("reconnect_ivl_max", &ZSocket::get_reconnect_ivl_max, &ZSocket::set_reconnect_ivl_max);
        o.property("backlog", &ZSocket::get_backlog, &ZSocket::set_backlog);
        o.property("maxmsgsize", &ZSocket::get_maxmsgsize, &ZSocket::set_maxmsgsize);
        o.property("multicast_hops", &ZSocket::get_multicast_hops, &ZSocket::set_multicast_hops);
        o.property("rcvtimeo", &ZSocket::get_rcvtimeo, &ZSocket::set_rcvtimeo);
        o.property("sndtimeo", &ZSocket::get_sndtimeo, &ZSocket::set_sndtimeo);
        o.property("tcp_keepalive", &ZSocket::get_tcp_keepalive, &ZSocket::set_tcp_keepalive);
        o.property("tcp_keepalive_idle", &ZSocket::get_tcp_keepalive_idle, &ZSocket::set_tcp_keepalive_idle);
        o.property("tcp_keepalive_cnt", &ZSocket::get_tcp_keepalive_cnt, &ZSocket::set_tcp_keepalive_cnt);
        o.property("tcp_keepalive_intvl", &ZSocket::get_tcp_keepalive_intvl, &ZSocket::set_tcp_keepalive_intvl);
        o.property("tcp_accept_filter", &ZSocket::get_tcp_accept_filter, &ZSocket::set_tcp_accept_filter);
        o.property("rcvmore", &ZSocket::get_rcvmore);
        o.property("events", &ZSocket::get_events);
        o.property("last_endpoint", &ZSocket::get_last_endpoint);

        o.property("router_raw", &ZSocket::emptyFn, &ZSocket::set_router_raw);
        o.property("delay_attach_on_connect", &ZSocket::emptyFn, &ZSocket::set_delay_attach_on_connect);
        o.property("xpub_verbose", &ZSocket::emptyFn, &ZSocket::set_xpub_verbose);

        o.method("subscribe", &ZSocket::set_subscribe, {
            Php::ByVal("topic", Php::Type::String, true)
        });
        o.method("unsubscribe", &ZSocket::set_unsubscribe, {
            Php::ByVal("topic", Php::Type::String, true)
        });

#if (ZMQ_VERSION_MAJOR == 4)

        o.property("tos", &ZSocket::get_tos, &ZSocket::set_tos);
        o.property("zap_domain", &ZSocket::get_zap_domain, &ZSocket::set_zap_domain);
        o.property("mechanism", &ZSocket::get_mechanism);
        o.property("plain_server", &ZSocket::get_plain_server, &ZSocket::set_plain_server);
        o.property("plain_username", &ZSocket::get_plain_username, &ZSocket::set_plain_username);
        o.property("plain_password", &ZSocket::get_plain_password, &ZSocket::set_plain_password);
        o.property("curve_server", &ZSocket::get_curve_server, &ZSocket::set_curve_server);
        o.property("curve_publickey", &ZSocket::get_curve_publickey, &ZSocket::set_curve_publickey);
        o.property("curve_secretkey", &ZSocket::get_curve_secretkey, &ZSocket::set_curve_secretkey);
        o.property("curve_serverkey", &ZSocket::get_curve_serverkey, &ZSocket::set_curve_serverkey);
        o.property("gssapi_server", &ZSocket::get_gssapi_server, &ZSocket::set_gssapi_server);
        o.property("gssapi_plaintext", &ZSocket::get_gssapi_plaintext, &ZSocket::set_gssapi_plaintext);
        o.property("gssapi_principal", &ZSocket::get_gssapi_principal, &ZSocket::set_gssapi_principal);
        o.property("gssapi_service_principal", &ZSocket::get_gssapi_service_principal, &ZSocket::set_gssapi_service_principal);
        o.property("ipv6", &ZSocket::get_ipv6, &ZSocket::set_ipv6);
        o.property("immediate", &ZSocket::get_immediate, &ZSocket::set_immediate);
        o.property("handshake_ivl", &ZSocket::get_handshake_ivl, &ZSocket::set_handshake_ivl);

        o.property("conflate", &ZSocket::emptyFn, &ZSocket::set_conflate);
        o.property("rid", &ZSocket::emptyFn, &ZSocket::set_connect_rid);
        o.property("router_handover", &ZSocket::emptyFn, &ZSocket::set_router_handover);
        o.property("router_mandatory", &ZSocket::emptyFn, &ZSocket::set_router_mandatory);
        o.property("probe_router", &ZSocket::emptyFn, &ZSocket::set_probe_router);
        o.property("req_relaxed", &ZSocket::emptyFn, &ZSocket::set_req_relaxed);
        o.property("req_correlate", &ZSocket::emptyFn, &ZSocket::set_req_correlate);

#endif


        return o;
    }

};
