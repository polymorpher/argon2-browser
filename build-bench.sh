#!/usr/bin/env bash

set -e
set -o pipefail

cmake \
    -DOUTPUT_NAME="bench" \
    -DCMAKE_VERBOSE_MAKEFILE=OFF \
    -DCMAKE_BUILD_TYPE=MinSizeRel \
    -Dbench="1" \
    -DCMAKE_C_FLAGS="-O3" \
    .
cmake --build .

./clean-cmake.sh