#pragma once

#include "../../common.h"

class TitanicStorage {
public:

    virtual zmsg_t *read_request(const char *uuid) = 0;

    virtual void store_request(const char *uuid, zmsg_t *msg) = 0;

    virtual const char *status(const char *uuid)= 0;

    virtual zmsg_t *read_response(const char *uuid) = 0;

    virtual void store_response(const char *uuid, zmsg_t *msg) = 0;

    virtual void close(const char *uuid) = 0;

    virtual char *process() = 0;
};