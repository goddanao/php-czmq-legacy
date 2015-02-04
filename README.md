PHP-CZMQ
================
Experimental php binding for [CZMQ](http://czmq.zeromq.org) built with [PHP-CPP](http://www.php-cpp.com/).

**DISCLAIMER:** It's my first (early stage) approach to c++, this project need to be considered highly experimental thus open to your suggestions/improvements. Please be patient! ;-)

##Motivation

The official ZeroMq php binding doesn't cover the CZMQ Api 3, Zyre and others interesting projects/patterns from the ZeroMq community and i whish to implement my first php extension using [PHP-CPP](http://www.php-cpp.com/).

##Status

The project wraps most of the CZMQ api and components in easy to use php components. It's in a early stage, please use it only for testing.

----------------

## Build
Install the required libraries, clone this repo and do a standard make/make install.

###Requirements
To build php-czmq you need to install these libraries:
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
