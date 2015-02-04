#pragma once

#include "zhandle.h"
#include "zsocket.h"

class ZCert : public ZHandle {
private:
    bool _verbose;
public:
    ZCert() : ZHandle() {}
    ZCert(zcert_t *handle, bool owned) : ZHandle(handle, owned, "zcert") {}
    zcert_t *zcert_handle() const { return (zcert_t *) get_handle(); }

    void __construct(Php::Parameters &param);

    Php::Value get_public_key();

    Php::Value get_secret_key();

    Php::Value get_public_key_txt();

    Php::Value get_secret_key_txt();

    void set_meta(Php::Parameters &param);

    Php::Value get_meta(Php::Parameters &param);

    Php::Value get_meta_keys();

    void save(Php::Parameters &param);

    void save_public(Php::Parameters &param);

    void save_secret(Php::Parameters &param);

    void apply(Php::Parameters &param);

    void dump();

    void __clone();

    int __compare(const ZCert &that) const;

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
            Php::ByRef("zhandle", "ZHandle", false, true)
        });

        o.method("dump", &ZCert::dump);

        return o;
    }

};
