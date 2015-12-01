
#include "../czmq/zmsg.h"

bool ZValue::isZMsg(void) { ZMsg  *zmsg = dynamic_cast<ZMsg *> (implementation()); return zmsg != nullptr; }
bool ZValue::isZFrame(void) { ZFrame  *zframe = dynamic_cast<ZFrame *> (implementation()); return zframe != nullptr; }

zmsg_t *ZValue::to_zmsg(void) {
    zmsg_t *zmsg = nullptr;

    if(isString()) {
        zmsg = zmsg_new ();
        zmsg_pushstr (zmsg, stringValue().c_str());
    }
    else
    if(isObject()) {
        ZMsg *zzmsg = dynamic_cast<ZMsg *>(implementation());
        if(zzmsg) {
            zmsg = zmsg_dup(zzmsg->zmsg_handle());
        } else {
            ZFrame *frame = dynamic_cast<ZFrame *>(implementation());
            if(frame) {
                zmsg = zmsg_new ();
                zmsg_pushmem (zmsg, zframe_data(frame->zframe_handle()), zframe_size(frame->zframe_handle()));
            }
        }
    }
    else
    if(isArray()) {
        zmsg = zmsg_new ();
        for (auto &iter : Php::Array(this)) {
            Php::Value item = iter.second;
            if(item.isString()) {
                zmsg_pushstr (zmsg, item.stringValue().c_str());
            }
            else
            if(item.isObject()) {
//                    zmsg_t *zmsg_dup = msg_from_object(&item);
//                    if(zmsg_dup)
//                        zmsg_addmsg(zmsg, &zmsg_dup);
            }
        }
    }

    return zmsg;
}

zmq_pollitem_t ZValue::to_pollitem(short event) {
    int fd = INVALID_SOCKET;
    if(isResource()) {
        TSRMLS_FETCH(); // we need the tsrm_ls variable
        php_stream *stream;
        php_stream_from_zval_no_verify(stream, &_val);
        if (stream) {
           if (php_stream_can_cast(stream, (PHP_STREAM_AS_FD | PHP_STREAM_CAST_INTERNAL | PHP_STREAM_AS_SOCKETD) & ~REPORT_ERRORS) == SUCCESS) {
               if (php_stream_cast(stream, (PHP_STREAM_AS_FD | PHP_STREAM_CAST_INTERNAL | PHP_STREAM_AS_SOCKETD) & ~REPORT_ERRORS, (void**) &fd, 0) == FAILURE) {
                   fd = INVALID_SOCKET;
               }
           }
        }
    }
    return zmq_pollitem_t ({ get_socket(), isResource() ? fd : get_fd(), event, 0 });
}