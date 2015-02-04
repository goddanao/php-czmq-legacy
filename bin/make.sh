#!/bin/sh
make clean
make -j8
sudo make install
make clean