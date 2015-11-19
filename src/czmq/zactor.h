#pragma once

#include "zmsg.h"

class ZActor  : public ZHandle {
public:
    ZActor() : ZHandle() {}
    ZActor(zactor_t *handle, bool owned) : ZHandle(handle, owned, "zactor") {}
    zactor_t *zactor_handle() const { return (zactor_t *) get_handle(); }

};
