#!/bin/sh
rm -rf ./vendoor
mkdir -p ./vendor
git clone --branch 1.0.2 https://github.com/jedisct1/libsodium.git ./libsodium
cd ./libsodium
./autogen.sh
./configure
make check
sudo make install
sudo ldconfig
cd ..

git clone --branch v4.1.0 git://github.com/zeromq/zeromq4-1.git ./libzmq
cd ./libzmq
./autogen.sh
./configure
make check
sudo make install
sudo ldconfig
cd ..

git clone --branch v3.0.0 git://github.com/zeromq/czmq.git ./czmq
cd ./czmq
./autogen.sh
./configure
make check
sudo make install
sudo ldconfig
cd ..

git clone git://github.com/CopernicaMarketingSoftware/PHP-CPP.git ./phpcpp
cd ./phpcpp
./autogen.sh
./configure
make check
sudo make install
sudo ldconfig
cd ..


