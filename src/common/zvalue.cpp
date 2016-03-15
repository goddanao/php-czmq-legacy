
#include <php.h>
#include <php_ini.h>
#include <zend_exceptions.h>
#include <zend_interfaces.h>
#include <zend_ini.h>
#include <zend_string.h>
#include <ext/standard/php_var.h>
#include <ext/standard/php_smart_str.h>
#include <ext/standard/php_incomplete_class.h>
#include "../czmq/zmsg.h"

// Php Globals Utils
void ZValue::ensure_global(void) {
    TSRMLS_FETCH();
    if(!EG(active_symbol_table)) {
        zend_rebuild_symbol_table(TSRMLS_C);
    }
}

std::string ZValue::get_class_name(void) {
    std::string result;
    if(isObject() && !isCallable()) {
        TSRMLS_FETCH();
        PHP_CLASS_ATTRIBUTES;
        PHP_SET_CLASS_ATTRIBUTES(_val);
        result = class_name;
        PHP_CLEANUP_CLASS_ATTRIBUTES();
    }
    return result;
}

bool ZValue::isResource(void) { return (Z_TYPE_P(_val) == IS_RESOURCE); }
bool ZValue::isZMsg(void) { ZMsg  *zmsg = dynamic_cast<ZMsg *> (implementation()); return zmsg != nullptr; }
bool ZValue::isZFrame(void) { ZFrame  *zframe = dynamic_cast<ZFrame *> (implementation()); return zframe != nullptr; }
bool ZValue::isHashMap(void) {

    int count = zend_hash_num_elements(Z_ARRVAL_P(_val));

    if (count != (Z_ARRVAL_P(_val))->nNextFreeElement) {
        return true;
    } else {
        int i;
        HashPosition pos = {0};
        zend_hash_internal_pointer_reset_ex(Z_ARRVAL_P(_val), &pos);
        for (i = 0; i < count; i++) {
            if (zend_hash_get_current_key_type_ex(Z_ARRVAL_P(_val), &pos) != HASH_KEY_IS_LONG) {
                return true;
            }
            zend_hash_move_forward_ex(Z_ARRVAL_P(_val), &pos);
        }
    }
    return false;
}

zmsg_t *ZValue::to_zmsg(void) {

    ZMsg *zzmsg = nullptr;
    if((zzmsg = dynamic_cast<ZMsg *>(implementation())) != nullptr)
        return zmsg_dup(zzmsg->zmsg_handle());

    zframe_t *frame = to_zframe();
    if(frame) {
        zmsg_t *msg = zmsg_new();
        zmsg_push(msg, frame);
        return msg;
    }

    return nullptr;
}

zframe_t *ZValue::to_zframe(void) {
    zframe_t *frame = nullptr;
    ZFrame *zzframe = nullptr;

    if(isScalar()) {
        std::string res = stringValue();
        frame = zframe_new (res.c_str(), res.size());
    }
    else
    if((zzframe = dynamic_cast<ZFrame *>(implementation())) != nullptr) {
        frame = zframe_dup(zzframe->zframe_handle());
    }
    else
    if(isCallable()) {
        zsys_info("Trying to serialize a closure ...");
        if(Php::class_exists("SuperClosure\\Serializer")) {
            zsys_info("SuperClosure\\Serializer FOUND!!");
            // Php::Value res = Php::eval("SuperClosure\\Serializer::serialize", Php::Value(_val));
        } else {
            zsys_info("SuperClosure\\Serializer NOT FOUND!!");
        }
    }
    else {
        Php::Value res = Php::call("serialize", Php::Value(_val));
        frame = zframe_new(res.rawValue(), res.size());
    }
    return frame;
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