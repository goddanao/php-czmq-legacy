#!/usr/bin/env bash

install_libsodium() {
    pushd /tmp

    git clone https://github.com/jedisct1/libsodium
    cd libsodium
    git checkout "tags/${LIBSODIUM_VERSION}"
    ./autogen.sh
    ./configure
    make -j 8
    sudo make install
    sudo ldconfig
    cd ..

    popd # pushd /tmp
}

install_zeromq() {

    pushd /tmp

    case $version in
    v2.2.0)
        wget http://download.zeromq.org/zeromq-2.2.0.tar.gz
        tar -xf zeromq-2.2.0.tar.gz
        cd zeromq-2.2.0
        ;;
    v3*)
        git clone https://github.com/zeromq/zeromq3-x
        cd zeromq3-x
        git checkout "tags/${version}"
        ;;
    v4.1*)
        git clone https://github.com/zeromq/zeromq4-1
        cd zeromq4-1
        git checkout "tags/${version}"
        ;;
    v4*)
        git clone https://github.com/zeromq/zeromq4-x
        cd zeromq4-x
        git checkout "tags/${version}"
        ;;
    esac
    ./autogen.sh
    ./configure
    make -j 8
    sudo make install
    sudo ldconfig
    cd ..

    popd # pushd /tmp
}

install_czmq() {

  pushd /tmp

  git clone https://github.com/zeromq/czmq
  cd czmq
  git checkout "tags/${CZMQ_VERSION}"
  ./autogen.sh
  ./configure
  make -j 8
  sudo make install
  sudo ldconfig
  cd ..

  popd # pushd /tmp
}

install_zyre() {

  pushd /tmp

  git clone https://github.com/zeromq/zyre
  cd zyre
  git checkout "tags/${ZYRE_VERSION}"
  ./autogen.sh
  ./configure
  make -j 8
  sudo make install
  sudo ldconfig
  cd ..

  popd # pushd /tmp
}
install_libsodium
install_zeromq
install_czmq
install_zyre

# Build, check, and install the version of MALAMUTE given by MALAMUTE_REPO
git clone git://github.com/zeromq/majordomo.git &&
( cd majordomo; ./autogen.sh && ./configure &&
    make -j4 check && make -j4 &&  sudo make install && sudo ldconfig && cd ..) || exit 1

# Build, check, and install the version of MALAMUTE given by MALAMUTE_REPO
git clone git://github.com/zeromq/malamute.git &&
( cd malamute; ./autogen.sh && ./configure &&
    make -j4 check && make -j4 &&  sudo make install && sudo ldconfig && cd ..) || exit 1

# Build, check, and install the version of FILEMQ given by FILEMQ_REPO
git clone git://github.com/zeromq/filemq.git &&
( cd filemq; ./autogen.sh && ./configure &&
    make -j4 check && make -j4 &&  sudo make install && sudo ldconfig && cd ..) || exit 1

# Build and install PHP-CPP (-b 'v1.5' --single-branch --depth 1)
git clone git://github.com/CopernicaMarketingSoftware/PHP-CPP.git &&
( cd PHP-CPP; make -j4 && sudo make install && sudo ldconfig && cd ..) || exit 1

# Build and install PHP-CZMQ
(make -j4 VERBOSE=1 && sudo make install && sudo ldconfig) || exit 1

# Install the extension in the current phpenv
(cp php-czmq.so `php-config --extension-dir` && echo "extension=php-czmq.so" >> `php-config --prefix`/etc/php.ini) || exit 1

composer update

# Run PhpUnit tests
php -dzend.enable_gc=0 $(which phpunit)

# Detect Memory Leaks
# USE_ZEND_ALLOC=0 ZEND_DONT_UNLOAD_MODULES=1 valgrind --log-file=./czmq.log php ~/.phpenv/versions/$(phpenv version-name)/bin/phpunit
# USE_ZEND_ALLOC=0 ZEND_DONT_UNLOAD_MODULES=1 gdb php ~/.phpenv/versions/$(phpenv version-name)/bin/phpunit

