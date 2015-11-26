#!/usr/bin/env bash

# Cache dirs
#LIBSODIUM_DIR="${TRAVIS_BUILD_DIR}/travis/cache/libsodium/${LIBSODIUM_VERSION}"
#ZEROMQ_DIR="${TRAVIS_BUILD_DIR}/travis/cache/zeromq/${ZEROMQ_VERSION}"
#CZMQ_DIR="${TRAVIS_BUILD_DIR}/travis/cache/czmq/${CZMQ_VERSION}"
#ZYRE_DIR="${TRAVIS_BUILD_DIR}/travis/cache/zyre/${ZYRE_VERSION}"
#MAJORDOMO_DIR="${TRAVIS_BUILD_DIR}/travis/cache/majordomo/${MAJORDOMO_VERSION}"
#MALAMUTE_DIR="${TRAVIS_BUILD_DIR}/travis/cache/malamute/${MALAMUTE_VERSION}"
#FILEMQ_DIR="${TRAVIS_BUILD_DIR}/travis/cache/filemq/${FILEMQ_VERSION}"

# Installs libsodium.
install_libsodium() {
    pushd /tmp

    git clone https://github.com/jedisct1/libsodium
    cd libsodium
    if [ $LIBSODIUM_VERSION != "master" ]; then
        git checkout "tags/${LIBSODIUM_VERSION}"
    fi
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

    case $ZEROMQ_VERSION in
    v2.2.0)
        wget http://download.zeromq.org/zeromq-2.2.0.tar.gz
        tar -xf zeromq-2.2.0.tar.gz
        cd zeromq-2.2.0
        ;;
    v3*)
        git clone https://github.com/zeromq/zeromq3-x
        cd zeromq3-x
        git checkout "tags/${ZEROMQ_VERSION}"
        ;;
    v4.1*)
        git clone https://github.com/zeromq/zeromq4-1
        cd zeromq4-1
        git checkout "tags/${ZEROMQ_VERSION}"
        ;;
    v4*)
        git clone https://github.com/zeromq/zeromq4-x
        cd zeromq4-x
        git checkout "tags/${ZEROMQ_VERSION}"
       ;;
    master*)
        git clone https://github.com/zeromq/libzmq
        cd libzmq
        if [ $ZEROMQ_HASH != "" ]; then
            git reset --hard $ZEROMQ_HASH
        fi
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
  if [ $CZMQ_VERSION != "master" ]; then
        git checkout "tags/${CZMQ_VERSION}"
  else
    if [ $CZMQ_HASH != "" ]; then
        git reset --hard $CZMQ_HASH
    fi
  fi
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
  if [ $ZYRE_VERSION != "master" ]; then
        git checkout "tags/${ZYRE_VERSION}"
  else
    if [ $ZYRE_HASH != "" ]; then
        git reset --hard $ZYRE_HASH
    fi
  fi
  ./autogen.sh
  ./configure
  make -j 8
  sudo make install
  sudo ldconfig
  cd ..

  popd # pushd /tmp
}


install_majordomo() {

  pushd /tmp

  git clone https://github.com/zeromq/majordomo
  cd majordomo
  if [ $MAJORDOMO_VERSION != "master" ]; then
        git checkout "tags/${MAJORDOMO_VERSION}"
  fi
  ./autogen.sh
  ./configure
  make -j 8
  sudo make install
  sudo ldconfig
  cd ..

  popd # pushd /tmp
}


install_malamute() {

  pushd /tmp

  git clone https://github.com/zeromq/malamute
  cd malamute
  if [ $MALAMUTE_VERSION != "master" ]; then
        git checkout "tags/${MALAMUTE_VERSION}"
  fi
  ./autogen.sh
  ./configure
  make -j 8
  sudo make install
  sudo ldconfig
  cd ..

  popd # pushd /tmp
}


install_filemq() {

  pushd /tmp

  git clone https://github.com/zeromq/filemq
  cd filemq
  if [ $FILEMQ_VERSION != "master" ]; then
        git checkout "tags/${FILEMQ_VERSION}"
  fi
  ./autogen.sh
  ./configure
  make -j 8
  sudo make install
  sudo ldconfig
  cd ..

  popd # pushd /tmp
}

install_phpcpp() {

  pushd /tmp

  git clone https://github.com/CopernicaMarketingSoftware/PHP-CPP
  cd PHP-CPP
  if [ $PHPCPP_VERSION != "master" ]; then
        git checkout "tags/${PHPCPP_VERSION}"
  fi
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
install_majordomo
install_malamute
install_filemq
install_phpcpp

# Build and install PHP-CZMQ
(make -j8 VERBOSE=1 && sudo make install && sudo ldconfig) || exit 1

# Install the extension in the current phpenv
(cp php-czmq.so `php-config --extension-dir` && echo "extension=php-czmq.so" >> `php-config --prefix`/etc/php.ini) || exit 1

composer update

# Run PhpUnit tests
$(which phpunit) -dzend.enable_gc=0

