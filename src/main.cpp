#include "czmq.h"
#include "zyre.h"
#include "majordomo.h"
#include "fmq.h"

#if (ZMQ_VERSION >= ZMQ_MAKE_VERSION(4,2,0))
    #include "malamute.h"
#endif

extern "C" {
    
    PHPCPP_EXPORT void *get_module()
    {
        static Php::Extension extension("php-czmq", "0.3");

        // Initialize zmq global context and defaults
        extension.onStartup([]() {
            zsys_init ();               //  Earliest initialization
            zsys_set_pipehwm (0);
            zsys_set_sndhwm (0);
            zsys_set_rcvhwm (0);

            // mlm_client_verbose = true;
            // fmq_client_verbose = true;

        });

        // Shutdown zmq global context
        extension.onShutdown([]() {
            zsys_shutdown();
        });

    // COMMON

        // IZDescriptor
        Php::Interface izdescriptor("IZDescriptor");
        izdescriptor.method("get_fd");

        // IZSocket
        Php::Interface izsocket("IZSocket");
        izsocket.extends(izdescriptor);
        izsocket.method("get_socket");

        // IZEmitter
        Php::Interface izemitter("IZEmitter");
        izemitter.method("on", {
            Php::ByVal("event", Php::Type::String, true),
            Php::ByVal("listener", Php::Type::Callable, true)
        });
        izemitter.method("once", {
            Php::ByVal("event", Php::Type::String, true),
            Php::ByVal("listener", Php::Type::Callable, true)
        });
        izemitter.method("remove_listener", {
            Php::ByVal("event", Php::Type::String, true),
            Php::ByVal("listener", Php::Type::Callable, true)
        });
        izemitter.method("remove_all_listeners", {
            Php::ByVal("event", Php::Type::String, false)
        });
        izemitter.method("listeners", {
            Php::ByVal("event", Php::Type::String, true)
        });
        izemitter.method("emit", {
            Php::ByVal("event", Php::Type::String, true),
            Php::ByVal("arguments", Php::Type::Array, true)
        });

    // MSGPACK
        Php::Class<MsgPack> mmsgpack = MsgPack::php_register();

    // CZMQ

        // ZSys
        Php::Class<ZSys> zsys = ZSys::php_register();

        // ZMsg
        Php::Class<ZMsg> zmsg = ZMsg::php_register();

        // ZFrame
        Php::Class<ZFrame> zframe = ZFrame::php_register();

        // ZPoll
        Php::Class<ZPoll> zpoll = ZPoll::php_register();

        // ZLoop
        Php::Class<ZLoop> zloop = ZLoop::php_register();

        // ZCert
        Php::Class<ZCert> zcert = ZCert::php_register();

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

        // ZUdp
        Php::Class<ZUdp> zudp = ZUdp::php_register();
        zudp.implements(izdescriptor);

        // ZGossip
        Php::Class<ZGossip> zgossip = ZGossip::php_register();
        zgossip.implements(izsocket);

        // ZInotify
        Php::Class<ZInotify> zinotify = ZInotify::php_register();
        zinotify.implements(izdescriptor);

        // Std IN OUT ERR
        Php::Class<ZStdIn> _stdin = ZStdIn::php_register();
        _stdin.implements(izdescriptor);
        Php::Class<ZStdOut> _stdout = ZStdOut::php_register();
        _stdout.implements(izdescriptor);
        Php::Class<ZStdErr> _stderr = ZStdErr::php_register();
        _stderr.implements(izdescriptor);

    // ZYRE

        Php::Namespace zyre_ns("Zyre");

        // Zyre
        Php::Class<Zyre> zyre = Zyre::php_register();
        zyre.implements(izsocket);
        zyre_ns.add(std::move(zyre));

    // MAJORDOMO

        Php::Namespace mdp_ns("Majordomo");

        // Majordomo Broker V2
        Php::Class<MajordomoBrokerV2> mdpbroker = MajordomoBrokerV2::php_register();
        mdpbroker.implements(izsocket);
        mdp_ns.add(std::move(mdpbroker));

        // Majordomo Worker V2
        Php::Class<MajordomoWorkerV2> mdpworker = MajordomoWorkerV2::php_register();
        mdpworker.implements(izsocket);
        mdp_ns.add(std::move(mdpworker));

        // Majordomo Client V2
        Php::Class<MajordomoClientV2> mdpclient = MajordomoClientV2::php_register();
        mdpclient.implements(izsocket);
        mdp_ns.add(std::move(mdpclient));

        // Majordomo Titanic V2
        Php::Class<MajordomoTitanicV2> mdptitanic = MajordomoTitanicV2::php_register();
        mdptitanic.implements(izsocket);
        mdp_ns.add(std::move(mdptitanic));

        // TitanicStorage
        Php::Interface iTitanicStorage("ITitanicStorage");
        iTitanicStorage.method("read", {
            Php::ByVal("what", Php::Type::String, true),
            Php::ByVal("uuid", Php::Type::String, true)
        });
        iTitanicStorage.method("store", {
            Php::ByVal("what", Php::Type::String, true),
            Php::ByVal("uuid", Php::Type::String, true),
            Php::ByVal("msg", "ZMsg", false, true)
        });
        iTitanicStorage.method("close", {
            Php::ByVal("uuid", Php::Type::String, true)
        });
        iTitanicStorage.method("status", {
            Php::ByVal("uuid", Php::Type::String, true)
        });
        iTitanicStorage.method("process");
        mdp_ns.add(std::move(iTitanicStorage));


#ifdef MALAMUTE_VERSION_MAJOR

    // MALAMUTE

        Php::Namespace mlm_ns("Malamute");

        // Malamute Broker
        Php::Class<MalamuteBroker> mlmbroker = MalamuteBroker::php_register();
        mlmbroker.implements(izsocket);
        mlm_ns.add(std::move(mlmbroker));

        // Malamute Client
        Php::Class<MalamuteClient> mlmclient = MalamuteClient::php_register();
        mlmclient.implements(izsocket);
        mlm_ns.add(std::move(mlmclient));

        // Malamute Worker
        Php::Class<MalamuteWorker> mlmworker = MalamuteWorker::php_register();
        mlmworker.implements(izsocket);
        mlm_ns.add(std::move(mlmworker));

        // Malamute Producer
        Php::Class<MalamuteProducer> mlmproducer = MalamuteProducer::php_register();
        mlmproducer.implements(izsocket);
        mlm_ns.add(std::move(mlmproducer));

        // Malamute Consumer
        Php::Class<MalamuteConsumer> mlmconsumer = MalamuteConsumer::php_register();
        mlmconsumer.implements(izsocket);
        mlm_ns.add(std::move(mlmconsumer));

#endif

    // FILEMQ

        Php::Namespace fmq_ns("FileMq");

        // FileMq Broker
        Php::Class<FileMqServer> fmqserver = FileMqServer::php_register();
        fmqserver.implements(izsocket);
        fmq_ns.add(std::move(fmqserver));

        // FileMq Client
        Php::Class<FileMqClient> fmqclient = FileMqClient::php_register();
        fmqclient.implements(izsocket);
        fmq_ns.add(std::move(fmqclient));

    // Add classes to Extension

        //common
        extension.add(std::move(izdescriptor));
        extension.add(std::move(izsocket));
        extension.add(std::move(izemitter));

        // msgpack
        extension.add(std::move(mmsgpack));

        // czmq
        extension.add(std::move(zsys));
        extension.add(std::move(zudp));
        extension.add(std::move(zmsg));
        extension.add(std::move(zframe));
        extension.add(std::move(zloop));
        extension.add(std::move(zpoll));
        extension.add(std::move(zcert));
        extension.add(std::move(zsocket));
        extension.add(std::move(zproxy));
        extension.add(std::move(zbeacon));
        extension.add(std::move(zauth));
        extension.add(std::move(zgossip));
        extension.add(std::move(zinotify));
        extension.add(std::move(_stdin));
        extension.add(std::move(_stdout));
        extension.add(std::move(_stderr));

        // zyre
        extension.add(std::move(zyre_ns));

        // majordomo
        extension.add(std::move(mdp_ns));

    #ifdef MALAMUTE_VERSION_MAJOR
        // malamute
        extension.add(std::move(mlm_ns));
    #endif

        // fmq
        extension.add(std::move(fmq_ns));

        return extension;
    }
}
