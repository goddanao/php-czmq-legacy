#!/usr/bin/env bash

# Build, check, and install libsodium if WITH_LIBSODIUM is set
if [ -n "$WITH_LIBSODIUM" ]; then
    git clone git://github.com/jedisct1/libsodium.git &&
    ( cd libsodium; ./autogen.sh && ./configure &&
        make -j4 check && make -j4 &&  sudo make install && sudo ldconfig && cd ..) || exit 1
fi

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
    make -j4 check CFLAGS="-w" && make -j4 CFLAGS="-w" &&  sudo make install && sudo ldconfig && cd ..) || exit 1

# Build, check, and install the version of MALAMUTE given by MALAMUTE_REPO
git clone git://github.com/zeromq/${MALAMUTE_REPO}.git &&
( cd ${MALAMUTE_REPO}; ./autogen.sh && ./configure &&
    make -j4 check && make -j4 &&  sudo make install && sudo ldconfig && cd ..) || exit 1

# Build and install PHP-CPP
git clone git://github.com/CopernicaMarketingSoftware/PHP-CPP.git &&
( cd PHP-CPP; make -j4 && sudo make install && sudo ldconfig && cd ..) || exit 1

# Build and install PHP-CZMQ
(make -j4 VERBOSE=1 && sudo make install) || exit 1

# Run PhpUnit tests
(cp czmq.so ~/.phpenv/versions/$(phpenv version-name)/lib/php/extensions/no-debug-zts-20131226/ && echo "extension=czmq.so" >> ~/.phpenv/versions/$(phpenv version-name)/etc/php.ini && phpunit) || exit 1