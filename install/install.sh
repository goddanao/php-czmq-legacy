#!/usr/bin/env bash

# Installs libsodium.
install_libsodium() {

    pushd /tmp

    git clone https://github.com/jedisct1/libsodium
    cd libsodium

    if [ $LIBSODIUM_VERSION != "master" ]; then
        if [ ${#LIBSODIUM_VERSION} == 40 ]; then
            git reset --hard $LIBSODIUM_VERSION
        else
            git checkout "tags/${LIBSODIUM_VERSION}"
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
    v4.0*)
        git clone https://github.com/zeromq/zeromq4-x
        cd zeromq4-x
        git checkout "tags/${ZEROMQ_VERSION}"
       ;;
    v4.1*)
        git clone https://github.com/zeromq/zeromq4-1
        cd zeromq4-1
        git checkout "tags/${ZEROMQ_VERSION}"
        ;;
    *)
        git clone https://github.com/zeromq/libzmq
        cd libzmq
        if [ $ZEROMQ_VERSION != "master" ]; then
            if [ ${#ZEROMQ_VERSION} == 40 ]; then
                git reset --hard $ZEROMQ_VERSION
            else
                git checkout "tags/${ZEROMQ_VERSION}"
            fi
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
      if [ ${#CZMQ_VERSION} == 40 ]; then
        git reset --hard $CZMQ_VERSION
      else
        git checkout "tags/${CZMQ_VERSION}"
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
      if [ ${#ZYRE_VERSION} == 40 ]; then
        git reset --hard $ZYRE_VERSION
      else
        git checkout "tags/${ZYRE_VERSION}"
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
      if [ ${#MAJORDOMO_VERSION} == 40 ]; then
        git reset --hard $MAJORDOMO_VERSION
      else
        git checkout "tags/${MAJORDOMO_VERSION}"
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


install_malamute() {

  pushd /tmp

  git clone https://github.com/zeromq/malamute
  cd malamute

  if [ $MALAMUTE_VERSION != "master" ]; then
      if [ ${#MALAMUTE_VERSION} == 40 ]; then
        git reset --hard $MALAMUTE_VERSION
      else
        git checkout "tags/${MALAMUTE_VERSION}"
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


install_filemq() {

  pushd /tmp

  git clone https://github.com/zeromq/filemq
  cd filemq

  if [ $FILEMQ_VERSION != "master" ]; then
      if [ ${#FILEMQ_VERSION} == 40 ]; then
        git reset --hard $FILEMQ_VERSION
      else
        git checkout "tags/${FILEMQ_VERSION}"
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

install_phpcpp() {

  pushd /tmp

  git clone https://github.com/CopernicaMarketingSoftware/PHP-CPP
  cd PHP-CPP

  if [ $PHPCPP_VERSION != "master" ]; then
      if [ ${#PHPCPP_VERSION} == 40 ]; then
        git reset --hard $PHPCPP_VERSION
      else
        git checkout "tags/${PHPCPP_VERSION}"
      fi
  fi

  make -j 8
  sudo make install
  sudo ldconfig
  cd ..

  popd # pushd /tmp
}

install_msgpack() {

  pushd /tmp

  git clone https://github.com/msgpack/msgpack-c.git
  cd msgpack-c

  if [ $MSGPACK_VERSION != "master" ]; then
      if [ ${#MSGPACK_VERSION} == 40 ]; then
        git reset --hard $MSGPACK_VERSION
      else
        git checkout "tags/${MSGPACK_VERSION}"
      fi
  fi

  cmake -DMSGPACK_CXX11=ON .
  sudo make install
  sudo ldconfig
  cd ..

  popd # pushd /tmp
}

install_bson() {

  pushd /tmp

  git clone https://github.com/mongodb/libbson.git
  cd libbson

  if [ $BSON_VERSION != "master" ]; then
      if [ ${#BSON_VERSION} == 40 ]; then
        git reset --hard $BSON_VERSION
      else
        git checkout "tags/${BSON_VERSION}"
      fi
  fi

  ./autogen.sh
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

# Malamute works with libzmq v4.2.0+ wich is current dev/master
if [ $ZEROMQ_VERSION == "master" ] || [ ${#ZEROMQ_VERSION} == 40 ]; then
    install_malamute
    export LINKER_DEPENDENCIES="-lphpcpp -lzmq -lczmq -lzyre -lmajordomo -lfilemq -lbson-1.0 -lmlm"
else
    export LINKER_DEPENDENCIES="-lphpcpp -lzmq -lczmq -lzyre -lmajordomo -lfilemq -lbson-1.0"
fi

install_filemq
install_phpcpp
install_msgpack
install_bson

# Build and install PHP-CZMQ
(make -j8 VERBOSE=1 && sudo make install && sudo ldconfig) || exit 1

# Install the extension in the current phpenv
(cp php-czmq.so `php-config --extension-dir` && echo "extension=php-czmq.so" >> `php-config --prefix`/etc/php.ini) || exit 1

