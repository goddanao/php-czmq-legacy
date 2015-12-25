#include "zsocket.h"


void ZSocket::set_options(Php::Parameters &param) {
    _set_options(zsock_handle(), param[0]);
}

void ZSocket::_set_options(zsock_t *socket, Php::Value &value) {
    for (auto &iter : value) {
        std::string key = ZUtils::toLower(iter.first.stringValue());

        #if (ZMQ_VERSION_MAJOR == 4)
            if(key == "tos") { zsock_set_tos(socket, iter.second.numericValue()); }
            else
            if(key == "router_handover") { zsock_set_router_handover(socket, iter.second.numericValue()); }
            else
            if(key == "router_mandatory") { zsock_set_router_mandatory(socket, iter.second.numericValue()); }
            else
            if(key == "probe_router") { zsock_set_probe_router(socket, iter.second.numericValue()); }
            else
            if(key == "req_relaxed") { zsock_set_req_relaxed(socket, iter.second.numericValue()); }
            else
            if(key == "req_correlate") { zsock_set_req_correlate(socket, iter.second.numericValue()); }
            else
            if(key == "conflate") { zsock_set_conflate(socket, iter.second.numericValue()); }
            else
            if(key == "zap_domain") { zsock_set_zap_domain(socket, iter.second.stringValue().c_str()); }
            else
            if(key == "plain_server") { zsock_set_plain_server(socket, iter.second.numericValue()); }
            else
            if(key == "plain_username") { zsock_set_plain_username(socket, iter.second.stringValue().c_str()); }
            else
            if(key == "plain_password") { zsock_set_plain_password(socket, iter.second.stringValue().c_str()); }
            else
            if(key == "curve_server") { zsock_set_curve_server(socket, iter.second.numericValue()); }
            else
            if(key == "curve_publickey") { zsock_set_curve_publickey(socket, iter.second.stringValue().c_str()); }
            else
            if(key == "curve_secretkey") { zsock_set_curve_secretkey(socket, iter.second.stringValue().c_str()); }
            else
            if(key == "curve_serverkey") { zsock_set_curve_serverkey(socket, iter.second.stringValue().c_str()); }
            else
            if(key == "gssapi_server") { zsock_set_gssapi_server(socket, iter.second.numericValue()); }
            else
            if(key == "gssapi_plaintext") { zsock_set_gssapi_plaintext(socket, iter.second.numericValue()); }
            else
            if(key == "gssapi_principal") { zsock_set_gssapi_principal(socket, iter.second.stringValue().c_str()); }
            else
            if(key == "gssapi_service_principal") { zsock_set_gssapi_service_principal(socket, iter.second.stringValue().c_str()); }
            else
            if(key == "ipv6") { zsock_set_ipv6(socket, iter.second.numericValue()); }
            else
            if(key == "immediate") { zsock_set_immediate(socket, iter.second.numericValue()); }
            else
            if(key == "connect_rid") {
                int ret = zmq_setsockopt (socket, ZMQ_CONNECT_RID, iter.second.rawValue(), iter.second.size());
                assert (0 == ret);
            }
            else
            if(key == "handshake_ivl") {
                int val = iter.second.numericValue();
                size_t sval = sizeof(val);
                int ret = zmq_setsockopt (socket, ZMQ_HANDSHAKE_IVL, &val, sval);
                assert (0 == ret);
            }
            else

        #endif

        if(key == "router_raw") { zsock_set_router_raw(socket, iter.second.numericValue()); }
        else
        if(key == "ipv4only") { zsock_set_ipv4only(socket, iter.second.numericValue()); }
        else
        if(key == "delay_attach_on_connect") { zsock_set_delay_attach_on_connect(socket, iter.second.numericValue()); }
        else
        if(key == "sndhwm") { zsock_set_sndhwm(socket, iter.second.numericValue()); }
        else
        if(key == "rcvhwm") { zsock_set_rcvhwm(socket, iter.second.numericValue()); }
        else
        if(key == "affinity") { zsock_set_affinity(socket, iter.second.numericValue()); }
        else
        if(key == "identity") { zsock_set_identity(socket, iter.second.stringValue().c_str()); }
        else
        if(key == "rate") { zsock_set_rate(socket, iter.second.numericValue()); }
        else
        if(key == "recovery_ivl") { zsock_set_recovery_ivl(socket, iter.second.numericValue()); }
        else
        if(key == "sndbuf") { zsock_set_sndbuf(socket, iter.second.numericValue()); }
        else
        if(key == "rcvbuf") { zsock_set_rcvbuf(socket, iter.second.numericValue()); }
        else
        if(key == "linger") { zsock_set_linger(socket, iter.second.numericValue()); }
        else
        if(key == "reconnect_ivl") { zsock_set_reconnect_ivl(socket, iter.second.numericValue()); }
        else
        if(key == "reconnect_ivl_max") { zsock_set_reconnect_ivl_max(socket, iter.second.numericValue()); }
        else
        if(key == "backlog") { zsock_set_backlog(socket, iter.second.numericValue()); }
        else
        if(key == "maxmsgsize") { zsock_set_maxmsgsize(socket, iter.second.numericValue()); }
        else
        if(key == "multicast_hops") { zsock_set_multicast_hops(socket, iter.second.numericValue()); }
        else
        if(key == "rcvtimeo") { zsock_set_rcvtimeo(socket, iter.second.numericValue()); }
        else
        if(key == "sndtimeo") { zsock_set_sndtimeo(socket, iter.second.numericValue()); }
        else
        if(key == "tcp_keepalive") { zsock_set_tcp_keepalive(socket, iter.second.numericValue()); }
        else
        if(key == "tcp_keepalive_idle") { zsock_set_tcp_keepalive_idle(socket, iter.second.numericValue()); }
        else
        if(key == "tcp_keepalive_cnt") { zsock_set_tcp_keepalive_cnt(socket, iter.second.numericValue()); }
        else
        if(key == "tcp_keepalive_intvl") { zsock_set_tcp_keepalive_intvl(socket, iter.second.numericValue()); }
        else
        if(key == "tcp_accept_filter") { zsock_set_tcp_accept_filter(socket, iter.second.stringValue().c_str()); }
        else
        if(key == "xpub_verbose") { zsock_set_xpub_verbose(socket, iter.second.numericValue()); }

    }

}

Php::Value ZSocket::get_options() {
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
        // result["handshake_ivl"] = get_handshake_ivl();
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



#if (ZMQ_VERSION_MAJOR == 4)

Php::Value ZSocket::get_tos() {
    return zsock_tos(zsock_handle());
}

Php::Value ZSocket::get_zap_domain() {
    char *zap_domain = zsock_zap_domain(zsock_handle());
    Php::Value result = zap_domain;
    zstr_free(&zap_domain);
    return result;
}

Php::Value ZSocket::get_mechanism() {
    switch(zsock_mechanism(zsock_handle())) {
        case ZMQ_NULL : return "null";
        case ZMQ_PLAIN: return "plain";
        case ZMQ_CURVE: return "curve";
        case ZMQ_GSSAPI: return "gssapi";
    }
    return "unknown";
}

Php::Value ZSocket::get_plain_server() {
    return zsock_plain_server(zsock_handle()) == 1;
}

Php::Value ZSocket::get_plain_username() {
    char *plain_username = zsock_plain_username(zsock_handle());
    Php::Value result = plain_username;
    zstr_free(&plain_username);
    return result;
}

Php::Value ZSocket::get_plain_password() {
    char *plain_password = zsock_plain_password(zsock_handle());
    Php::Value result = plain_password;
    zstr_free(&plain_password);
    return result;
}

Php::Value ZSocket::get_curve_server() {
    return zsock_curve_server(zsock_handle()) == 1;
}

Php::Value ZSocket::get_curve_publickey() {
    char *curve_publickey = zsock_curve_publickey(zsock_handle());
    Php::Value result = curve_publickey;
    zstr_free(&curve_publickey);
    return result;
}

Php::Value ZSocket::get_curve_secretkey() {
    char *curve_secretkey = zsock_curve_secretkey(zsock_handle());
    Php::Value result = curve_secretkey;
    zstr_free(&curve_secretkey);
    return result;
}

Php::Value ZSocket::get_curve_serverkey() {
    char *curve_serverkey = zsock_curve_serverkey(zsock_handle());
    Php::Value result = curve_serverkey;
    zstr_free(&curve_serverkey);
    return result;
}

Php::Value ZSocket::get_gssapi_server() {
    return zsock_gssapi_server(zsock_handle()) == 1;
}

Php::Value ZSocket::get_gssapi_plaintext() {
    return zsock_gssapi_plaintext(zsock_handle()) == 1;
}

Php::Value ZSocket::get_gssapi_principal() {
    char *gssapi_principal = zsock_gssapi_principal(zsock_handle());
    Php::Value result = gssapi_principal;
    zstr_free(&gssapi_principal);
    return result;
}

Php::Value ZSocket::get_gssapi_service_principal() {
    char *gssapi_service_principal = zsock_gssapi_service_principal(zsock_handle());
    Php::Value result = gssapi_service_principal;
    zstr_free(&gssapi_service_principal);
    return result;
}

Php::Value ZSocket::get_ipv6() {
    return zsock_ipv6(zsock_handle()) == 1;
}

Php::Value ZSocket::get_immediate() {
    return zsock_immediate(zsock_handle()) == 1;
}

Php::Value ZSocket::get_handshake_ivl() {
    int val;
    size_t sval = sizeof(val);
    int ret = zmq_getsockopt (zsock_handle(), ZMQ_HANDSHAKE_IVL, &val, &sval);
    assert (0 == ret);
    return val;
}


#endif

Php::Value ZSocket::get_ipv4only() {
    return zsock_ipv4only(zsock_handle()) == 1;
}

Php::Value ZSocket::get_socket_type() {
    switch(zsock_type(zsock_handle())) {
        case ZMQ_PUB : return "pub";
        case ZMQ_SUB : return "sub";
        case ZMQ_REQ : return "req";
        case ZMQ_REP : return "rep";
        case ZMQ_DEALER : return "dealer";
        case ZMQ_ROUTER : return "router";
        case ZMQ_PUSH : return "push";
        case ZMQ_PULL : return "pull";
        case ZMQ_XPUB : return "xpub";
        case ZMQ_XSUB : return "xsub";
        case ZMQ_PAIR : return "pair";
        case ZMQ_STREAM : return "stream";

    #ifdef ZMQ_SERVER

        case ZMQ_SERVER : return "server";
        case ZMQ_CLIENT : return "client";

    #endif

        default:
            return nullptr;
    };
}


Php::Value ZSocket::get_sndhwm() {
    return zsock_sndhwm(zsock_handle());
}

Php::Value ZSocket::get_rcvhwm() {
    return zsock_rcvhwm(zsock_handle());
}

Php::Value ZSocket::get_affinity() {
    return zsock_affinity(zsock_handle());
}

Php::Value ZSocket::get_identity() {
    char *identity = zsock_identity(zsock_handle());
    Php::Value result = identity;
    zstr_free(&identity);
    return result;
}

Php::Value ZSocket::get_rate() {
    return zsock_rate(zsock_handle());
}

Php::Value ZSocket::get_recovery_ivl() {
    return zsock_recovery_ivl(zsock_handle());
}

Php::Value ZSocket::get_sndbuf() {
    return zsock_sndbuf(zsock_handle());
}

Php::Value ZSocket::get_rcvbuf() {
    return zsock_rcvbuf(zsock_handle());
}

Php::Value ZSocket::get_linger() {
    return zsock_linger(zsock_handle());
}

Php::Value ZSocket::get_reconnect_ivl() {
    return zsock_reconnect_ivl(zsock_handle());
}

Php::Value ZSocket::get_reconnect_ivl_max() {
    return zsock_reconnect_ivl_max(zsock_handle());
}

Php::Value ZSocket::get_backlog() {
    return zsock_backlog(zsock_handle());
}

Php::Value ZSocket::get_maxmsgsize() {
    return zsock_maxmsgsize(zsock_handle());
}

Php::Value ZSocket::get_multicast_hops() {
    return zsock_multicast_hops(zsock_handle());
}

Php::Value ZSocket::get_rcvtimeo() {
    return zsock_rcvtimeo(zsock_handle());
}

Php::Value ZSocket::get_sndtimeo() {
    return zsock_sndtimeo(zsock_handle());
}

Php::Value ZSocket::get_tcp_keepalive() {
    return zsock_tcp_keepalive(zsock_handle());
}

Php::Value ZSocket::get_tcp_keepalive_idle() {
    return zsock_tcp_keepalive_idle(zsock_handle());
}

Php::Value ZSocket::get_tcp_keepalive_cnt() {
    return zsock_tcp_keepalive_cnt(zsock_handle());
}

Php::Value ZSocket::get_tcp_keepalive_intvl() {
    return zsock_tcp_keepalive_intvl(zsock_handle());
}

Php::Value ZSocket::get_tcp_accept_filter() {
    char *tcp_accept_filter = zsock_tcp_accept_filter(zsock_handle());
    Php::Value result = tcp_accept_filter;
    zstr_free(&tcp_accept_filter);
    return result;
}

Php::Value ZSocket::get_rcvmore() {
    return zsock_rcvmore(zsock_handle()) == 1;
}

Php::Value ZSocket::get_fd() {
    return zsock_fd(zsock_handle());
}

Php::Value ZSocket::get_events() {
    return zsock_events(zsock_handle());
}

Php::Value ZSocket::get_last_endpoint() {
    char *last_endpoint = zsock_last_endpoint(zsock_handle());
    Php::Value result = last_endpoint;
    zstr_free(&last_endpoint);
    return result;
}

// Set Socket Options

#if (ZMQ_VERSION_MAJOR == 4)

void ZSocket::set_tos(const Php::Value &value) {
    zsock_set_tos(zsock_handle(), value.numericValue());
}

void ZSocket::set_router_handover(const Php::Value &value) {
    zsock_set_router_handover(zsock_handle(), value.numericValue());
}

void ZSocket::set_router_mandatory(const Php::Value &value) {
    zsock_set_router_mandatory(zsock_handle(), value.numericValue());
}

void ZSocket::set_probe_router(const Php::Value &value) {
    zsock_set_probe_router(zsock_handle(), value.numericValue());
}

void ZSocket::set_req_relaxed(const Php::Value &value) {
    zsock_set_req_relaxed(zsock_handle(), value.numericValue());
}

void ZSocket::set_req_correlate(const Php::Value &value) {
    zsock_set_req_correlate(zsock_handle(), value.numericValue());
}

void ZSocket::set_conflate(const Php::Value &value) {
    zsock_set_conflate(zsock_handle(), value.numericValue());
}

void ZSocket::set_zap_domain(const Php::Value &value) {
    zsock_set_zap_domain(zsock_handle(), value.stringValue().c_str());
}

void ZSocket::set_plain_server(const Php::Value &value) {
    zsock_set_plain_server(zsock_handle(), value.numericValue());
}

void ZSocket::set_plain_username(const Php::Value &value) {
    zsock_set_plain_username(zsock_handle(), value.stringValue().c_str());
}

void ZSocket::set_plain_password(const Php::Value &value) {
    zsock_set_plain_password(zsock_handle(), value.stringValue().c_str());
}

void ZSocket::set_curve_server(const Php::Value &value) {
    zsock_set_curve_server(zsock_handle(), value.numericValue());
}

void ZSocket::set_curve_publickey(const Php::Value &value) {
    zsock_set_curve_publickey(zsock_handle(), value.stringValue().c_str());
}

void ZSocket::set_curve_secretkey(const Php::Value &value) {
    zsock_set_curve_secretkey(zsock_handle(), value.stringValue().c_str());
}

void ZSocket::set_curve_serverkey(const Php::Value &value) {
    zsock_set_curve_serverkey(zsock_handle(), value.stringValue().c_str());
}

void ZSocket::set_gssapi_server(const Php::Value &value) {
    zsock_set_gssapi_server(zsock_handle(), value.numericValue());
}

void ZSocket::set_gssapi_plaintext(const Php::Value &value) {
    zsock_set_gssapi_plaintext(zsock_handle(), value.numericValue());
}

void ZSocket::set_gssapi_principal(const Php::Value &value) {
    zsock_set_gssapi_principal(zsock_handle(), value.stringValue().c_str());
}

void ZSocket::set_gssapi_service_principal(const Php::Value &value) {
    zsock_set_gssapi_service_principal(zsock_handle(), value.stringValue().c_str());
}

void ZSocket::set_ipv6(const Php::Value &value) {
    zsock_set_ipv6(zsock_handle(), value.numericValue());
}

void ZSocket::set_immediate(const Php::Value &value) {
    zsock_set_immediate(zsock_handle(), value.numericValue());
}


void ZSocket::set_connect_rid(const Php::Value &value) {
    int ret = zmq_setsockopt (zsock_handle(), ZMQ_CONNECT_RID, value.rawValue(), value.size());
    assert (0 == ret);
}

void ZSocket::set_handshake_ivl(const Php::Value &value) {
    int val = value.numericValue();
    size_t sval = sizeof(val);
    int ret = zmq_setsockopt (zsock_handle(), ZMQ_HANDSHAKE_IVL, &val, sval);
    assert (0 == ret);
}

#endif

void ZSocket::set_router_raw(const Php::Value &value) {
    zsock_set_router_raw(zsock_handle(), value.numericValue());
}

void ZSocket::set_ipv4only(const Php::Value &value) {
    zsock_set_ipv4only(zsock_handle(), value.numericValue());
}

void ZSocket::set_delay_attach_on_connect(const Php::Value &value) {
    zsock_set_delay_attach_on_connect(zsock_handle(), value.numericValue());
}

void ZSocket::set_sndhwm(const Php::Value &value) {
    zsock_set_sndhwm(zsock_handle(), value.numericValue());
}

void ZSocket::set_rcvhwm(const Php::Value &value) {
    zsock_set_rcvhwm(zsock_handle(), value.numericValue());
}

void ZSocket::set_affinity(const Php::Value &value) {
    zsock_set_affinity(zsock_handle(), value.numericValue());
}

void ZSocket::set_subscribe(Php::Parameters &param) {
    zsock_set_subscribe(zsock_handle(), param[0].stringValue().c_str());
}

void ZSocket::set_unsubscribe(Php::Parameters &param) {
    zsock_set_unsubscribe(zsock_handle(), param[0].stringValue().c_str());
}

void ZSocket::set_identity(const Php::Value &value) {
    zsock_set_identity(zsock_handle(), value.stringValue().c_str());
}

void ZSocket::set_rate(const Php::Value &value) {
    zsock_set_rate(zsock_handle(), value.numericValue());
}

void ZSocket::set_recovery_ivl(const Php::Value &value) {
    zsock_set_recovery_ivl(zsock_handle(), value.numericValue());
}

void ZSocket::set_sndbuf(const Php::Value &value) {
    zsock_set_sndbuf(zsock_handle(), value.numericValue());
}

void ZSocket::set_rcvbuf(const Php::Value &value) {
    zsock_set_rcvbuf(zsock_handle(), value.numericValue());
}

void ZSocket::set_linger(const Php::Value &value) {
    zsock_set_linger(zsock_handle(), value.numericValue());
}

void ZSocket::set_reconnect_ivl(const Php::Value &value) {
    zsock_set_reconnect_ivl(zsock_handle(), value.numericValue());
}

void ZSocket::set_reconnect_ivl_max(const Php::Value &value) {
    zsock_set_reconnect_ivl_max(zsock_handle(), value.numericValue());
}

void ZSocket::set_backlog(const Php::Value &value) {
    zsock_set_backlog(zsock_handle(), value.numericValue());
}

void ZSocket::set_maxmsgsize(const Php::Value &value) {
    zsock_set_maxmsgsize(zsock_handle(), value.numericValue());
}

void ZSocket::set_multicast_hops(const Php::Value &value) {
    zsock_set_multicast_hops(zsock_handle(), value.numericValue());
}

void ZSocket::set_rcvtimeo(const Php::Value &value) {
    zsock_set_rcvtimeo(zsock_handle(), value.numericValue());
}

void ZSocket::set_sndtimeo(const Php::Value &value) {
    zsock_set_sndtimeo(zsock_handle(), value.numericValue());
}

void ZSocket::set_xpub_verbose(const Php::Value &value) {
    zsock_set_xpub_verbose(zsock_handle(), value.numericValue());
}

void ZSocket::set_tcp_keepalive(const Php::Value &value) {
    zsock_set_tcp_keepalive(zsock_handle(), value.numericValue());
}

void ZSocket::set_tcp_keepalive_idle(const Php::Value &value) {
    zsock_set_tcp_keepalive_idle(zsock_handle(), value.numericValue());
}

void ZSocket::set_tcp_keepalive_cnt(const Php::Value &value) {
    zsock_set_tcp_keepalive_cnt(zsock_handle(), value.numericValue());
}

void ZSocket::set_tcp_keepalive_intvl(const Php::Value &value) {
    zsock_set_tcp_keepalive_intvl(zsock_handle(), value.numericValue());
}

void ZSocket::set_tcp_accept_filter(const Php::Value &value) {
    zsock_set_tcp_accept_filter(zsock_handle(), value.stringValue().c_str());
}