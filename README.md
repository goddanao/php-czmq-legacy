PHP-CZMQ [![Build Status](https://travis-ci.org/goddanao/php-czmq.svg)](https://travis-ci.org/goddanao/php-czmq)
================
Php 5.4+ binding built with [PHP-CPP](http://www.php-cpp.com/) for 

Library | Description | Classes
--- | --- | ---
[CZMQ](https://github.com/zeromq/czmq) | [CLASS](http://rfc.zeromq.org/spec:21)y ZeromMQ | [ZSys](https://github.com/goddanao/php-czmq/blob/master/api/ZSys.md), [ZMsg](https://github.com/goddanao/php-czmq/blob/master/api/ZMsg.md), [ZFrame](https://github.com/goddanao/php-czmq/blob/master/api/ZFrame.md), [ZSocket](https://github.com/goddanao/php-czmq/blob/master/api/ZSocket.md), [ZLoop](https://github.com/goddanao/php-czmq/blob/master/api/ZLoop.md), [ZPoll](https://github.com/goddanao/php-czmq/blob/master/api/ZPoll.md), [ZProxy](https://github.com/goddanao/php-czmq/blob/master/api/ZProxy.md), [ZGossip](https://github.com/goddanao/php-czmq/blob/master/api/ZGossip.md), [ZBeacon](https://github.com/goddanao/php-czmq/blob/master/api/ZBeacon.md), [ZUdp](https://github.com/goddanao/php-czmq/blob/master/api/ZUdp.md), [ZAuth](https://github.com/goddanao/php-czmq/blob/master/api/ZAuth.md), [ZCert](https://github.com/goddanao/php-czmq/blob/master/api/ZCert.md), [ZMonitor](https://github.com/goddanao/php-czmq/blob/master/api/ZMonitor.md)
[ZYRE](https://github.com/zeromq/zyre) | Framework for proximity-based peer-to-peer applications | [Zyre\Zyre](https://github.com/goddanao/php-czmq/blob/master/api/Zyre-Zyre.md)
[FILEMQ](https://github.com/zeromq/filemq) | Publish-Subscribe file service | [FileMq\Server](https://github.com/goddanao/php-czmq/blob/master/api/FileMq-Server.md), [FileMq\Client](https://github.com/goddanao/php-czmq/blob/master/api/FileMq-Client.md)
[Malamute](https://github.com/zeromq/malamute) | All the enterprise messaging patterns in one box. [(docs)](https://github.com/zeromq/malamute/blob/master/MALAMUTE.md) | [Malamute\Broker](https://github.com/goddanao/php-czmq/blob/master/api/Malamute-Broker.md), [Malamute\Worker](https://github.com/goddanao/php-czmq/blob/master/api/Malamute-Worker.md), [Malamute\Client](https://github.com/goddanao/php-czmq/blob/master/api/Malamute-Client.md), [Malamute\Producer](https://github.com/goddanao/php-czmq/blob/master/api/Malamute-Producer.md), [Malamute\Consumer](https://github.com/goddanao/php-czmq/blob/master/api/Malamute-Consumer.md)
[Majordomo Pattern V1](http://rfc.zeromq.org/spec:7) | Reliable service-oriented request-reply dialog between a set of client applications, a broker and a set of worker applications | [Majordomo\V1\Broker](https://github.com/goddanao/php-czmq/blob/master/api/Majordomo-V1-Broker.md), [Majordomo\V1\Worker](https://github.com/goddanao/php-czmq/blob/master/api/Majordomo-V1-Worker.md), [Majordomo\V1\Client](https://github.com/goddanao/php-czmq/blob/master/api/Majordomo-V1-Client.md) 
[Majordomo Pattern V2](http://rfc.zeromq.org/spec:18) | Adds support for multiple replies for a single request | [Majordomo\V2\Broker](https://github.com/goddanao/php-czmq/blob/master/api/Majordomo-V2-Broker.md), [Majordomo\V2\Worker](https://github.com/goddanao/php-czmq/blob/master/api/Majordomo-V2-Worker.md), [Majordomo\V2\Client](https://github.com/goddanao/php-czmq/blob/master/api/Majordomo-V2-Client.md)

**DISCLAIMER:** It's my first (early stage) approach to c++, this project need to be considered highly experimental thus open to your suggestions/improvements. Please be patient! ;-)

##Motivation
The official ZeroMq php binding doesn't cover the CZMQ Api 3, Zyre, Malamute and other interesting projects/patterns from the ZeroMq community and i wish to implement my first php extension using [PHP-CPP](http://www.php-cpp.com/).

##Status
The project wraps most of the CZMQ api in easy to use php components. It's in a early stage, interfaces and classes are subject to changes, please use it only for testing.

## Build
Install the required libraries, clone this repo and do a standard make/make install. 
The installer puts czmq.ini config file in ```/etc/php5/mods-available```, modify your php.ini to include "extension=czmq.so" or make a symbolic link in ```/etc/php5/cli/conf.d/20-czmq.ini``` or ```/etc/php5/apache2/conf.d/20-czmq.ini``` for default loading in cli and in apache.
Otherwise use docker! There is a docker config for building the test environment.

### Install Required Libraries
```
git clone git://github.com/jedisct1/libsodium.git
git clone git://github.com/zeromq/libzmq.git
git clone git://github.com/zeromq/czmq.git
git clone git://github.com/zeromq/zyre.git
git clone git://github.com/zeromq/majordomo.git
git clone git://github.com/zeromq/filemq.git
git clone git://github.com/zeromq/malamute.git
for project in libsodium libzmq czmq zyre majordomo filemq malamute; do
    cd $project
    ./autogen.sh
    ./configure && make check
    sudo make install
    sudo ldconfig
    cd ..
done
git clone git://github.com/CopernicaMarketingSoftware/PHP-CPP.git
cd PHP-CPP
make
sudo make install
sudo ldconfig
cd ..
```
## Usage
Still to come... Take a look at the [Api](https://github.com/goddanao/php-czmq/blob/master/api/ApiIndex.md), [Examples](https://github.com/goddanao/php-czmq/tree/master/examples), [Tests](https://github.com/goddanao/php-czmq/tree/master/tests).
