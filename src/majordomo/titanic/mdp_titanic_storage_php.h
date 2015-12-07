#pragma once

#include "mdp_titanic_storage.h"

class PhpCallbackStorage : public TitanicStorage {
private:
    Php::Value _object;
public:

    PhpCallbackStorage(Php::Value v) : _object(v) {}

    zmsg_t *read_request(const char *uuid) {
        zmsg_t *result;
        Php::Value res = _object.call("read", "request", uuid);
        if(!res.isNull()) {
            result = ZUtils::phpvalue_to_zmsg(res);
        }
        return result;
    }

    void store_request(const char *uuid, zmsg_t *msg) {
        _object.call("store", "request", uuid, Php::Object("ZMsg", new ZMsg(zmsg_dup(msg), true)));
    }

    const char * status(const char *uuid) {
        return _object.call("status", uuid);
    }

    zmsg_t *read_response(const char *uuid) {
        zmsg_t *result;
        Php::Value res = _object.call("read", "response", uuid);
        if(!res.isNull()) {
            result = ZUtils::phpvalue_to_zmsg(res);
        }
        return result;
    }

    void store_response(const char *uuid, zmsg_t *msg) {
        _object.call("store", "response", uuid, Php::Object("ZMsg", new ZMsg(zmsg_dup(msg), true)));
    }

    void close(const char *uuid) {
        _object.call("close", uuid);
    }

    char *process() {
        char *result = nullptr;
        Php::Value res = _object.call("process");
        if(!res.isNull()) {
            result = strdup(res.stringValue().c_str());
        }
        return result;
    }
};