#pragma once

#include "common.h"
#include "czmq/zcontext.h"
#include "czmq/zsys.h"
#include "czmq/zframe.h"
#include "czmq/zmsg.h"
#include "czmq/zsocket.h"
#include "czmq/zproxy.h"
#include "czmq/zpoller.h"
#include "czmq/zpoll.h"
#include "czmq/zcert.h"
#include "czmq/zcertstore.h"
#include "czmq/zbeacon.h"
#include "czmq/zreactor.h"
#include "czmq/zactor.h"
#include "czmq/zauth.h"
#include "czmq/zgossip.h"
#include "czmq/zudp.h"

void php_czmq_register(Php::Extension *extension) {

    // ZContext
    Php::Class<ZContext> zcontext = ZContext::php_register();
    extension->add(std::move(zcontext));

    // ZSys
    Php::Class<ZSys> zsys = ZSys::php_register();
    extension->add(std::move(zsys));

    // ZUdp
    Php::Class<ZUdp> zudp = ZUdp::php_register();
    extension->add(std::move(zudp));

    // ZMsg
    Php::Class<ZMsg> zmsg = ZMsg::php_register();
    extension->add(std::move(zmsg));

    // ZFrame
    Php::Class<ZFrame> zframe = ZFrame::php_register();
    extension->add(std::move(zframe));

    // ZPoll (Read/Write - LIBZMQ Based)
    Php::Class<ZPoll> zpoll = ZPoll::php_register();
    extension->add(std::move(zpoll));

    // ZPoller
    Php::Class<ZPoller> zpoller = ZPoller::php_register();
    extension->add(std::move(zpoller));

    // ZReactor
    Php::Class<ZReactor> zreactor = ZReactor::php_register();
    extension->add(std::move(zreactor));

    // ZCert
    Php::Class<ZCert> zcert = ZCert::php_register();
    extension->add(std::move(zcert));

    // ZCertStore
    Php::Class<ZCertStore> zcertstore = ZCertStore::php_register();
    extension->add(std::move(zcertstore));


    // IZSocket
    Php::Interface izsocket("IZSocket");

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

    extension->add(std::move(izsocket));
    extension->add(std::move(zsocket));
    extension->add(std::move(zproxy));
    extension->add(std::move(zbeacon));
    extension->add(std::move(zauth));
    extension->add(std::move(zgossip));

}