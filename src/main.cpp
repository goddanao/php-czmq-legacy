#include "czmq.h"
#include "zyre.h"
#include "majordomo.h"
#include "malamute.h"
#include "fmq.h"

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

            // mlm_client_verbose = true;
            // fmq_client_verbose = true;

        });

        // Shutdown zmq global context
        extension.onShutdown([]() {
            zsys_shutdown();
        });

    // COMMON

        // IZSocket
        Php::Interface izsocket("IZSocket");
        izsocket.method("get_socket");
        izsocket.method("get_fd");

    // CZMQ

        // ZContext
        Php::Class<ZContext> zcontext = ZContext::php_register();

        // ZSys
        Php::Class<ZSys> zsys = ZSys::php_register();

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

        // ZUdp
        Php::Class<ZUdp> zudp = ZUdp::php_register();
        zudp.implements(izsocket);

        // ZGossip
        Php::Class<ZGossip> zgossip = ZGossip::php_register();
        zgossip.implements(izsocket);

    // ZYRE

        // Zyre
        Php::Class<Zyre> zyre = Zyre::php_register();
        zyre.implements(izsocket);

    // MAJORDOMO

        Php::Namespace mdp_ns("Majordomo");
        Php::Namespace mdp_ns_version2("V2");
        Php::Namespace mdp_ns_versionX("V1");

        // Majordomo Broker
        Php::Class<MajordomoBrokerV2> mdpbroker = MajordomoBrokerV2::php_register();
        mdpbroker.implements(izsocket);
        mdp_ns_version2.add(std::move(mdpbroker));

        // Majordomo Worker
        Php::Class<MajordomoWorkerV2> mdpworker = MajordomoWorkerV2::php_register();
        mdpworker.implements(izsocket);
        mdp_ns_version2.add(std::move(mdpworker));

        // Majordomo Client
        Php::Class<MajordomoClientV2> mdpclient = MajordomoClientV2::php_register();
        mdpclient.implements(izsocket);
        mdp_ns_version2.add(std::move(mdpclient));

        mdp_ns.add(std::move(mdp_ns_version2));

        // Majordomo Broker V1
        Php::Class<MajordomoBrokerV1> mdpbrokerv1 = MajordomoBrokerV1::php_register();
        mdpbrokerv1.implements(izsocket);
        mdp_ns_versionX.add(std::move(mdpbrokerv1));

        // Majordomo Worker V1
        Php::Class<MajordomoWorkerV1> mdpworkerv1 = MajordomoWorkerV1::php_register();
        mdpworkerv1.implements(izsocket);
        mdp_ns_versionX.add(std::move(mdpworkerv1));

        // Majordomo Client V1
        Php::Class<MajordomoClientV1> mdpclientv1 = MajordomoClientV1::php_register();
        mdpclientv1.implements(izsocket);
        mdp_ns_versionX.add(std::move(mdpclientv1));

        mdp_ns.add(std::move(mdp_ns_versionX));

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
        extension.add(std::move(mdp_ns));
        // malamute
        extension.add(std::move(mlm_ns));
        // fmq
        extension.add(std::move(fmq_ns));

        return extension;
    }
}
