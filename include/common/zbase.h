#pragma once

#include <phpcpp.h>
#include <czmq.h>

class ZBase : public Php::Base {
protected:
    void *handle      = nullptr;
    bool owned        = false;
    std::string type  = "";

    virtual void do_destroy() {}

public:
    virtual ~ZBase() { do_destroy(); }

};

class ZBaseSocket : public ZBase {

};

class ZBaseActor : public ZBaseSocket {
protected:
    ZBaseActor(void *_handle, bool _owned) : ZBaseSocket() { handle = _handle; owned = _owned; type = "zactor"; }
    void do_destroy() override { if(owned && handle && (handle != nullptr)) zactor_destroy((zactor_t**) &handle); }
};

