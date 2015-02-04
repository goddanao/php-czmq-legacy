#pragma once

#include <phpcpp.h>
#include <czmq.h>

class ZHandle : public Php::Base {
protected:
    void *_handle      = nullptr;
    int  _fd           = -1;
    bool _owned        = false;
    std::string _type  = "unknown";
public:
    ZHandle() : Php::Base() {}
    ZHandle(void *handle, bool owned, std::string type) : Php::Base() { set_handle(handle, owned, type); }
    virtual ~ZHandle();

    void set_handle(void *handle, bool owned, std::string type);

    void *get_handle() const;

    void *get_socket() const;

    Php::Value send(Php::Parameters &param);

    Php::Value recv(Php::Parameters &param);

    Php::Value send_string(Php::Parameters &param);

    Php::Value recv_string(Php::Parameters &param);

    Php::Value send_picture(Php::Parameters &param);

    Php::Value recv_picture(Php::Parameters &param);

    static Php::Class<ZHandle> php_register() {
        Php::Class<ZHandle> o("ZHandle");
        return o;
    }
};