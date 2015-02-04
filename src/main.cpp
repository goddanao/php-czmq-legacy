#include <phpcpp.h>
#include "../czmq.h"

/**
 *  tell the compiler that the get_module is a pure C function
 */

extern "C" {
    
    /**
     *  Function that is called by PHP right after the PHP process
     *  has started, and that returns an address of an internal PHP
     *  strucure with all the details and features of your extension
     *
     *  @return void*   a pointer to an address that is understood by PHP
     */
    PHPCPP_EXPORT void *get_module() 
    {
        // static(!) Php::Extension object that should stay in memory
        // for the entire duration of the process (that's why it's static)
        static Php::Extension extension("czmq", "1.0");

        // Allo startup (load del modulo) inizializza il global context e imposta alcuni defaults per zmq
        extension.onStartup([]() {
            //  Send logging to system facility as well as stdout
            zsys_init ();
            zsys_set_logsystem (true);
            zsys_set_pipehwm (0);
            zsys_set_sndhwm (0);
            zsys_set_rcvhwm (0);
        });

        php_czmq_register(&extension);

//
//
//        // ZCertStore
//        Php::Class<ZCertStore> zcertstore("ZCertStore");
//        zcertstore.method("__construct", &ZCertStore::__construct);
//        zcertstore.method("lookup", &ZCertStore::lookup);
//        zcertstore.method("insert", &ZCertStore::insert);
//        zcertstore.method("dump", &ZCertStore::dump);
//        extension.add(std::move(zcertstore));
//
//        // ZUtils
//        Php::Class<ZUtils> zutils("ZUtils");
//        zutils.method("zmq_version", &ZUtils::libzmq_version);
//        zutils.method("czmq_version", &ZUtils::libczmq_version);
//        zutils.method("zyre_version", &ZUtils::libzyre_version);
//        zutils.method("hostname", &ZUtils::hostname);
//        zutils.method("list_interfaces", &ZUtils::list_interfaces);
//        extension.add(std::move(zutils));

        // return the extension
        return extension;
    }
}
