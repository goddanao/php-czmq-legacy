#pragma once

#include "zactor.h"
#include "zutils.h"
#include <iostream>

class ZSocket  : public ZHandle {
private:
    bool _verbose = false;

    static zsock_t *new_socket(const char* name, const char* endpoint);

    static Php::Value new_socket_php(std::string type, Php::Parameters &param) {
        const char *endpoint = (param.size() > 0) ? param[0].stringValue().c_str() : NULL;
    	zsock_t *socket = new_socket(type.c_str(), endpoint);
    	if(socket)
    		return Php::Object("ZSocket", new ZSocket(socket, true));
    	return nullptr;
    }

public:
    ZSocket() : ZHandle() {}
    ZSocket(zsock_t *handle, bool owned) : ZHandle(handle, owned, "zsock") {}
    zsock_t *zsock_handle() const { return (zsock_t *) get_handle(); }

    void __construct(Php::Parameters &param);

    void set_verbose (Php::Parameters &param);

    void set_unbounded();

    static Php::Value pub(Php::Parameters &param) { return Php::Object("ZSocket", new ZSocket(new_socket("pub", param[0].stringValue().c_str()), true)); }
    static Php::Value sub(Php::Parameters &param) { return Php::Object("ZSocket", new ZSocket(new_socket("sub", param[0].stringValue().c_str()), true)); }
    static Php::Value rep(Php::Parameters &param) { return Php::Object("ZSocket", new ZSocket(new_socket("rep", param[0].stringValue().c_str()), true)); }
    static Php::Value req(Php::Parameters &param) { return Php::Object("ZSocket", new ZSocket(new_socket("req", param[0].stringValue().c_str()), true)); }
    static Php::Value dealer(Php::Parameters &param) { return Php::Object("ZSocket", new ZSocket(new_socket("dealer", param[0].stringValue().c_str()), true)); }
    static Php::Value router(Php::Parameters &param) { return Php::Object("ZSocket", new ZSocket(new_socket("router", param[0].stringValue().c_str()), true)); }
    static Php::Value push(Php::Parameters &param) { return Php::Object("ZSocket", new ZSocket(new_socket("push", param[0].stringValue().c_str()), true)); }
    static Php::Value pull(Php::Parameters &param) { return Php::Object("ZSocket", new ZSocket(new_socket("pull", param[0].stringValue().c_str()), true)); }
    static Php::Value xpub(Php::Parameters &param) { return Php::Object("ZSocket", new ZSocket(new_socket("xpub", param[0].stringValue().c_str()), true)); }
    static Php::Value xsub(Php::Parameters &param) { return Php::Object("ZSocket", new ZSocket(new_socket("xsub", param[0].stringValue().c_str()), true)); }
    static Php::Value xreq(Php::Parameters &param) { return Php::Object("ZSocket", new ZSocket(new_socket("xreq", param[0].stringValue().c_str()), true)); }
    static Php::Value xrep(Php::Parameters &param) { return Php::Object("ZSocket", new ZSocket(new_socket("xrep", param[0].stringValue().c_str()), true)); }
    static Php::Value stream(Php::Parameters &param) { return Php::Object("ZSocket", new ZSocket(new_socket("stream",  param[0].stringValue().c_str()), true)); }

//    static Php::Value __callStatic(const char *name, Php::Parameters &params)
//    {
//         Php::out << "example static call" << std::flush;
//        return nullptr;
//
//       const char *endpoint = (params.size() > 0) ? params[0].stringValue().c_str() : NULL;
//       zsock_t *socket = ZSocket::new_socket(name, endpoint);
//       if(!socket)
//         return nullptr;
//       return Php::Object("ZSocket", new ZSocket(socket, true));
//    }

    Php::Value bind(Php::Parameters &param);

    Php::Value unbind(Php::Parameters &param);

    Php::Value connect(Php::Parameters &param);

    Php::Value disconnect(Php::Parameters &param);

    Php::Value attach(Php::Parameters &param);

    Php::Value signal(Php::Parameters &param);

    Php::Value wait();

    void flush();



    // Options
    Php::Value get_tos();
    Php::Value get_zap_domain();
    Php::Value get_mechanism();
    Php::Value get_plain_server();
    Php::Value get_plain_username();
    Php::Value get_plain_password();
    Php::Value get_curve_server();
    Php::Value get_curve_publickey();
    Php::Value get_curve_secretkey();
    Php::Value get_curve_serverkey();
    Php::Value get_gssapi_server();
    Php::Value get_gssapi_plaintext();
    Php::Value get_gssapi_principal();
    Php::Value get_gssapi_service_principal();
    Php::Value get_ipv6();
    Php::Value get_immediate();
    Php::Value get_ipv4only();
    Php::Value get_type();
    Php::Value get_sndhwm();
    Php::Value get_rcvhwm();
    Php::Value get_affinity();
    Php::Value get_identity();
    Php::Value get_rate();
    Php::Value get_recovery_ivl();
    Php::Value get_sndbuf();
    Php::Value get_rcvbuf();
    Php::Value get_linger();
    Php::Value get_reconnect_ivl();
    Php::Value get_reconnect_ivl_max();
    Php::Value get_backlog();
    Php::Value get_maxmsgsize();
    Php::Value get_multicast_hops();
    Php::Value get_rcvtimeo();
    Php::Value get_sndtimeo();
    Php::Value get_tcp_keepalive();
    Php::Value get_tcp_keepalive_idle();
    Php::Value get_tcp_keepalive_cnt();
    Php::Value get_tcp_keepalive_intvl();
    Php::Value get_tcp_accept_filter();
    Php::Value get_rcvmore();
    Php::Value get_events();
    Php::Value get_last_endpoint();

    void set_tos(Php::Parameters &param);
    void set_router_handover(Php::Parameters &param);
    void set_router_mandatory(Php::Parameters &param);
    void set_probe_router(Php::Parameters &param);
    void set_req_relaxed(Php::Parameters &param);
    void set_req_correlate(Php::Parameters &param);
    void set_conflate(Php::Parameters &param);
    void set_zap_domain(Php::Parameters &param);
    void set_plain_server(Php::Parameters &param);
    void set_plain_username(Php::Parameters &param);
    void set_plain_password(Php::Parameters &param);
    void set_curve_server(Php::Parameters &param);
    void set_curve_publickey(Php::Parameters &param);
    void set_curve_publickey_bin(Php::Parameters &param);
    void set_curve_secretkey(Php::Parameters &param);
    void set_curve_secretkey_bin(Php::Parameters &param);
    void set_curve_serverkey(Php::Parameters &param);
    void set_curve_serverkey_bin(Php::Parameters &param);
    void set_gssapi_server(Php::Parameters &param);
    void set_gssapi_plaintext(Php::Parameters &param);
    void set_gssapi_principal(Php::Parameters &param);
    void set_gssapi_service_principal(Php::Parameters &param);
    void set_ipv6(Php::Parameters &param);
    void set_immediate(Php::Parameters &param);
    void set_router_raw(Php::Parameters &param);
    void set_ipv4only(Php::Parameters &param);
    void set_delay_attach_on_connect(Php::Parameters &param);
    void set_sndhwm(Php::Parameters &param);
    void set_rcvhwm(Php::Parameters &param);
    void set_affinity(Php::Parameters &param);
    void set_subscribe(Php::Parameters &param);
    void set_unsubscribe(Php::Parameters &param);
    void set_identity(Php::Parameters &param);
    void set_rate(Php::Parameters &param);
    void set_recovery_ivl(Php::Parameters &param);
    void set_sndbuf(Php::Parameters &param);
    void set_rcvbuf(Php::Parameters &param);
    void set_linger(Php::Parameters &param);
    void set_reconnect_ivl(Php::Parameters &param);
    void set_reconnect_ivl_max(Php::Parameters &param);
    void set_backlog(Php::Parameters &param);
    void set_maxmsgsize(Php::Parameters &param);
    void set_multicast_hops(Php::Parameters &param);
    void set_rcvtimeo(Php::Parameters &param);
    void set_sndtimeo(Php::Parameters &param);
    void set_xpub_verbose(Php::Parameters &param);
    void set_tcp_keepalive(Php::Parameters &param);
    void set_tcp_keepalive_idle(Php::Parameters &param);
    void set_tcp_keepalive_cnt(Php::Parameters &param);
    void set_tcp_keepalive_intvl(Php::Parameters &param);
    void set_tcp_accept_filter(Php::Parameters &param);

    static Php::Class<ZSocket> php_register() {

        Php::Class<ZSocket> o("ZSocket");

    	o.method("__construct", &ZSocket::__construct, {
    		Php::ByVal("socket_type", Php::Type::String, true),
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
    	o.method("attach", &ZSocket::attach, {
            Php::ByVal("endpoints", Php::Type::String, true),
            Php::ByVal("serverish", Php::Type::Bool, false)
        });
    	o.method("signal", &ZSocket::signal, {
            Php::ByVal("byte", Php::Type::Numeric, true)
        });
    	o.method("wait", &ZSocket::wait);
    	o.method("flush", &ZSocket::flush);
    	o.method("send_picture", &ZSocket::send_picture, {
            Php::ByVal("picture", Php::Type::String, true)
        });
    	o.method("recv_picture", &ZSocket::recv_picture, {
            Php::ByVal("picture", Php::Type::String, true)
        });
        o.method("send_string", &ZSocket::send_string, {
            Php::ByVal("value", Php::Type::String, true)
        });
        o.method("recv_string", &ZSocket::recv_string);

    	o.method("send", &ZSocket::send, {
            Php::ByRef("zmsg", "ZMsg", false, true)
        });
    	o.method("recv", &ZSocket::recv);


    	// static accessor

        o.method("pub", &ZSocket::pub);
    	o.method("sub", &ZSocket::sub);
    	o.method("rep", &ZSocket::rep);
    	o.method("req", &ZSocket::req);
    	o.method("dealer", &ZSocket::dealer);
    	o.method("router", &ZSocket::router);
    	o.method("push", &ZSocket::push);
    	o.method("pull", &ZSocket::pull);
    	o.method("xpub", &ZSocket::xpub);
    	o.method("xsub", &ZSocket::xsub);
    	o.method("xreq", &ZSocket::xreq);
    	o.method("xrep", &ZSocket::xrep);
    	o.method("stream", &ZSocket::stream);


    	// Class Options
    	o.method("get_tos", &ZSocket::get_tos);
    	o.method("get_zap_domain", &ZSocket::get_zap_domain);
    	o.method("get_mechanism", &ZSocket::get_mechanism);
    	o.method("get_plain_server", &ZSocket::get_plain_server);
    	o.method("get_plain_username", &ZSocket::get_plain_username);
    	o.method("get_plain_password", &ZSocket::get_plain_password);
    	o.method("get_curve_server", &ZSocket::get_curve_server);
    	o.method("get_curve_publickey", &ZSocket::get_curve_publickey);
    	o.method("get_curve_secretkey", &ZSocket::get_curve_secretkey);
    	o.method("get_curve_serverkey", &ZSocket::get_curve_serverkey);
    	o.method("get_gssapi_server", &ZSocket::get_gssapi_server);
    	o.method("get_gssapi_plaintext", &ZSocket::get_gssapi_plaintext);
    	o.method("get_gssapi_principal", &ZSocket::get_gssapi_principal);
    	o.method("get_gssapi_service_principal", &ZSocket::get_gssapi_service_principal);
    	o.method("get_ipv6", &ZSocket::get_ipv6);
    	o.method("get_immediate", &ZSocket::get_immediate);
    	o.method("get_ipv4only", &ZSocket::get_ipv4only);
    	o.method("get_type", &ZSocket::get_type);
    	o.method("get_sndhwm", &ZSocket::get_sndhwm);
    	o.method("get_rcvhwm", &ZSocket::get_rcvhwm);
    	o.method("get_affinity", &ZSocket::get_affinity);
    	o.method("get_identity", &ZSocket::get_identity);
    	o.method("get_rate", &ZSocket::get_rate);
    	o.method("get_recovery_ivl", &ZSocket::get_recovery_ivl);
    	o.method("get_sndbuf", &ZSocket::get_sndbuf);
    	o.method("get_rcvbuf", &ZSocket::get_rcvbuf);
    	o.method("get_linger", &ZSocket::get_linger);
    	o.method("get_reconnect_ivl", &ZSocket::get_reconnect_ivl);
    	o.method("get_reconnect_ivl_max", &ZSocket::get_reconnect_ivl_max);
    	o.method("get_backlog", &ZSocket::get_backlog);
    	o.method("get_maxmsgsize", &ZSocket::get_maxmsgsize);
    	o.method("get_multicast_hops", &ZSocket::get_multicast_hops);
    	o.method("get_rcvtimeo", &ZSocket::get_rcvtimeo);
    	o.method("get_sndtimeo", &ZSocket::get_sndtimeo);
    	o.method("get_tcp_keepalive", &ZSocket::get_tcp_keepalive);
    	o.method("get_tcp_keepalive_idle", &ZSocket::get_tcp_keepalive_idle);
    	o.method("get_tcp_keepalive_cnt", &ZSocket::get_tcp_keepalive_cnt);
    	o.method("get_tcp_keepalive_intvl", &ZSocket::get_tcp_keepalive_intvl);
    	o.method("get_tcp_accept_filter", &ZSocket::get_tcp_accept_filter);
    	o.method("get_rcvmore", &ZSocket::get_rcvmore);
    	o.method("get_events", &ZSocket::get_events);
    	o.method("get_last_endpoint", &ZSocket::get_last_endpoint);
    	o.method("set_tos", &ZSocket::set_tos);
    	o.method("set_router_handover", &ZSocket::set_router_handover);
    	o.method("set_router_mandatory", &ZSocket::set_router_mandatory);
    	o.method("set_probe_router", &ZSocket::set_probe_router);
    	o.method("set_req_relaxed", &ZSocket::set_req_relaxed);
    	o.method("set_req_correlate", &ZSocket::set_req_correlate);
    	o.method("set_conflate", &ZSocket::set_conflate);
    	o.method("set_zap_domain", &ZSocket::set_zap_domain);
    	o.method("set_plain_server", &ZSocket::set_plain_server);
    	o.method("set_plain_username", &ZSocket::set_plain_username);
    	o.method("set_plain_password", &ZSocket::set_plain_password);
    	o.method("set_curve_server", &ZSocket::set_curve_server);
    	o.method("set_curve_publickey", &ZSocket::set_curve_publickey);
    	o.method("set_curve_publickey_bin", &ZSocket::set_curve_publickey_bin);
    	o.method("set_curve_secretkey", &ZSocket::set_curve_secretkey);
    	o.method("set_curve_secretkey_bin", &ZSocket::set_curve_secretkey_bin);
    	o.method("set_curve_serverkey", &ZSocket::set_curve_serverkey);
    	o.method("set_curve_serverkey_bin", &ZSocket::set_curve_serverkey_bin);
    	o.method("set_gssapi_server", &ZSocket::set_gssapi_server);
    	o.method("set_gssapi_plaintext", &ZSocket::set_gssapi_plaintext);
    	o.method("set_gssapi_principal", &ZSocket::set_gssapi_principal);
    	o.method("set_gssapi_service_principal", &ZSocket::set_gssapi_service_principal);
    	o.method("set_ipv6", &ZSocket::set_ipv6);
    	o.method("set_immediate", &ZSocket::set_immediate);
    	o.method("set_router_raw", &ZSocket::set_router_raw);
    	o.method("set_ipv4only", &ZSocket::set_ipv4only);
    	o.method("set_delay_attach_on_connect", &ZSocket::set_delay_attach_on_connect);
    	o.method("set_sndhwm", &ZSocket::set_sndhwm);
    	o.method("set_rcvhwm", &ZSocket::set_rcvhwm);
    	o.method("set_affinity", &ZSocket::set_affinity);
    	o.method("set_subscribe", &ZSocket::set_subscribe);
    	o.method("set_unsubscribe", &ZSocket::set_unsubscribe);
    	o.method("set_identity", &ZSocket::set_identity);
    	o.method("set_rate", &ZSocket::set_rate);
    	o.method("set_recovery_ivl", &ZSocket::set_recovery_ivl);
    	o.method("set_sndbuf", &ZSocket::set_sndbuf);
    	o.method("set_rcvbuf", &ZSocket::set_rcvbuf);
    	o.method("set_linger", &ZSocket::set_linger);
    	o.method("set_reconnect_ivl", &ZSocket::set_reconnect_ivl);
    	o.method("set_reconnect_ivl_max", &ZSocket::set_reconnect_ivl_max);
    	o.method("set_backlog", &ZSocket::set_backlog);
    	o.method("set_maxmsgsize", &ZSocket::set_maxmsgsize);
    	o.method("set_multicast_hops", &ZSocket::set_multicast_hops);
    	o.method("set_rcvtimeo", &ZSocket::set_rcvtimeo);
    	o.method("set_sndtimeo", &ZSocket::set_sndtimeo);
    	o.method("set_xpub_verbose", &ZSocket::set_xpub_verbose);
    	o.method("set_tcp_keepalive", &ZSocket::set_tcp_keepalive);
    	o.method("set_tcp_keepalive_idle", &ZSocket::set_tcp_keepalive_idle);
    	o.method("set_tcp_keepalive_cnt", &ZSocket::set_tcp_keepalive_cnt);
    	o.method("set_tcp_keepalive_intvl", &ZSocket::set_tcp_keepalive_intvl);
    	o.method("set_tcp_accept_filter", &ZSocket::set_tcp_accept_filter);

        return o;
    }

};
