#pragma once

#include <phpcpp.h>
#include <iostream>
#include <czmq.h>

class ZCertStore : public Php::Base {
private:
    zcertstore_t *store;

public:

    ZCertStore();

    virtual ~ZCertStore();

    void __construct(Php::Parameters &param);

    Php::Value lookup (Php::Parameters &param);

    void insert(Php::Parameters &param);

    void dump();

};
