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

### Required Libraries
```
# libsodium
git clone --branch 1.0.2 https://github.com/jedisct1/libsodium.git ./libsodium
cd ./libsodium
./autogen.sh
./configure
make check
sudo make install
sudo ldconfig
cd ..

# libzmq
git clone --branch v4.1.0 git://github.com/zeromq/zeromq4-1.git ./libzmq
cd ./libzmq
./autogen.sh
./configure
make check
sudo make install
sudo ldconfig
cd ..

# czmq
git clone --branch v3.0.0 git://github.com/zeromq/czmq.git ./czmq
cd ./czmq
./autogen.sh
./configure
make check
sudo make install
sudo ldconfig
cd ..

# phpcpp
git clone git://github.com/CopernicaMarketingSoftware/PHP-CPP.git ./phpcpp
cd ./phpcpp
./autogen.sh
./configure
make check
sudo make install
sudo ldconfig
cd ..
```

## Usage
still to come... Take a look at the php tests and at [CZMQ manual](http://czmq.zeromq.org/manual:_start) 