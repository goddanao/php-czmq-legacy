#include <phpcpp.h>
#include "../include/czmq.h"
#include "../include/zyre.h"
#include "../include/malamute.h"
#include "../include/majordomo.h"

extern "C" {
    
    PHPCPP_EXPORT void *get_module()
    {
        static Php::Extension extension("czmq", "0.2");

        // Initialize zmq global context and defaults
        extension.onStartup([]() {
            zsys_init ();
            zsys_set_logsystem (true); //  Send logging to system facility as well as stdout
            zsys_set_pipehwm (0);
            zsys_set_sndhwm (0);
            zsys_set_rcvhwm (0);
        });

        // Shutdown zmq global context
        extension.onShutdown([]() {
            zsys_shutdown();
        });

        php_czmq_register(&extension);
        php_zyre_register(&extension);
        php_malamute_register(&extension);
        php_majordomo_register(&extension);

        return extension;
    }
}
