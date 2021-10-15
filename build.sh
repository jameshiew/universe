#!/usr/bin/env bash

set -eou pipefail

if ! conan remote list | grep public-conan; then
	conan remote add public-conan https://bincrafters.jfrog.io/artifactory/api/conan/public-conan
fi
conan config set general.revisions_enabled=1
mkdir -p build/
cd build/
conan install --build missing ..
cmake ..
make
