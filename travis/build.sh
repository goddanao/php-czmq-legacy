#!/usr/bin/env bash

LIBSODIUM_DIR="${TRAVIS_BUILD_DIR}/travis/cache/libsodium/v${LIBSODIUM_VERSION}"
CZMQ_DIR="${TRAVIS_BUILD_DIR}/travis/cache/czmq/${CZMQ_VERSION}"

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
    ./configure
    make -j 8
    sudo make install
    sudo ldconfig
    cd ..

    popd # pushd /tmp
}

install_zeromq() {
    local version=$ZEROMQ_VERSION
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
    PKG_CONFIG_PATH="${LIBSODIUM_DIR}/lib/pkgconfig" ./configure $with_libsodium
    make -j 8
    sudo make install
    sudo ldconfig
    cd ..

    popd # pushd /tmp
}

install_czmq() {
  local zeromq_version=$ZEROMQ_VERSION
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
  # git checkout "tags/${ZYRE_VERSION}"
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
  # git checkout "tags/${MAJORDOMO_VERSION}"
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
  cd majordomo
  # git checkout "tags/${MALAMUTE_VERSION}"
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
  cd majordomo
  # git checkout "tags/${FILEMQ_VERSION}"
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
  # git checkout "tags/${PHP-CPP_VERSION}"
  # ./autogen.sh
  # ./configure
  make -j 8
  sudo make install
  sudo ldconfig
  cd ..

  popd # pushd /tmp
}



#install_libsodium
#install_zeromq
#install_czmq
#install_zyre
#install_majordomo
#install_malamute
#install_filemq
#install_phpcpp

pushd /tmp
git clone git://github.com/jedisct1/libsodium.git
git clone git://github.com/zeromq/libzmq.git
git clone git://github.com/zeromq/czmq.git
git clone git://github.com/zeromq/zyre.git
git clone git://github.com/zeromq/majordomo.git
git clone git://github.com/zeromq/filemq.git
git clone git://github.com/zeromq/malamute.git
for project in libsodium libzmq czmq zyre majordomo filemq malamute; do
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

popd
# Build and install PHP-CZMQ
(make -j8 VERBOSE=1 && sudo make install && sudo ldconfig) || exit 1

# Install the extension in the current phpenv
(cp php-czmq.so `php-config --extension-dir` && echo "extension=php-czmq.so" >> `php-config --prefix`/etc/php.ini) || exit 1

composer update

# Run PhpUnit tests
php -dzend.enable_gc=0 $(which phpunit)

# Detect Memory Leaks
# USE_ZEND_ALLOC=0 ZEND_DONT_UNLOAD_MODULES=1 valgrind --log-file=./czmq.log php ~/.phpenv/versions/$(phpenv version-name)/bin/phpunit
# USE_ZEND_ALLOC=0 ZEND_DONT_UNLOAD_MODULES=1 gdb php ~/.phpenv/versions/$(phpenv version-name)/bin/phpunit

