#!/usr/bin/env bash

LIBSODIUM_VERSION="1.0.3"
CZMQ_VERSION="v2.2.0"

LIBSODIUM_DIR="${TRAVIS_BUILD_DIR}/travis/cache/libsodium/v${LIBSODIUM_VERSION}"
CZMQ_DIR="${TRAVIS_BUILD_DIR}/travis/cache/czmq/${CZMQ_VERSION}"

# Installs libsodium.
install_libsodium() {
    local cache_dir=$LIBSODIUM_DIR

    if test -d $cache_dir
    then
        return
    fi

    pushd /tmp

    git clone https://github.com/jedisct1/libsodium
    cd libsodium
    git checkout "tags/${LIBSODIUM_VERSION}"
    ./autogen.sh
    ./configure --prefix=$cache_dir
    make -j 8
    make install
    cd ..

    popd # pushd /tmp
}

# Installs the specified version of ØMQ.
#
# Parameters:
#
#     1 - The version of ØMQ to install, in the form "vx.y.z"
install_zeromq() {
    local version=$1
    local cache_dir="${TRAVIS_BUILD_DIR}/travis/cache/zeromq/${version}"
    local with_libsodium=""

    if test -d $cache_dir
    then
        return
    fi

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

        with_libsodium="--with-libsodium=${LIBSODIUM_DIR}"
        ;;
    esac
    ./autogen.sh
    PKG_CONFIG_PATH="${LIBSODIUM_DIR}/lib/pkgconfig" ./configure --prefix=$cache_dir $with_libsodium
    make -j 8
    make install
    cd ..

    popd # pushd /tmp
}

# Installs CZMQ.
#
# Parameters:
#
#     1 - The version of ØMQ that was installed
install_czmq() {
  local zeromq_version=$1
  local zeromq_dir="${TRAVIS_BUILD_DIR}/travis/cache/zeromq/${zeromq_version}"
  local cache_dir=$CZMQ_DIR

  if test -d $cache_dir
  then
      return
  fi

  pushd /tmp

  git clone https://github.com/zeromq/czmq
  cd czmq
  git checkout "tags/${CZMQ_VERSION}"
  ./autogen.sh
  ./configure \
    --prefix=$cache_dir \
    --with-libzmq=$zeromq_dir \
    --with-libsodium=$LIBSODIUM_DIR
  make -j 8
  make install
  cd ..

  popd # pushd /tmp
}


zeromq_version=$1
with_czmq=$2
build_dir=/tmp/build

install_libsodium
install_zeromq $zeromq_version

if [ "x${with_czmq}" = "xtrue" ]
then
    install_czmq $zeromq_version
fi

# Build, check, and install the version of ZYRE given by ZYRE_REPO
git clone git://github.com/zeromq/zyre.git &&
( cd zyre; ./autogen.sh && ./configure &&
    make -j4 check && make -j4 &&  sudo make install && sudo ldconfig && cd ..) || exit 1

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

