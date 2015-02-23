#pragma once

#include "czmq/zsys.h"
#include "czmq/zhandle.h"
#include "czmq/zhash.h"
#include "czmq/zchunk.h"
#include "czmq/zframe.h"
#include "czmq/zmsg.h"
#include "czmq/zsocket.h"
#include "czmq/zproxy.h"
#include "czmq/zpoller.h"
#include "czmq/zpoll.h"
#include "czmq/zcert.h"
#include "czmq/zbeacon.h"
#include "czmq/zreactor.h"
#include "czmq/zactor.h"
#include "czmq/zauth.h"
#include "czmq/zgossip.h"
//#include "czmq/zudp.h"

void php_czmq_register(Php::Extension *extension) {

    // ZSys
    Php::Class<ZSys> zsys = ZSys::php_register();
    extension->add(std::move(zsys));

    // ZContext
    Php::Class<ZContext> zcontext = ZContext::php_register();
    extension->add(std::move(zcontext));

    // ZUdp
//    Php::Class<ZUdp> zudp = ZUdp::php_register();
//    extension->add(std::move(zudp));

    // ZHash
    Php::Class<ZHash> zhash = ZHash::php_register();
    extension->add(std::move(zhash));

    // ZMsg
    Php::Class<ZMsg> zmsg = ZMsg::php_register();
    extension->add(std::move(zmsg));

    // ZFrame
    Php::Class<ZFrame> zframe = ZFrame::php_register();
    extension->add(std::move(zframe));

    // ZChunk
    Php::Class<ZChunk> zchunk = ZChunk::php_register();
    extension->add(std::move(zchunk));

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

    // ZHandle
    Php::Class<ZHandle> zhandle("ZHandle");

    // ZSocket
    Php::Class<ZSocket> zsocket = ZSocket::php_register();
    zsocket.extends(zhandle);

    // ZActor
    Php::Class<ZActor> zactor = ZActor::php_register();
    zactor.extends(zhandle);

    // ZProxy
    Php::Class<ZProxy> zproxy = ZProxy::php_register();
    zproxy.extends(zactor);

    // ZBeacon
    Php::Class<ZBeacon> zbeacon = ZBeacon::php_register();
    zbeacon.extends(zactor);

    // ZAuth
    Php::Class<ZAuth> zauth = ZAuth::php_register();
    zauth.extends(zactor);

    // ZGossip
    Php::Class<ZGossip> zgossip = ZGossip::php_register();
    zgossip.extends(zactor);

    extension->add(std::move(zhandle));
    extension->add(std::move(zactor));
    extension->add(std::move(zsocket));
    extension->add(std::move(zproxy));
    extension->add(std::move(zbeacon));
    extension->add(std::move(zauth));
    extension->add(std::move(zgossip));

}