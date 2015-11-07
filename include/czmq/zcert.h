#pragma once

#include "../common.h"
#include "zsocket.h"

class ZCert : public ZHandle, public Php::Base  {
private:
    bool _verbose;
public:
    ZCert() : ZHandle(), Php::Base() {}
    ZCert(zcert_t *handle, bool owned) : ZHandle(handle, owned, "zcert"), Php::Base() {}
    zcert_t *zcert_handle() const { return (zcert_t *) get_handle(); }


    void __construct(Php::Parameters &param) {
        if(param.size() == 0)
            set_handle(zcert_new (), true, "zcert");
        else
            set_handle(zcert_load(param[0].stringValue().c_str()), true, "zcert");
    }

    Php::Value get_public_key() {
        Php::Value result;
        char *buffer  = result.reserve(32);
        byte *pubcert = zcert_public_key(zcert_handle());
        memcpy(buffer, pubcert, 32);
        return result;
    }

    Php::Value get_secret_key() {
        Php::Value result;
        char *buffer  = result.reserve(32);
        byte *pubcert = zcert_secret_key(zcert_handle());
        memcpy(buffer, pubcert, 32);
        return result;
    }

    Php::Value get_public_key_txt() {
        return zcert_public_txt(zcert_handle());
    }

    Php::Value get_secret_key_txt() {
        return zcert_secret_txt(zcert_handle());
    }

    void set_meta(Php::Parameters &param) {
         zcert_set_meta(zcert_handle(), param[0].stringValue().c_str(), param[1].stringValue().c_str());
    }

    Php::Value get_meta(Php::Parameters &param) {
         return zcert_meta(zcert_handle(), param[0].stringValue().c_str());
    }

    Php::Value get_meta_keys() {
        Php::Value result;
        zlist_t *meta_keys = zcert_meta_keys(zcert_handle());
        if(!meta_keys)
            return Php::Array();
        char *meta_key = (char *) zlist_first(meta_keys);
        int result_idx = 0;
        while (meta_key) {
            result[result_idx++] = meta_key;
            meta_key = (char *) zlist_next(meta_keys);
        }
        zlist_destroy(&meta_keys);
        return result;
    }

    void save(Php::Parameters &param) {
        zcert_save(zcert_handle(), param[0].stringValue().c_str());
    }

    void save_public(Php::Parameters &param) {
        zcert_save_public(zcert_handle(), param[0].stringValue().c_str());
    }

    void save_secret(Php::Parameters &param) {
        zcert_save_secret(zcert_handle(), param[0].stringValue().c_str());
    }

    void apply(Php::Parameters &param) {
        if(param[0].isObject()) {
            ZHandle *zhandle = dynamic_cast<ZHandle*>(param[0].implementation());
            if(zhandle && zhandle->get_socket())
                zcert_apply(zcert_handle(), zhandle->get_socket());
        }
    }

    void dump() {
        zcert_print(zcert_handle());
    }

    void __clone() {
        set_handle(zcert_dup(zcert_handle()), true, "zcert");
    }

    int __compare(const ZCert &that) const {
        return (int) (zcert_eq(zcert_handle(), that.zcert_handle()) ? 0 : -1);
    }

    static Php::Class<ZCert> php_register() {
        Php::Class<ZCert> o("ZCert");

        o.method("__construct", &ZCert::__construct, {
            Php::ByVal("filename", Php::Type::String, false)
        });

        o.method("get_public_key", &ZCert::get_public_key);
        o.method("get_secret_key", &ZCert::get_secret_key);
        o.method("get_public_key_txt", &ZCert::get_public_key_txt);
        o.method("get_secret_key_txt", &ZCert::get_secret_key_txt);

        o.method("get_meta", &ZCert::get_meta, {
            Php::ByVal("name", Php::Type::String, true)
        });
        o.method("get_meta_keys", &ZCert::get_meta_keys);

        o.method("set_meta", &ZCert::set_meta, {
            Php::ByVal("name", Php::Type::String, true),
            Php::ByVal("value", Php::Type::String, true)
        });

        o.method("save", &ZCert::save, {
            Php::ByVal("filename", Php::Type::String, true)
        });

        o.method("save_public", &ZCert::save_public, {
            Php::ByVal("filename", Php::Type::String, true)
        });

        o.method("save_secret", &ZCert::save_secret, {
            Php::ByVal("filename", Php::Type::String, true)
        });

        o.method("apply", &ZCert::apply, {
            Php::ByRef("zhandle", "IZSocket", false, true)
        });

        o.method("dump", &ZCert::dump);

        return o;
    }

};
