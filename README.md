PHP-CZMQ [![Build Status](https://travis-ci.org/goddanao/php-czmq.svg)](https://travis-ci.org/goddanao/php-czmq)
================
Php 5.4+ binding for ZeroMQ and derived projects / patterns. Includes MsgPack binary serialization support.

Library | Description | Classes
--- | --- | ---
[czmq](https://github.com/zeromq/czmq) | [class](http://rfc.zeromq.org/spec:21)y ZeroMq | [ZSys](https://github.com/goddanao/php-czmq/blob/master/api/ZSys.md), [ZMsg](https://github.com/goddanao/php-czmq/blob/master/api/ZMsg.md), [ZFrame](https://github.com/goddanao/php-czmq/blob/master/api/ZFrame.md), [ZSocket](https://github.com/goddanao/php-czmq/blob/master/api/ZSocket.md), [ZLoop](https://github.com/goddanao/php-czmq/blob/master/api/ZLoop.md), [ZPoll](https://github.com/goddanao/php-czmq/blob/master/api/ZPoll.md), [ZProxy](https://github.com/goddanao/php-czmq/blob/master/api/ZProxy.md), [ZGossip](https://github.com/goddanao/php-czmq/blob/master/api/ZGossip.md), [ZBeacon](https://github.com/goddanao/php-czmq/blob/master/api/ZBeacon.md), [ZUdp](https://github.com/goddanao/php-czmq/blob/master/api/ZUdp.md), [ZAuth](https://github.com/goddanao/php-czmq/blob/master/api/ZAuth.md), [ZCert](https://github.com/goddanao/php-czmq/blob/master/api/ZCert.md)
[zyre](https://github.com/zeromq/zyre) | Framework for proximity-based peer-to-peer applications | [Zyre\Zyre](https://github.com/goddanao/php-czmq/blob/master/api/Zyre-Zyre.md)
[filemq](https://github.com/zeromq/filemq) | Publish-Subscribe file service | [FileMq\Server](https://github.com/goddanao/php-czmq/blob/master/api/FileMq-Server.md), [FileMq\Client](https://github.com/goddanao/php-czmq/blob/master/api/FileMq-Client.md)
[majordomo](https://github.com/zeromq/majordomo) | Reliable service-oriented request-reply dialog between a set of client applications, a broker and a set of worker applications. [(majordomo v2)](http://rfc.zeromq.org/spec:18) [(mmi)](http://rfc.zeromq.org/spec:8) [(titanic)](http://rfc.zeromq.org/spec:9) | [Majordomo\Broker](https://github.com/goddanao/php-czmq/blob/master/api/Majordomo-Broker.md), [Majordomo\Worker](https://github.com/goddanao/php-czmq/blob/master/api/Majordomo-Worker.md), [Majordomo\Client](https://github.com/goddanao/php-czmq/blob/master/api/Majordomo-Client.md), [Majordomo\Titanic](https://github.com/goddanao/php-czmq/blob/master/api/Majordomo-Titanic.md)
[malamute](https://github.com/zeromq/malamute) | All the enterprise messaging patterns in one box. Requires libzmq 4.2.0+ [(docs)](https://github.com/zeromq/malamute/blob/master/MALAMUTE.md) | [Malamute\Broker](https://github.com/goddanao/php-czmq/blob/master/api/Malamute-Broker.md), [Malamute\Worker](https://github.com/goddanao/php-czmq/blob/master/api/Malamute-Worker.md), [Malamute\Client](https://github.com/goddanao/php-czmq/blob/master/api/Malamute-Client.md), [Malamute\Producer](https://github.com/goddanao/php-czmq/blob/master/api/Malamute-Producer.md), [Malamute\Consumer](https://github.com/goddanao/php-czmq/blob/master/api/Malamute-Consumer.md)
[msgpack](https://github.com/msgpack/msgpack-c) | Efficient binary serialization format | [MsgPacker](https://github.com/goddanao/php-czmq/blob/master/api/MsgPacker.md)

##Motivation
The official ZeroMq php binding doesn't cover Zyre, Majordomo, Malamute and other interesting projects/patterns from the ZeroMq community and i wish to implement my first php extension using [PHP-CPP](http://www.php-cpp.com/).

##Status
The project wraps most of the api in easy to use php components. It's in a early stage, interfaces and classes are subject to changes, please use it only for testing.

##Install

On Ubuntu 14.04, install required packages
```
sudo apt-get install -qq git g++-4.8 uuid-dev build-essential autoconf php5-dev pkg-config
sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-4.8 90
```

Then use one of the provided installers for [master branch](https://github.com/goddanao/php-czmq/blob/master/install/install-master.sh), [stable 4.2 branch](https://github.com/goddanao/php-czmq/blob/master/install/install-stable-4.2.sh), [stable 4.1 branch](https://github.com/goddanao/php-czmq/blob/master/install/install-stable-4.1.sh) version on libzmq.

## Usage
Still to come... Take a look at the [Api](https://github.com/goddanao/php-czmq/blob/master/api/ApiIndex.md), [Ide Helper](https://github.com/goddanao/php-czmq/blob/master/ide_helper.php), [Examples](https://github.com/goddanao/php-czmq/tree/master/examples), [Tests](https://github.com/goddanao/php-czmq/tree/master/tests).
