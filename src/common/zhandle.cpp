#include "../czmq/zsocket.h"

Php::Value ZHandle::_get_socket() {
    return Php::Object("ZSocket", new ZSocket((zsock_t*) get_socket(), false));
}

Php::Value ZHandle::send_picture(Php::Parameters &param) {
    zmsg_t *msg = zmsg_new();
    ZMsg z(msg, false);
    z.append_picture(param);
    return _send (msg);
}

Php::Value ZHandle::recv_picture(Php::Parameters &param) {
    zmsg_t *msg = _recv ();
    if(!msg)
        return nullptr;
    ZMsg z(msg, true);
    return z.pop_picture(param);
}

Php::Value ZHandle::send_string(Php::Parameters &param) {
    zmsg_t *msg = ZUtils::phpvalue_to_zmsg(param[0]);
    return _send(msg);
}

Php::Value ZHandle::recv_string(Php::Parameters &param) {
    zmsg_t *msg = _recv ();
    if(!msg)
        return nullptr;
    ZMsg z(msg, true);
    return z.pop_string();
}

Php::Value ZHandle::send(Php::Parameters &param) {
    zmsg_t *msg = ZUtils::params_to_zmsg(param);
    return _send(msg);
}

Php::Value ZHandle::recv(Php::Parameters &param) {
    zmsg_t *msg = _recv ();
    if(!msg)
        return nullptr;
    return Php::Object("ZMsg", new ZMsg(msg, true));
}

Php::Value ZHandle::send_msgpack(Php::Parameters &param) {
    Php::Value callback;
    Php::Value v = MsgPack::encode(param[0], callback);
    zmsg_t *msg = ZUtils::phpvalue_to_zmsg(v);
    return _send(msg);
}

Php::Value ZHandle::recv_msgpack(Php::Parameters &param) {
    zmsg_t *msg = _recv ();
    if(!msg)
        return nullptr;
    zframe_t *frame = zmsg_pop (msg);
    if(frame) {
        Php::Value buffer;
        int _buffer_size = zframe_size(frame);
        buffer.reserve(_buffer_size);
        const char *_buffer_to = buffer.rawValue();
        byte *_buffer_from = zframe_data(frame);
        memcpy((void *) _buffer_to, _buffer_from, _buffer_size);
        zframe_destroy (&frame);
        zmsg_destroy(&msg);
        Php::Value callback;
        return MsgPack::decode(buffer, callback);
    }
    zmsg_destroy(&msg);
    return nullptr;
}

Php::Value ZHandle::send_zipped(Php::Parameters &param) {
    Php::Value v = ZUtils::compress_string(param[0]);
    zmsg_t *msg = ZUtils::phpvalue_to_zmsg(v);
    return _send(msg);
}

Php::Value ZHandle::recv_zipped(Php::Parameters &param) {
    zmsg_t *msg = _recv ();
    if(!msg)
        return nullptr;

    zframe_t *frame = zmsg_pop (msg);
    if(frame) {
        Php::Value buffer;
        int _buffer_size = zframe_size(frame);
        buffer.reserve(_buffer_size);
        const char *_buffer_to = buffer.rawValue();
        byte *_buffer_from = zframe_data(frame);
        memcpy((void *) _buffer_to, _buffer_from, _buffer_size);
        zframe_destroy (&frame);
        zmsg_destroy(&msg);
        return ZUtils::decompress_string(buffer);
    }
    zmsg_destroy(&msg);
    return nullptr;
}