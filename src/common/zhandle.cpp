#include "../czmq/zsocket.h"

Php::Value ZHandle::_get_fd () const {
    return get_fd();
}

Php::Value ZHandle::_get_socket () const {
    return Php::Object("ZSocket", new ZSocket((zsock_t *) get_socket(), false));
}
