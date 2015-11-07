#pragma once

#include "../common.h"

class ZCertStore : public ZHandle, public Php::Base  {
public:
    ZCertStore() : ZHandle(), Php::Base() {};
    ZCertStore(zcertstore_t *handle, bool owned) : ZHandle(handle, owned, "zcertstore"), Php::Base() {}
    zcertstore_t *zcertstore_handle() const { return (zcertstore_t *) get_handle(); }

    void __construct(Php::Parameters &param) {
        if(param.size() == 0)
            set_handle(zcertstore_new (NULL), true, "zcertstore");
        else
            set_handle(zcertstore_new(param[0].stringValue().c_str()), true, "zcertstore");
    }

    Php::Value lookup (Php::Parameters &param) {
        zcert_t *cert = zcertstore_lookup(zcertstore_handle(), param[0].stringValue().c_str());
        if(cert) {
            return Php::Object("ZCert", new ZCert(zcert_dup(cert), true));
        }
        return nullptr;
    }

    void insert(Php::Parameters &param) {
        ZCert *cert = dynamic_cast<ZCert *>(param[0].implementation());
        if(cert) {
            zcert_t* cert_p = zcert_dup(cert->zcert_handle());
            zcertstore_insert (zcertstore_handle(), &cert_p); // (zcert_t **)
        }
    }

    void dump() {
        zcertstore_print (zcertstore_handle());
    }

    static Php::Class<ZCertStore> php_register() {
        Php::Class<ZCertStore> o("ZCertStore");

        o.method("__construct", &ZCertStore::__construct, {
            Php::ByVal("certificates_dir", Php::Type::String, false)
        });

        o.method("lookup", &ZCertStore::lookup, {
            Php::ByVal("pubkey", Php::Type::String, true)
        });

        o.method("insert", &ZCertStore::insert, {
            Php::ByVal("cert", "ZCert", false, true)
        });

         o.method("dump", &ZCertStore::dump);

        return o;
    }
};
