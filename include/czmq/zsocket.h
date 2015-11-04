#pragma once

#include <iostream>
#include "zmsg.h"

class ZSocket  : public ZHandle {
private:
    bool _verbose = false;

    static zsock_t *new_socket(const char* name, const char* endpoint) {

       if(name == NULL || name == nullptr || (strcmp(name, "") == 0))
           return NULL;

       int type = 0;

       if(strcmp(name,"pub") == 0)         type = ZMQ_PUB; // socket = zsock_new_pub(endpoint);
       else if(strcmp(name,"sub") == 0)    type = ZMQ_SUB; // socket = zsock_new_sub(endpoint, NULL);
       else if(strcmp(name,"req") == 0)    type = ZMQ_REQ; // socket = zsock_new_req(endpoint);
       else if(strcmp(name,"rep") == 0)    type = ZMQ_REP; // socket = zsock_new_rep(endpoint);
       else if(strcmp(name,"dealer") == 0) type = ZMQ_DEALER; // socket = zsock_new_dealer(endpoint);
       else if(strcmp(name,"router") == 0) type = ZMQ_ROUTER; // socket = zsock_new_router(endpoint);
       else if(strcmp(name,"push") == 0)   type = ZMQ_PUSH; // socket = zsock_new_push(endpoint);
       else if(strcmp(name,"pull") == 0)   type = ZMQ_PULL; // socket = zsock_new_pull(endpoint);
       else if(strcmp(name,"xpub") == 0)   type = ZMQ_XPUB; // socket = zsock_new_xpub(endpoint);
       else if(strcmp(name,"xsub") == 0)   type = ZMQ_XSUB; // socket = zsock_new_xsub(endpoint);
       else if(strcmp(name,"xreq") == 0)   type = ZMQ_DEALER; // socket = zsock_new_dealer(endpoint);
       else if(strcmp(name,"xrep") == 0)   type = ZMQ_ROUTER; // socket = zsock_new_router(endpoint);
       else if(strcmp(name,"pair") == 0)   type = ZMQ_PAIR; // socket = zsock_new_pair(endpoint);
       else if(strcmp(name,"stream") == 0) type = ZMQ_STREAM; // socket = zsock_new_stream(endpoint);
       else
           throw Php::Exception("Can't create socket");

       zsock_t *sock = zsock_new (type);
       if (sock != NULL) {

           zsock_set_ipv4only(sock, 1);
           zsock_set_ipv6(sock, 0);

           if(endpoint != NULL) {
               // zsys_info("Connecting socket %s -> %s", name, endpoint);
               if (zsock_attach (sock, endpoint, true)) {
                   zsock_destroy (&sock);
                   sock = NULL;
               }
           }
       }
       return sock;
   }

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

    inline static Php::Value pub(Php::Parameters &param) { return Php::Object("ZSocket", new ZSocket(new_socket("pub", param[0].stringValue().c_str()), true)); }
    inline static Php::Value sub(Php::Parameters &param) { return Php::Object("ZSocket", new ZSocket(new_socket("sub", param[0].stringValue().c_str()), true)); }
    inline static Php::Value rep(Php::Parameters &param) { return Php::Object("ZSocket", new ZSocket(new_socket("rep", param[0].stringValue().c_str()), true)); }
    inline static Php::Value req(Php::Parameters &param) { return Php::Object("ZSocket", new ZSocket(new_socket("req", param[0].stringValue().c_str()), true)); }
    inline static Php::Value dealer(Php::Parameters &param) { return Php::Object("ZSocket", new ZSocket(new_socket("dealer", param[0].stringValue().c_str()), true)); }
    inline static Php::Value router(Php::Parameters &param) { return Php::Object("ZSocket", new ZSocket(new_socket("router", param[0].stringValue().c_str()), true)); }
    inline static Php::Value push(Php::Parameters &param) { return Php::Object("ZSocket", new ZSocket(new_socket("push", param[0].stringValue().c_str()), true)); }
    inline static Php::Value pull(Php::Parameters &param) { return Php::Object("ZSocket", new ZSocket(new_socket("pull", param[0].stringValue().c_str()), true)); }
    inline static Php::Value xpub(Php::Parameters &param) { return Php::Object("ZSocket", new ZSocket(new_socket("xpub", param[0].stringValue().c_str()), true)); }
    inline static Php::Value xsub(Php::Parameters &param) { return Php::Object("ZSocket", new ZSocket(new_socket("xsub", param[0].stringValue().c_str()), true)); }
    inline static Php::Value xreq(Php::Parameters &param) { return Php::Object("ZSocket", new ZSocket(new_socket("xreq", param[0].stringValue().c_str()), true)); }
    inline static Php::Value xrep(Php::Parameters &param) { return Php::Object("ZSocket", new ZSocket(new_socket("xrep", param[0].stringValue().c_str()), true)); }
    inline static Php::Value stream(Php::Parameters &param) { return Php::Object("ZSocket", new ZSocket(new_socket("stream",  param[0].stringValue().c_str()), true)); }


    Php::Value send_picture(Php::Parameters &param) {
        zmsg_t *msg = zmsg_new();
        ZMsg z(msg, false);
        z.append_picture(param);
        return (zmsg_send (&msg, get_socket()) == 0);
    }

    Php::Value recv_picture(Php::Parameters &param) {
        zmsg_t *msg = zmsg_recv (get_socket());
        if(!msg)
            return nullptr;
        ZMsg z(msg, true);
        return z.pop_picture(param);
    }

    Php::Value send_string(Php::Parameters &param) {
        zmsg_t *msg = zmsg_new();
        ZMsg z(msg, false);
        z.append_string(param);
        return (zmsg_send (&msg, get_socket()) == 0);
    }

    Php::Value recv_string(Php::Parameters &param) {
        zmsg_t *msg = zmsg_recv (get_socket());
        if(!msg)
            return nullptr;
        ZMsg z(msg, true);
        return z.pop_string();
    }

    Php::Value send(Php::Parameters &param) {
        ZMsg *zmsg = dynamic_cast<ZMsg *>(param[0].implementation());
        zmsg_t *czmsg = zmsg_dup(zmsg->zmsg_handle());
        return zmsg_send(&czmsg, get_socket());
    }

    Php::Value recv(Php::Parameters &param) {
        zmsg_t *msg = zmsg_recv (get_socket());
        if(!msg)
            return nullptr;
        return Php::Object("ZMsg", new ZMsg(msg, true));
    }

    void __construct(Php::Parameters &param) {
        void *socket;
        if(param.size() > 1 && param[1].size() > 0)
            socket = new_socket(param[0].stringValue().c_str(), param[1].stringValue().c_str());
        else
            socket = new_socket(param[0].stringValue().c_str(), NULL);

        if(socket)
            set_handle(socket, true, "zsock");
        else
            throw Php::Exception("Internal Error: Can't create socket.");
    }

    void set_verbose (Php::Parameters &param) {
        _verbose = param.size() > 0 ? param[0].boolValue() : true;
    }

    void set_unbounded () {
        zsock_set_unbounded(zsock_handle());
    }

    Php::Value bind(Php::Parameters &param) {
        int result = zsock_bind(zsock_handle(), param[0].stringValue().c_str());
    //	if(_verbose)
    //		zsys_info("binded ep: %s [%d]", param[0].stringValue().c_str(), result);
        return (result == -1 ? false : (result == 0 ? true : result));
    }

    Php::Value unbind(Php::Parameters &param) {
        return (zsock_unbind(zsock_handle(), param[0].stringValue().c_str()) == 0);
    }

    Php::Value connect(Php::Parameters &param) {
        int result = zsock_connect(zsock_handle(), param[0].stringValue().c_str());
    //	if(_verbose)
    //    	zsys_info("connected ep: %s [%d]", param[0].stringValue().c_str(), result);
        return (result == 0);
    }

    Php::Value disconnect(Php::Parameters &param) {
        return (zsock_disconnect(zsock_handle(), param[0].stringValue().c_str()) == 0);
    }

    Php::Value attach(Php::Parameters &param) {
        bool serverish = param.size() > 1 ? param[1].boolValue() : false;
        return (zsock_attach(zsock_handle(), param[0].stringValue().c_str(), serverish) == 0);
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

    // Options

    Php::Value get_tos() {
        return zsock_tos(zsock_handle());
    }

    Php::Value get_zap_domain() {
        char *zap_domain = zsock_zap_domain(zsock_handle());
        Php::Value result = zap_domain;
        free(zap_domain);
        return result;
    }

    Php::Value get_mechanism() {
        return zsock_mechanism(zsock_handle());
    }

    Php::Value get_plain_server() {
        return zsock_plain_server(zsock_handle());
    }

    Php::Value get_plain_username() {
        char *plain_username = zsock_plain_username(zsock_handle());
        Php::Value result = plain_username;
        free(plain_username);
        return result;
    }

    Php::Value get_plain_password() {
        char *plain_password = zsock_plain_password(zsock_handle());
        Php::Value result = plain_password;
        free(plain_password);
        return result;
    }

    Php::Value get_curve_server() {
        return zsock_curve_server(zsock_handle());
    }

    Php::Value get_curve_publickey() {
        char *curve_publickey = zsock_curve_publickey(zsock_handle());
        Php::Value result = curve_publickey;
        free(curve_publickey);
        return result;
    }

    Php::Value get_curve_secretkey() {
        char *curve_secretkey = zsock_curve_secretkey(zsock_handle());
        Php::Value result = curve_secretkey;
        free(curve_secretkey);
        return result;
    }

    Php::Value get_curve_serverkey() {
        char *curve_serverkey = zsock_curve_serverkey(zsock_handle());
        Php::Value result = curve_serverkey;
        free(curve_serverkey);
        return result;
    }

    Php::Value get_gssapi_server() {
        return zsock_gssapi_server(zsock_handle());
    }

    Php::Value get_gssapi_plaintext() {
        return zsock_gssapi_plaintext(zsock_handle());
    }

    Php::Value get_gssapi_principal() {
        char *gssapi_principal = zsock_gssapi_principal(zsock_handle());
        Php::Value result = gssapi_principal;
        free(gssapi_principal);
        return result;
    }

    Php::Value get_gssapi_service_principal() {
        char *gssapi_service_principal = zsock_gssapi_service_principal(zsock_handle());
        Php::Value result = gssapi_service_principal;
        free(gssapi_service_principal);
        return result;
    }

    Php::Value get_ipv6() {
        return zsock_ipv6(zsock_handle());
    }

    Php::Value get_immediate() {
        return zsock_immediate(zsock_handle());
    }

    Php::Value get_ipv4only() {
        return zsock_ipv4only(zsock_handle());
    }

    Php::Value get_type() {
        zsys_info("get_type");
        int type = zsock_type(zsock_handle());
        zsys_info("get_type_end");
        return type;

    }

    Php::Value get_sndhwm() {
        return zsock_sndhwm(zsock_handle());
    }

    Php::Value get_rcvhwm() {
        return zsock_rcvhwm(zsock_handle());
    }

    Php::Value get_affinity() {
        return zsock_affinity(zsock_handle());
    }

    Php::Value get_identity() {
        char *identity = zsock_identity(zsock_handle());
        Php::Value result = identity;
        free(identity);
        return result;
    }

    Php::Value get_rate() {
        return zsock_rate(zsock_handle());
    }

    Php::Value get_recovery_ivl() {
        return zsock_recovery_ivl(zsock_handle());
    }

    Php::Value get_sndbuf() {
        return zsock_sndbuf(zsock_handle());
    }

    Php::Value get_rcvbuf() {
        return zsock_rcvbuf(zsock_handle());
    }

    Php::Value get_linger() {
        return zsock_linger(zsock_handle());
    }

    Php::Value get_reconnect_ivl() {
        return zsock_reconnect_ivl(zsock_handle());
    }

    Php::Value get_reconnect_ivl_max() {
        return zsock_reconnect_ivl_max(zsock_handle());
    }

    Php::Value get_backlog() {
        return zsock_backlog(zsock_handle());
    }

    Php::Value get_maxmsgsize() {
        return zsock_maxmsgsize(zsock_handle());
    }

    Php::Value get_multicast_hops() {
        return zsock_multicast_hops(zsock_handle());
    }

    Php::Value get_rcvtimeo() {
        return zsock_rcvtimeo(zsock_handle());
    }

    Php::Value get_sndtimeo() {
        return zsock_sndtimeo(zsock_handle());
    }

    Php::Value get_tcp_keepalive() {
        return zsock_tcp_keepalive(zsock_handle());
    }

    Php::Value get_tcp_keepalive_idle() {
        return zsock_tcp_keepalive_idle(zsock_handle());
    }

    Php::Value get_tcp_keepalive_cnt() {
        return zsock_tcp_keepalive_cnt(zsock_handle());
    }

    Php::Value get_tcp_keepalive_intvl() {
        return zsock_tcp_keepalive_intvl(zsock_handle());
    }

    Php::Value get_tcp_accept_filter() {
        char *tcp_accept_filter = zsock_tcp_accept_filter(zsock_handle());
        Php::Value result = tcp_accept_filter;
        free(tcp_accept_filter);
        return result;
    }

    Php::Value get_rcvmore() {
        return zsock_rcvmore(zsock_handle());
    }

    Php::Value get_events() {
        return zsock_events(zsock_handle());
    }

    Php::Value get_last_endpoint() {
        char *last_endpoint = zsock_last_endpoint(zsock_handle());
        Php::Value result = last_endpoint;
        free(last_endpoint);
        return result;
    }

    void set_tos(Php::Parameters &param) {
        zsock_set_tos(zsock_handle(), param[0].numericValue());
    }

    void set_router_handover(Php::Parameters &param) {
        zsock_set_router_handover(zsock_handle(), param[0].numericValue());
    }

    void set_router_mandatory(Php::Parameters &param) {
        zsock_set_router_mandatory(zsock_handle(), param[0].numericValue());
    }

    void set_probe_router(Php::Parameters &param) {
        zsock_set_probe_router(zsock_handle(), param[0].numericValue());
    }

    void set_req_relaxed(Php::Parameters &param) {
        zsock_set_req_relaxed(zsock_handle(), param[0].numericValue());
    }

    void set_req_correlate(Php::Parameters &param) {
        zsock_set_req_correlate(zsock_handle(), param[0].numericValue());
    }

    void set_conflate(Php::Parameters &param) {
        zsock_set_conflate(zsock_handle(), param[0].numericValue());
    }

    void set_zap_domain(Php::Parameters &param) {
        zsock_set_zap_domain(zsock_handle(), param[0].stringValue().c_str());
    }

    void set_plain_server(Php::Parameters &param) {
        zsock_set_plain_server(zsock_handle(), param[0].numericValue());
    }

    void set_plain_username(Php::Parameters &param) {
        zsock_set_plain_username(zsock_handle(), param[0].stringValue().c_str());
    }

    void set_plain_password(Php::Parameters &param) {
        zsock_set_plain_password(zsock_handle(), param[0].stringValue().c_str());
    }

    void set_curve_server(Php::Parameters &param) {
        zsock_set_curve_server(zsock_handle(), param[0].numericValue());
    }

    void set_curve_publickey(Php::Parameters &param) {
        zsock_set_curve_publickey(zsock_handle(), param[0].stringValue().c_str());
    }

    void set_curve_publickey_bin(Php::Parameters &param) {
        zsock_set_curve_publickey_bin(zsock_handle(), (byte *) param[0].rawValue());
    }

    void set_curve_secretkey(Php::Parameters &param) {
        zsock_set_curve_secretkey(zsock_handle(), param[0].stringValue().c_str());
    }

    void set_curve_secretkey_bin(Php::Parameters &param) {
        zsock_set_curve_secretkey_bin(zsock_handle(), (byte *) param[0].rawValue());
    }

    void set_curve_serverkey(Php::Parameters &param) {
        zsock_set_curve_serverkey(zsock_handle(), param[0].stringValue().c_str());
    }

    void set_curve_serverkey_bin(Php::Parameters &param) {
        zsock_set_curve_serverkey_bin(zsock_handle(), (byte *) param[0].rawValue());
    }

    void set_gssapi_server(Php::Parameters &param) {
        zsock_set_gssapi_server(zsock_handle(), param[0].numericValue());
    }

    void set_gssapi_plaintext(Php::Parameters &param) {
        zsock_set_gssapi_plaintext(zsock_handle(), param[0].numericValue());
    }

    void set_gssapi_principal(Php::Parameters &param) {
        zsock_set_gssapi_principal(zsock_handle(), param[0].stringValue().c_str());
    }

    void set_gssapi_service_principal(Php::Parameters &param) {
        zsock_set_gssapi_service_principal(zsock_handle(), param[0].stringValue().c_str());
    }

    void set_ipv6(Php::Parameters &param) {
        zsock_set_ipv6(zsock_handle(), param[0].numericValue());
    }

    void set_immediate(Php::Parameters &param) {
        zsock_set_immediate(zsock_handle(), param[0].numericValue());
    }

    void set_router_raw(Php::Parameters &param) {
        zsock_set_router_raw(zsock_handle(), param[0].numericValue());
    }

    void set_ipv4only(Php::Parameters &param) {
        zsock_set_ipv4only(zsock_handle(), param[0].numericValue());
    }

    void set_delay_attach_on_connect(Php::Parameters &param) {
        zsock_set_delay_attach_on_connect(zsock_handle(), param[0].numericValue());
    }

    void set_sndhwm(Php::Parameters &param) {
        zsock_set_sndhwm(zsock_handle(), param[0].numericValue());
    }

    void set_rcvhwm(Php::Parameters &param) {
        zsock_set_rcvhwm(zsock_handle(), param[0].numericValue());
    }

    void set_affinity(Php::Parameters &param) {
        zsock_set_affinity(zsock_handle(), param[0].numericValue());
    }

    void set_subscribe(Php::Parameters &param) {
        zsock_set_subscribe(zsock_handle(), param[0].stringValue().c_str());
    }

    void set_unsubscribe(Php::Parameters &param) {
        zsock_set_unsubscribe(zsock_handle(), param[0].stringValue().c_str());
    }

    void set_identity(Php::Parameters &param) {
        zsock_set_identity(zsock_handle(), param[0].stringValue().c_str());
    }

    void set_rate(Php::Parameters &param) {
        zsock_set_rate(zsock_handle(), param[0].numericValue());
    }

    void set_recovery_ivl(Php::Parameters &param) {
        zsock_set_recovery_ivl(zsock_handle(), param[0].numericValue());
    }

    void set_sndbuf(Php::Parameters &param) {
        zsock_set_sndbuf(zsock_handle(), param[0].numericValue());
    }

    void set_rcvbuf(Php::Parameters &param) {
        zsock_set_rcvbuf(zsock_handle(), param[0].numericValue());
    }

    void set_linger(Php::Parameters &param) {
        zsock_set_linger(zsock_handle(), param[0].numericValue());
    }

    void set_reconnect_ivl(Php::Parameters &param) {
        zsock_set_reconnect_ivl(zsock_handle(), param[0].numericValue());
    }

    void set_reconnect_ivl_max(Php::Parameters &param) {
        zsock_set_reconnect_ivl_max(zsock_handle(), param[0].numericValue());
    }

    void set_backlog(Php::Parameters &param) {
        zsock_set_backlog(zsock_handle(), param[0].numericValue());
    }

    void set_maxmsgsize(Php::Parameters &param) {
        zsock_set_maxmsgsize(zsock_handle(), param[0].numericValue());
    }

    void set_multicast_hops(Php::Parameters &param) {
        zsock_set_multicast_hops(zsock_handle(), param[0].numericValue());
    }

    void set_rcvtimeo(Php::Parameters &param) {
        zsock_set_rcvtimeo(zsock_handle(), param[0].numericValue());
    }

    void set_sndtimeo(Php::Parameters &param) {
        zsock_set_sndtimeo(zsock_handle(), param[0].numericValue());
    }

    void set_xpub_verbose(Php::Parameters &param) {
        zsock_set_xpub_verbose(zsock_handle(), param[0].numericValue());
    }

    void set_tcp_keepalive(Php::Parameters &param) {
        zsock_set_tcp_keepalive(zsock_handle(), param[0].numericValue());
    }

    void set_tcp_keepalive_idle(Php::Parameters &param) {
        zsock_set_tcp_keepalive_idle(zsock_handle(), param[0].numericValue());
    }

    void set_tcp_keepalive_cnt(Php::Parameters &param) {
        zsock_set_tcp_keepalive_cnt(zsock_handle(), param[0].numericValue());
    }

    void set_tcp_keepalive_intvl(Php::Parameters &param) {
        zsock_set_tcp_keepalive_intvl(zsock_handle(), param[0].numericValue());
    }

    void set_tcp_accept_filter(Php::Parameters &param) {
        zsock_set_tcp_accept_filter(zsock_handle(), param[0].stringValue().c_str());
    }

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
