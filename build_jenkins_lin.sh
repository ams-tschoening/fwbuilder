#!/bin/bash

set -e -x

rm    -rf "build"
mkdir -p  "build"
pushd     "build"

cmake ".."
make -j$(nproc --ignore=1)
popd
