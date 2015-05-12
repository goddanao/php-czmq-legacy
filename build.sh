#!/usr/bin/env bash

# Build, check, and install the version of Libsodium given by LIBSODIUM_REPO
git clone git://github.com/jedisct1/${LIBSODIUM_REPO}.git &&
( cd ${LIBSODIUM_REPO}; ./autogen.sh && ./configure &&
    make -j4 check && make -j4 &&  sudo make install && sudo ldconfig && cd ..) || exit 1

# Build, check, and install the version of ZeroMQ given by ZMQ_REPO
git clone git://github.com/zeromq/${ZMQ_REPO}.git &&
( cd ${ZMQ_REPO}; ./autogen.sh && ./configure &&
    make -j4 check && make -j4 &&  sudo make install && sudo ldconfig && cd ..) || exit 1

# Build, check, and install the version of CZMQ given by CZMQ_REPO
git clone git://github.com/zeromq/${CZMQ_REPO}.git &&
( cd ${CZMQ_REPO}; ./autogen.sh && ./configure &&
    make -j4 check && make -j4 && sudo make install && sudo ldconfig && cd ..) || exit 1

# Build, check, and install the version of ZYRE given by ZYRE_REPO
git clone git://github.com/zeromq/${ZYRE_REPO}.git &&
( cd ${ZYRE_REPO}; ./autogen.sh && ./configure &&
    make -j4 check && make -j4 &&  sudo make install && sudo ldconfig && cd ..) || exit 1

# Build, check, and install the version of MALAMUTE given by MALAMUTE_REPO
git clone git://github.com/zeromq/${MALAMUTE_REPO}.git &&
( cd ${MALAMUTE_REPO}; ./autogen.sh && ./configure &&
    make -j4 check && make -j4 &&  sudo make install && sudo ldconfig && cd ..) || exit 1

# Build and install PHP-CPP
git clone git://github.com/CopernicaMarketingSoftware/PHP-CPP.git &&
( cd PHP-CPP; make -j4 && sudo make install && sudo ldconfig && cd ..) || exit 1

# Build and install PHP-CZMQ
(make -j4 VERBOSE=1 && sudo make install) || exit 1

# Install the extension
(cp czmq.so (ls -d ~/.phpenv/versions/$(phpenv version-name)/lib/php/extensions/no-debug-zts-* | head -1) && echo "extension=czmq.so" >> ~/.phpenv/versions/$(phpenv version-name)/etc/php.ini) || exit 1

# Run PhpUnit tests
cat ~/.phpenv/versions/$(phpenv version-name)/etc/php.ini