#pragma once

#include "zhandle.h"

class _PV : public Php::Value {
public:

    zmq_pollitem_t *get_pollitem(short event) {

        bool is_resource = (Z_TYPE_P(_val) == IS_RESOURCE);
        bool valid = is_resource || isObject() || isNumeric();

        if(valid) {

            int fd = INVALID_SOCKET;
            zsock_t *socket = NULL;

            if(valid && isObject()) {
                ZHandle  *zh = dynamic_cast<ZHandle *> (implementation());
                if(zh) {
                    socket = (zsock_t*) zh->get_socket();
                    if(socket == nullptr) {
                        fd = zh->get_fd();
                    }
                }
            }
            else
            if(valid && isNumeric()) {
                fd = numericValue();
            }
            else
            if(valid && is_resource) {
                php_stream *stream;
                php_stream_from_zval_no_verify(stream, &_val);

                if (stream) {
                    if (php_stream_can_cast(stream, (PHP_STREAM_AS_FD | PHP_STREAM_CAST_INTERNAL | PHP_STREAM_AS_SOCKETD) & ~REPORT_ERRORS) == SUCCESS) {
                        if (php_stream_cast(stream, (PHP_STREAM_AS_FD | PHP_STREAM_CAST_INTERNAL | PHP_STREAM_AS_SOCKETD) & ~REPORT_ERRORS, (void**) &fd, 0) == FAILURE) {
                            return nullptr;
                        }
                    }
                }
            }
            else {
                return nullptr;
            }

            if(socket == nullptr && fd == INVALID_SOCKET)
                return nullptr;

            // Pollitem
            zmq_pollitem_t *item = new zmq_pollitem_t ({ socket, fd, event, 0 });

            return item;
        }

    }


};