PHP-CZMQ
================
Experimental php binding for [CZMQ](http://czmq.zeromq.org) built with [PHP-CPP](http://www.php-cpp.com/).
**DISCLAIMER:** It's my first (early stage) approach to c++, this project need to be considered highly experimental thus open to your suggestions/improvements. Please be patient! ;-)

##Motivation
The official ZeroMq php binding doesn't cover the CZMQ Api 3, Zyre and others interesting projects/patterns from the ZeroMq community and i whish to implement my first php extension using [PHP-CPP](http://www.php-cpp.com/).

##Status
The project wraps most of the CZMQ api in easy to use php components. It's in a early stage, please use it only for testing.

## Build
Install the required libraries, clone this repo and do a standard make/make install. The installer puts czmq.ini config file in ```/etc/php5/mods-available```, modify your php.ini to include "extension=czmq.so" or make a symbolic link in ```/etc/php5/cli/conf.d/20-czmq.ini``` or ```/etc/php5/apache2/conf.d/20-czmq.ini``` for default loading in cli and in apache.
Otherwise use docker! There is a docker config for building the test enviroment.

### Install Required Libraries
```
git clone git://github.com/jedisct1/libsodium.git
git clone git://github.com/zeromq/libzmq.git
git clone git://github.com/zeromq/czmq.git
git clone git://github.com/zeromq/zyre.git
git clone git://github.com/malamute/malamute-core.git
for project in libsodium libzmq czmq zyre malamute-core; do
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
still to come... Take a look at the php tests and at [CZMQ manual](http://czmq.zeromq.org/manual:_start)
