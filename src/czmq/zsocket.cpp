#include "../../include/czmq/zsocket.h"

void ZSocket::__construct(Php::Parameters &param) {
	void *socket;
	if(param.size() > 1 && param[1].size() > 0)
		socket = ZSocket::new_socket(param[0].stringValue().c_str(), param[1].stringValue().c_str());
	else
		socket = ZSocket::new_socket(param[0].stringValue().c_str(), NULL);

	if(socket)
		set_handle(socket, true, "zsock");
	else
		throw Php::Exception("Internal Error: Can't create socket.");
}

void ZSocket::set_verbose (Php::Parameters &param) {
	_verbose = param.size() > 0 ? param[0].boolValue() : true;
}

void ZSocket::set_unbounded () {
	zsock_set_unbounded(zsock_handle());
}

zsock_t *ZSocket::new_socket(const char* name, const char* endpoint) {

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

		zsock_set_ipv6(sock, false);

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

Php::Value ZSocket::bind(Php::Parameters &param) {
	int result = zsock_bind(zsock_handle(), param[0].stringValue().c_str());
//	if(_verbose)
//		zsys_info("binded ep: %s [%d]", param[0].stringValue().c_str(), result);
	return (result == -1 ? false : (result == 0 ? true : result));
}

Php::Value ZSocket::unbind(Php::Parameters &param) {
	return (zsock_unbind(zsock_handle(), param[0].stringValue().c_str()) == 0);
}

Php::Value ZSocket::connect(Php::Parameters &param) {
	int result = zsock_connect(zsock_handle(), param[0].stringValue().c_str());
//	if(_verbose)
//    	zsys_info("connected ep: %s [%d]", param[0].stringValue().c_str(), result);
	return (result == 0);
}

Php::Value ZSocket::disconnect(Php::Parameters &param) {
	return (zsock_disconnect(zsock_handle(), param[0].stringValue().c_str()) == 0);
}

Php::Value ZSocket::attach(Php::Parameters &param) {
	bool serverish = param.size() > 1 ? param[1].boolValue() : false;
	return (zsock_attach(zsock_handle(), param[0].stringValue().c_str(), serverish) == 0);
}

Php::Value ZSocket::signal(Php::Parameters &param) {
    byte status = (uint8_t) param[0].numericValue();
	return (zsock_signal(zsock_handle(), status) == 0);
}

Php::Value ZSocket::wait() {
	return (zsock_wait(zsock_handle()) == 0);
}

void ZSocket::flush() {
	zsock_flush(zsock_handle());
}

/*
Php::Value ZSocket::send_picture(Php::Parameters &param) {
	zmsg_t *msg = zmsg_new();
	ZMsg z(msg, false);
	z.append_picture(param);
	return (zmsg_send (&msg, zsock_handle()) == 0);
}

Php::Value ZSocket::recv_picture(Php::Parameters &param) {
	zmsg_t *msg = zmsg_recv (zsock_handle());
	if(!msg)
		return nullptr;
	ZMsg z(msg, true);
	return z.pop_picture(param);
}

Php::Value ZSocket::send_string(Php::Parameters &param) {
	Php::Object self(this);
	return self.call("send_picture", "S", param[0].stringValue());
}

Php::Value ZSocket::recv_string(Php::Parameters &param) {
	Php::Object self(this);
	Php::Value result = self.call("recv_picture", "S");
	if(result.isArray())
	 	return result[0];
	return nullptr;
}

Php::Value ZSocket::send(Php::Parameters &param) {
	Php::Object self(this);
	return self.call("send_picture", "m", param[0]);
}

Php::Value ZSocket::recv(Php::Parameters &param) {
	Php::Object self(this);
	Php::Value result = self.call("recv_picture", "m");
	if(result.isArray())
	 	return result[0];
	return nullptr;
}

*/

// Options

Php::Value ZSocket::get_tos() {
	return zsock_tos(zsock_handle());
}

Php::Value ZSocket::get_zap_domain() {
	char *zap_domain = zsock_zap_domain(zsock_handle());
	Php::Value result = zap_domain;
	free(zap_domain);
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
	free(plain_username);
	return result;
}

Php::Value ZSocket::get_plain_password() {
	char *plain_password = zsock_plain_password(zsock_handle());
	Php::Value result = plain_password;
	free(plain_password);
	return result;
}

Php::Value ZSocket::get_curve_server() {
	return zsock_curve_server(zsock_handle());
}

Php::Value ZSocket::get_curve_publickey() {
	char *curve_publickey = zsock_curve_publickey(zsock_handle());
	Php::Value result = curve_publickey;
	free(curve_publickey);
	return result;
}

Php::Value ZSocket::get_curve_secretkey() {
	char *curve_secretkey = zsock_curve_secretkey(zsock_handle());
	Php::Value result = curve_secretkey;
	free(curve_secretkey);
	return result;
}

Php::Value ZSocket::get_curve_serverkey() {
	char *curve_serverkey = zsock_curve_serverkey(zsock_handle());
	Php::Value result = curve_serverkey;
	free(curve_serverkey);
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
	free(gssapi_principal);
	return result;
}

Php::Value ZSocket::get_gssapi_service_principal() {
	char *gssapi_service_principal = zsock_gssapi_service_principal(zsock_handle());
	Php::Value result = gssapi_service_principal;
	free(gssapi_service_principal);
	return result;
}

Php::Value ZSocket::get_ipv6() {
	return zsock_ipv6(zsock_handle());
}

Php::Value ZSocket::get_immediate() {
	return zsock_immediate(zsock_handle());
}

Php::Value ZSocket::get_ipv4only() {
	return zsock_ipv4only(zsock_handle());
}

Php::Value ZSocket::get_type() {
	zsys_info("get_type");
	int type = zsock_type(zsock_handle());
	zsys_info("get_type_end");
	return type;

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
	free(identity);
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
	free(tcp_accept_filter);
	return result;
}

Php::Value ZSocket::get_rcvmore() {
	return zsock_rcvmore(zsock_handle());
}

Php::Value ZSocket::get_events() {
	return zsock_events(zsock_handle());
}

Php::Value ZSocket::get_last_endpoint() {
	char *last_endpoint = zsock_last_endpoint(zsock_handle());
	Php::Value result = last_endpoint;
	free(last_endpoint);
	return result;
}

void ZSocket::set_tos(Php::Parameters &param) {
	zsock_set_tos(zsock_handle(), param[0].numericValue());
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

void ZSocket::set_zap_domain(Php::Parameters &param) {
	zsock_set_zap_domain(zsock_handle(), param[0].stringValue().c_str());
}

void ZSocket::set_plain_server(Php::Parameters &param) {
	zsock_set_plain_server(zsock_handle(), param[0].numericValue());
}

void ZSocket::set_plain_username(Php::Parameters &param) {
	zsock_set_plain_username(zsock_handle(), param[0].stringValue().c_str());
}

void ZSocket::set_plain_password(Php::Parameters &param) {
	zsock_set_plain_password(zsock_handle(), param[0].stringValue().c_str());
}

void ZSocket::set_curve_server(Php::Parameters &param) {
	zsock_set_curve_server(zsock_handle(), param[0].numericValue());
}

void ZSocket::set_curve_publickey(Php::Parameters &param) {
	zsock_set_curve_publickey(zsock_handle(), param[0].stringValue().c_str());
}

void ZSocket::set_curve_publickey_bin(Php::Parameters &param) {
	zsock_set_curve_publickey_bin(zsock_handle(), (byte *) param[0].rawValue());
}

void ZSocket::set_curve_secretkey(Php::Parameters &param) {
	zsock_set_curve_secretkey(zsock_handle(), param[0].stringValue().c_str());
}

void ZSocket::set_curve_secretkey_bin(Php::Parameters &param) {
	zsock_set_curve_secretkey_bin(zsock_handle(), (byte *) param[0].rawValue());
}

void ZSocket::set_curve_serverkey(Php::Parameters &param) {
	zsock_set_curve_serverkey(zsock_handle(), param[0].stringValue().c_str());
}

void ZSocket::set_curve_serverkey_bin(Php::Parameters &param) {
	zsock_set_curve_serverkey_bin(zsock_handle(), (byte *) param[0].rawValue());
}

void ZSocket::set_gssapi_server(Php::Parameters &param) {
	zsock_set_gssapi_server(zsock_handle(), param[0].numericValue());
}

void ZSocket::set_gssapi_plaintext(Php::Parameters &param) {
	zsock_set_gssapi_plaintext(zsock_handle(), param[0].numericValue());
}

void ZSocket::set_gssapi_principal(Php::Parameters &param) {
	zsock_set_gssapi_principal(zsock_handle(), param[0].stringValue().c_str());
}

void ZSocket::set_gssapi_service_principal(Php::Parameters &param) {
	zsock_set_gssapi_service_principal(zsock_handle(), param[0].stringValue().c_str());
}

void ZSocket::set_ipv6(Php::Parameters &param) {
	zsock_set_ipv6(zsock_handle(), param[0].numericValue());
}

void ZSocket::set_immediate(Php::Parameters &param) {
	zsock_set_immediate(zsock_handle(), param[0].numericValue());
}

void ZSocket::set_router_raw(Php::Parameters &param) {
	zsock_set_router_raw(zsock_handle(), param[0].numericValue());
}

void ZSocket::set_ipv4only(Php::Parameters &param) {
	zsock_set_ipv4only(zsock_handle(), param[0].numericValue());
}

void ZSocket::set_delay_attach_on_connect(Php::Parameters &param) {
	zsock_set_delay_attach_on_connect(zsock_handle(), param[0].numericValue());
}

void ZSocket::set_sndhwm(Php::Parameters &param) {
	zsock_set_sndhwm(zsock_handle(), param[0].numericValue());
}

void ZSocket::set_rcvhwm(Php::Parameters &param) {
	zsock_set_rcvhwm(zsock_handle(), param[0].numericValue());
}

void ZSocket::set_affinity(Php::Parameters &param) {
	zsock_set_affinity(zsock_handle(), param[0].numericValue());
}

void ZSocket::set_subscribe(Php::Parameters &param) {
	zsock_set_subscribe(zsock_handle(), param[0].stringValue().c_str());
}

void ZSocket::set_unsubscribe(Php::Parameters &param) {
	zsock_set_unsubscribe(zsock_handle(), param[0].stringValue().c_str());
}

void ZSocket::set_identity(Php::Parameters &param) {
	zsock_set_identity(zsock_handle(), param[0].stringValue().c_str());
}

void ZSocket::set_rate(Php::Parameters &param) {
	zsock_set_rate(zsock_handle(), param[0].numericValue());
}

void ZSocket::set_recovery_ivl(Php::Parameters &param) {
	zsock_set_recovery_ivl(zsock_handle(), param[0].numericValue());
}

void ZSocket::set_sndbuf(Php::Parameters &param) {
	zsock_set_sndbuf(zsock_handle(), param[0].numericValue());
}

void ZSocket::set_rcvbuf(Php::Parameters &param) {
	zsock_set_rcvbuf(zsock_handle(), param[0].numericValue());
}

void ZSocket::set_linger(Php::Parameters &param) {
	zsock_set_linger(zsock_handle(), param[0].numericValue());
}

void ZSocket::set_reconnect_ivl(Php::Parameters &param) {
	zsock_set_reconnect_ivl(zsock_handle(), param[0].numericValue());
}

void ZSocket::set_reconnect_ivl_max(Php::Parameters &param) {
	zsock_set_reconnect_ivl_max(zsock_handle(), param[0].numericValue());
}

void ZSocket::set_backlog(Php::Parameters &param) {
	zsock_set_backlog(zsock_handle(), param[0].numericValue());
}

void ZSocket::set_maxmsgsize(Php::Parameters &param) {
	zsock_set_maxmsgsize(zsock_handle(), param[0].numericValue());
}

void ZSocket::set_multicast_hops(Php::Parameters &param) {
	zsock_set_multicast_hops(zsock_handle(), param[0].numericValue());
}

void ZSocket::set_rcvtimeo(Php::Parameters &param) {
	zsock_set_rcvtimeo(zsock_handle(), param[0].numericValue());
}

void ZSocket::set_sndtimeo(Php::Parameters &param) {
	zsock_set_sndtimeo(zsock_handle(), param[0].numericValue());
}

void ZSocket::set_xpub_verbose(Php::Parameters &param) {
	zsock_set_xpub_verbose(zsock_handle(), param[0].numericValue());
}

void ZSocket::set_tcp_keepalive(Php::Parameters &param) {
	zsock_set_tcp_keepalive(zsock_handle(), param[0].numericValue());
}

void ZSocket::set_tcp_keepalive_idle(Php::Parameters &param) {
	zsock_set_tcp_keepalive_idle(zsock_handle(), param[0].numericValue());
}

void ZSocket::set_tcp_keepalive_cnt(Php::Parameters &param) {
	zsock_set_tcp_keepalive_cnt(zsock_handle(), param[0].numericValue());
}

void ZSocket::set_tcp_keepalive_intvl(Php::Parameters &param) {
	zsock_set_tcp_keepalive_intvl(zsock_handle(), param[0].numericValue());
}

void ZSocket::set_tcp_accept_filter(Php::Parameters &param) {
	zsock_set_tcp_accept_filter(zsock_handle(), param[0].stringValue().c_str());
}
