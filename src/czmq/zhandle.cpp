#include "../../include/czmq/zhandle.h"
#include "../../include/czmq/zhash.h"
#include "../../include/czmq/zframe.h"
#include "../../include/czmq/zchunk.h"
#include "../../include/czmq/zmsg.h"

ZHandle::~ZHandle() {
    if(!_owned || _handle == nullptr || _handle == NULL)
        return;
//        if(_type == "zcontext")
//            zcontext_destroy((zcontext_t **) &_handle);
//        else
    if(_type == "zactor" && zactor_is(_handle))
        zactor_destroy((zactor_t **) &_handle);
    else
    if(_type == "zsock" && zsock_is(_handle))
        zsock_destroy((zsock_t **) &_handle);
    else
    if(_type == "zsocket")
        zsys_close(_handle, NULL, 0);
    else
    if(_type == "zcert")
        zcert_destroy((zcert_t **) &_handle);
    else
    if(_type == "zframe" && zframe_is(_handle))
        zframe_destroy((zframe_t **) &_handle);
    else
    if(_type == "zmsg" && zmsg_is(_handle))
        zmsg_destroy((zmsg_t **) &_handle);
    else
    if(_type == "zhash")
        zhash_destroy((zhash_t **) &_handle);
    else
    if(_type == "zchunk" && zchunk_is(_handle))
        zchunk_destroy((zchunk_t **) &_handle);
    else
    if(_type == "zcertstore")
        zcertstore_destroy((zcertstore_t **) &_handle);
    else
    if(_type == "zloop")
        zloop_destroy((zloop_t **) &_handle);
    else
    if(_type == "zudp") {
        SOCKET *socket = (SOCKET *) _handle;
        SOCKET s = *socket;
        zsys_udp_close( s );
    }
    else
    if(_type == "zyre")
        zyre_destroy((zyre_t **) &_handle);
    else
    if(_type == "zpoller")
        zpoller_destroy((zpoller_t **) &_handle);
    else
    if(_type == "malamute_client")
        mlm_client_destroy ((mlm_client_t **) &_handle);
    else
        ;
    _handle = nullptr;
}


void ZHandle::set_handle(void *handle, bool owned, std::string type) {
    _handle = handle;
    _owned = owned;
    _type  = type;
}

void *ZHandle::get_handle() const { return _handle; }

void *ZHandle::get_socket() const {
    if(_type == "socket")
        return _handle;
    if(_type == "zsock")
        return (void *) zsock_resolve(_handle);
    if(_type == "zactor")
        return (void *) zactor_resolve(_handle);
    if(_type == "zyre")
        return (void *) zyre_socket((zyre_t*)_handle);
    return nullptr;
}

Php::Value ZHandle::send_picture(Php::Parameters &param) {
	zmsg_t *msg = zmsg_new();
	ZMsg z(msg, false);
	z.append_picture(param);
	return (zmsg_send (&msg, get_socket()) == 0);
}

Php::Value ZHandle::recv_picture(Php::Parameters &param) {
	zmsg_t *msg = zmsg_recv (get_socket());
	if(!msg)
		return nullptr;
	ZMsg z(msg, true);
	return z.pop_picture(param);
}

Php::Value ZHandle::send_string(Php::Parameters &param) {
	Php::Object self(this);
	std::string value = param[0].stringValue();
	return self.call("send_picture", "S", value);
}

Php::Value ZHandle::recv_string(Php::Parameters &param) {
	Php::Object self(this);
	Php::Value result = self.call("recv_picture", "S");
	if(result.isArray())
	 	return result[0];
	return nullptr;
}

Php::Value ZHandle::send(Php::Parameters &param) {
	Php::Object self(this);
	return self.call("send_picture", "m", param[0]);
}

Php::Value ZHandle::recv(Php::Parameters &param) {
	Php::Object self(this);
	Php::Value result = self.call("recv_picture", "m");
	if(result.isArray())
	 	return result[0];
	return nullptr;
}