
#include <php.h>
#include <php_ini.h>
#include <zend_exceptions.h>
#include <zend_interfaces.h>
#include <zend_ini.h>
#include <ext/standard/php_smart_str.h>
#include <ext/standard/php_incomplete_class.h>
#include <ext/standard/php_var.h>
#include "../czmq/zmsg.h"


std::string ZValue::serialize() {
    std::string result = NULL;
    zval *retval_ptr = NULL;
    zval fname;
    int res;
    zend_class_entry *ce = NULL;

    HashTable* var_hash; // ??

    TSRMLS_FETCH();

    if (Z_OBJ_HT_P(_val)->get_class_entry)
        ce = Z_OBJCE_P(_val);

    // Object has a custom serializer? Use it ..
    #if (PHP_MAJOR_VERSION == 5 && PHP_MINOR_VERSION > 0)
        if (ce && ce->serialize != NULL) {
            unsigned char *serialized_data = NULL;
            zend_uint serialized_length;
            if (ce->serialize(_val, &serialized_data, &serialized_length, (zend_serialize_data *) var_hash TSRMLS_CC) == SUCCESS && !EG(exception))
                result = std::string((const char *) serialized_data, serialized_length);
            if (serialized_data)
                efree(serialized_data);
        }
    #endif

    return result;
}

std::string ZValue::get_class_name(void) {
    std::string result;
    if(isObject()) {
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
        return 1;
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
    zmsg_t *zmsg = nullptr;

    if(isString()) {
        zmsg = zmsg_new ();
        // zmsg_pushstr (zmsg, stringValue().c_str());
        zmsg_pushmem (zmsg, rawValue(), size());
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
                zmsg_pushmem (zmsg, item.rawValue(), item.size());
                // zmsg_pushstr (zmsg, item.stringValue().c_str());
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