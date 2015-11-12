#include "czmq.h"
#include "zyre.h"
#include "majordomo.h"
#include "malamute.h"

extern "C" {
    
    PHPCPP_EXPORT void *get_module()
    {
        static Php::Extension extension("php-czmq", "0.3");

        // Initialize zmq global context and defaults
        extension.onStartup([]() {
            zsys_init ();               //  Earliest initialization
            zsys_set_logsystem (true);  //  Send logging to system facility as well as stdout
            zsys_set_pipehwm (0);
            zsys_set_sndhwm (0);
            zsys_set_rcvhwm (0);
        });

        // Shutdown zmq global context
        extension.onShutdown([]() {
            zsys_shutdown();
        });

    // COMMON

        // IZSocket
        Php::Interface izsocket("IZSocket");

    // CZMQ

        // ZContext
        Php::Class<ZContext> zcontext = ZContext::php_register();

        // ZSys
        Php::Class<ZSys> zsys = ZSys::php_register();

        // ZUdp
        Php::Class<ZUdp> zudp = ZUdp::php_register();

        // ZMsg
        Php::Class<ZMsg> zmsg = ZMsg::php_register();

        // ZFrame
        Php::Class<ZFrame> zframe = ZFrame::php_register();

        // ZPoll (Read/Write - LIBZMQ Based)
        Php::Class<ZPoll> zpoll = ZPoll::php_register();

        // ZLoop
        Php::Class<ZLoop> zloop = ZLoop::php_register();

        // ZCert
        Php::Class<ZCert> zcert = ZCert::php_register();

        // ZCertStore
        Php::Class<ZCertStore> zcertstore = ZCertStore::php_register();

        // ZSocket
        Php::Class<ZSocket> zsocket = ZSocket::php_register();
        zsocket.implements(izsocket);

        // ZProxy
        Php::Class<ZProxy> zproxy = ZProxy::php_register();
        zproxy.implements(izsocket);

        // ZBeacon
        Php::Class<ZBeacon> zbeacon = ZBeacon::php_register();
        zbeacon.implements(izsocket);

        // ZAuth
        Php::Class<ZAuth> zauth = ZAuth::php_register();
        zauth.implements(izsocket);

        // ZGossip
        Php::Class<ZGossip> zgossip = ZGossip::php_register();
        zgossip.implements(izsocket);

    // ZYRE

        // Zyre
        Php::Class<Zyre> zyre = Zyre::php_register();
        zyre.implements(izsocket);

    // MAJORDOMO

        // Majordomo Broker
        Php::Class<MajordomoBroker> mdpbroker = MajordomoBroker::php_register();
        mdpbroker.implements(izsocket);

        // Majordomo Worker
        Php::Class<MajordomoWorker> mdpworker = MajordomoWorker::php_register();
        mdpworker.implements(izsocket);

        // Majordomo Client
        Php::Class<MajordomoClient> mdpclient = MajordomoClient::php_register();
        mdpclient.implements(izsocket);

    // MALAMUTE

        // Malamute Broker
        Php::Class<MalamuteBroker> mlmbroker = MalamuteBroker::php_register();
        mlmbroker.implements(izsocket);


        // Malamute Client
        Php::Class<MalamuteClient> mlmclient = MalamuteClient::php_register();
        mlmclient.implements(izsocket);


    // Add classes to Extension

        //common
        extension.add(std::move(izsocket));

        // czmq
        extension.add(std::move(zcontext));
        extension.add(std::move(zsys));
        extension.add(std::move(zudp));
        extension.add(std::move(zmsg));
        extension.add(std::move(zframe));
        extension.add(std::move(zloop));
        extension.add(std::move(zpoll));
        extension.add(std::move(zcert));
        extension.add(std::move(zcertstore));
        extension.add(std::move(zsocket));
        extension.add(std::move(zproxy));
        extension.add(std::move(zbeacon));
        extension.add(std::move(zauth));
        extension.add(std::move(zgossip));
        // zyre
        extension.add(std::move(zyre));
        // majordomo
        extension.add(std::move(mdpbroker));
        extension.add(std::move(mdpworker));
        extension.add(std::move(mdpclient));
        // malamute
        extension.add(std::move(mlmbroker));
        extension.add(std::move(mlmclient));



        return extension;
    }
}
