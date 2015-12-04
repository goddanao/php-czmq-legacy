PHP-CZMQ [![Build Status](https://travis-ci.org/goddanao/php-czmq.svg)](https://travis-ci.org/goddanao/php-czmq)
================
Php 5.4+ binding for 

Library | Description | Classes
--- | --- | ---
[CZMQ](https://github.com/zeromq/czmq) | [CLASS](http://rfc.zeromq.org/spec:21)y ZeroMQ | [ZSys](https://github.com/goddanao/php-czmq/blob/master/api/ZSys.md), [ZMsg](https://github.com/goddanao/php-czmq/blob/master/api/ZMsg.md), [ZFrame](https://github.com/goddanao/php-czmq/blob/master/api/ZFrame.md), [ZSocket](https://github.com/goddanao/php-czmq/blob/master/api/ZSocket.md), [ZLoop](https://github.com/goddanao/php-czmq/blob/master/api/ZLoop.md), [ZPoll](https://github.com/goddanao/php-czmq/blob/master/api/ZPoll.md), [ZProxy](https://github.com/goddanao/php-czmq/blob/master/api/ZProxy.md), [ZGossip](https://github.com/goddanao/php-czmq/blob/master/api/ZGossip.md), [ZBeacon](https://github.com/goddanao/php-czmq/blob/master/api/ZBeacon.md), [ZUdp](https://github.com/goddanao/php-czmq/blob/master/api/ZUdp.md), [ZAuth](https://github.com/goddanao/php-czmq/blob/master/api/ZAuth.md), [ZCert](https://github.com/goddanao/php-czmq/blob/master/api/ZCert.md)
[ZYRE](https://github.com/zeromq/zyre) | Framework for proximity-based peer-to-peer applications | [Zyre\Zyre](https://github.com/goddanao/php-czmq/blob/master/api/Zyre-Zyre.md)
[FILEMQ](https://github.com/zeromq/filemq) | Publish-Subscribe file service | [FileMq\Server](https://github.com/goddanao/php-czmq/blob/master/api/FileMq-Server.md), [FileMq\Client](https://github.com/goddanao/php-czmq/blob/master/api/FileMq-Client.md)
[Malamute](https://github.com/zeromq/malamute) | All the enterprise messaging patterns in one box. Requires libzmq 4.2.0+ [(docs)](https://github.com/zeromq/malamute/blob/master/MALAMUTE.md) | [Malamute\Broker](https://github.com/goddanao/php-czmq/blob/master/api/Malamute-Broker.md), [Malamute\Worker](https://github.com/goddanao/php-czmq/blob/master/api/Malamute-Worker.md), [Malamute\Client](https://github.com/goddanao/php-czmq/blob/master/api/Malamute-Client.md), [Malamute\Producer](https://github.com/goddanao/php-czmq/blob/master/api/Malamute-Producer.md), [Malamute\Consumer](https://github.com/goddanao/php-czmq/blob/master/api/Malamute-Consumer.md)
[Majordomo](https://github.com/zeromq/majordomo) | Reliable service-oriented request-reply dialog between a set of client applications, a broker and a set of worker applications. [(docs)](http://rfc.zeromq.org/spec:18) | [Majordomo\Broker](https://github.com/goddanao/php-czmq/blob/master/api/Majordomo-Broker.md), [Majordomo\Worker](https://github.com/goddanao/php-czmq/blob/master/api/Majordomo-Worker.md), [Majordomo\Client](https://github.com/goddanao/php-czmq/blob/master/api/Majordomo-Client.md), [Majordomo\Titanic](https://github.com/goddanao/php-czmq/blob/master/api/Majordomo-Titanic.md)

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

Fetch, build and install required libraries

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

Build and install

```
make
sudo make install
```

The installer puts php-czmq.ini config file in ```/etc/php5/mods-available```, modify your php.ini to include "extension=php-czmq.so" or make a symbolic link in ```/etc/php5/cli/conf.d/20-php-czmq.ini``` or ```/etc/php5/apache2/conf.d/20-php-czmq.ini``` for default loading in cli and in apache.
Otherwise there is a docker config for building the test environment.


## Usage
Still to come... Take a look at the [Api](https://github.com/goddanao/php-czmq/blob/master/api/ApiIndex.md), [Ide Helper](https://github.com/goddanao/php-czmq/blob/master/ide_helper.php), [Examples](https://github.com/goddanao/php-czmq/tree/master/examples), [Tests](https://github.com/goddanao/php-czmq/tree/master/tests).
