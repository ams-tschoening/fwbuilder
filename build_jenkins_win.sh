#!/bin/bash

set -e -x
export PATH=$PATH:/opt/mxe/usr/bin

rm    -rf "build"
mkdir -p  "build"
pushd     "build"

# The following only works if the executing user has write access to ".ccache" of MXE, as that is
# used by default.
#
# https://github.com/mxe/mxe/issues/2311#issuecomment-622369525
i686-w64-mingw32.shared-cmake ".."
make -j$(nproc --ignore=1)
popd
