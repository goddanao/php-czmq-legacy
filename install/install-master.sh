#!/usr/bin/env bash
export LIBSODIUM_VERSION=master
export ZEROMQ_VERSION=master
export CZMQ_VERSION=master
export ZYRE_VERSION=master
export MAJORDOMO_VERSION=master
export FILEMQ_VERSION=master
export MALAMUTE_VERSION=master
export PHPCPP_VERSION=master
export MSGPACK_VERSION=master
export BSON_VERSION=master
bash `dirname ${BASH_SOURCE[0]}`/install.sh