PHP-CZMQ [![Build Status](https://travis-ci.org/goddanao/php-czmq.svg)](https://travis-ci.org/goddanao/php-czmq)
================
Experimental php (5.4+) binding for [CZMQ](http://czmq.zeromq.org), [ZYRE](https://github.com/zeromq/zyre), [FILEMQ](https://github.com/zeromq/filemq), [Malamute](https://github.com/Malamute/malamute-core), [Majordomo Pattern V1](http://rfc.zeromq.org/spec:7), [Majordomo Pattern V2](http://rfc.zeromq.org/spec:18) built with [PHP-CPP](http://www.php-cpp.com/).
**DISCLAIMER:** It's my first (early stage) approach to c++, this project need to be considered highly experimental thus open to your suggestions/improvements. Please be patient! ;-)

##Motivation
The official ZeroMq php binding doesn't cover the CZMQ Api 3, Zyre, Malamute and other interesting projects/patterns from the ZeroMq community and i wish to implement my first php extension using [PHP-CPP](http://www.php-cpp.com/).

##Status
The project wraps most of the CZMQ api in easy to use php components. It's in a early stage, interfaces and classes are subject to changes, please use it only for testing.

##Dependencies
Name | Version | Status
--- | --- | --- | ---
libsodium | dev-master | [![Build Status](https://travis-ci.org/jedisct1/libsodium.svg)](https://travis-ci.org/jedisct1/libsodium?branch=master)
libzmq | dev-master | [![Build Status](https://travis-ci.org/zeromq/libzmq.svg)](https://travis-ci.org/zeromq/libzmq?branch=master) 
czmq | dev-master | [![Build Status](https://travis-ci.org/zeromq/czmq.svg)](https://travis-ci.org/zeromq/czmq?branch=master) 
zyre | dev-master | [![Build Status](https://travis-ci.org/zeromq/zyre.svg)](https://travis-ci.org/zeromq/zyre?branch=master)
malamute | dev-master | [![Build Status](https://travis-ci.org/zeromq/malamute.svg)](https://travis-ci.org/zeromq/malamute?branch=master)
majordomo | dev-master | [![Build Status](https://travis-ci.org/zeromq/majordomo.svg)](https://travis-ci.org/zeromq/majordomo?branch=master)
filemq | dev-master | [![Build Status](https://travis-ci.org/zeromq/filemq.svg)](https://travis-ci.org/zeromq/filemq?branch=master)


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
still to come... Take a look at the api, examples, php tests.
