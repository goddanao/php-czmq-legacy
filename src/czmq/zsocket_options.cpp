#include "zsocket.h"

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
    return zsock_mechanism(zsock_handle());
}

Php::Value ZSocket::get_plain_server() {
    return zsock_plain_server(zsock_handle());
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
    return zsock_curve_server(zsock_handle());
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
    return zsock_gssapi_server(zsock_handle());
}

Php::Value ZSocket::get_gssapi_plaintext() {
    return zsock_gssapi_plaintext(zsock_handle());
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
    return zsock_ipv6(zsock_handle());
}

Php::Value ZSocket::get_immediate() {
    return zsock_immediate(zsock_handle());
}

#endif

Php::Value ZSocket::get_ipv4only() {
    return zsock_ipv4only(zsock_handle());
}

Php::Value ZSocket::get_type() {
    return zsock_type(zsock_handle());
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

    #if (ZMQ_VERSION >= ZMQ_MAKE_VERSION(4,2,0))

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
    return zsock_rcvmore(zsock_handle());
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

void ZSocket::set_router_handover(Php::Parameters &param) {
    zsock_set_router_handover(zsock_handle(), param[0].numericValue());
}

void ZSocket::set_router_mandatory(Php::Parameters &param) {
    zsock_set_router_mandatory(zsock_handle(), param[0].numericValue());
}

void ZSocket::set_probe_router(Php::Parameters &param) {
    zsock_set_probe_router(zsock_handle(), param[0].numericValue());
}

void ZSocket::set_req_relaxed(Php::Parameters &param) {
    zsock_set_req_relaxed(zsock_handle(), param[0].numericValue());
}

void ZSocket::set_req_correlate(Php::Parameters &param) {
    zsock_set_req_correlate(zsock_handle(), param[0].numericValue());
}

void ZSocket::set_conflate(Php::Parameters &param) {
    zsock_set_conflate(zsock_handle(), param[0].numericValue());
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

void ZSocket::set_curve_publickey_bin(Php::Parameters &param) {
    zsock_set_curve_publickey_bin(zsock_handle(), (byte *) param[0].rawValue());
}

void ZSocket::set_curve_secretkey(const Php::Value &value) {
    zsock_set_curve_secretkey(zsock_handle(), value.stringValue().c_str());
}

void ZSocket::set_curve_secretkey_bin(Php::Parameters &param) {
    zsock_set_curve_secretkey_bin(zsock_handle(), (byte *) param[0].rawValue());
}

void ZSocket::set_curve_serverkey(const Php::Value &value) {
    zsock_set_curve_serverkey(zsock_handle(), value.stringValue().c_str());
}

void ZSocket::set_curve_serverkey_bin(Php::Parameters &param) {
    zsock_set_curve_serverkey_bin(zsock_handle(), (byte *) param[0].rawValue());
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

#endif

void ZSocket::set_router_raw(Php::Parameters &param) {
    zsock_set_router_raw(zsock_handle(), param[0].numericValue());
}

void ZSocket::set_ipv4only(const Php::Value &value) {
    zsock_set_ipv4only(zsock_handle(), value.numericValue());
}

void ZSocket::set_delay_attach_on_connect(Php::Parameters &param) {
    zsock_set_delay_attach_on_connect(zsock_handle(), param[0].numericValue());
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

void ZSocket::set_xpub_verbose(Php::Parameters &param) {
    zsock_set_xpub_verbose(zsock_handle(), param[0].numericValue());
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