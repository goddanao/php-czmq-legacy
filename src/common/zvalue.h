#pragma once

#include "zhandle.h"

class ZValue : public Php::Value {
public:

    bool isZHandle(void) { ZHandle  *zh = dynamic_cast<ZHandle *> (implementation()); return zh != nullptr; }
    bool isZMsg(void);
    bool isZFrame(void);

    bool isZDescriptor(void) { ZHandle  *zh = dynamic_cast<ZHandle *> (implementation()); return (zh != nullptr) && (zh->get_fd() != INVALID_SOCKET); }
    bool isZSocket(void) { ZHandle  *zh = dynamic_cast<ZHandle *> (implementation()); return (zh != nullptr) && (zh->get_socket() != nullptr); }

    bool isResource(void) { return (Z_TYPE_P(_val) == IS_RESOURCE); }

    zsock_t *get_socket(void) { ZHandle  *zh = dynamic_cast<ZHandle *> (implementation()); return (zh != nullptr) ? (zsock_t *) zh->get_socket() : nullptr; }
    int get_fd(void) { ZHandle  *zh = dynamic_cast<ZHandle *> (implementation()); return (zh != nullptr) ? zh->get_fd().numericValue() : INVALID_SOCKET; }

    zmq_pollitem_t to_pollitem(short event = 0);

    zmsg_t *to_zmsg(void);
};
