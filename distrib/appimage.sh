#!/bin/bash
set -xe
mkdir -p build
cd build
cmake .. -DCMAKE_INSTALL_PREFIX=/usr

make -j$(nproc)

make install DESTDIR=./distrib/temp/AppDir