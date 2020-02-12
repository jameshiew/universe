#!/usr/bin/env bash

set -eoux

conan remote add public-conan https://api.bintray.com/conan/bincrafters/public-conan
mkdir -p build/
cd build/
conan install --build missing ..
cmake ..
make
