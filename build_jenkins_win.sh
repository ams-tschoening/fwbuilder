#!/bin/bash

set -e -x
export PATH=$PATH:/opt/mxe/usr/bin

LNK_DEST="/home/Datenserver/Software/System Management/fwbuilder"
LNK_FNAME=fwbuilder-*.exe

rm    -rf "build"
mkdir -p  "build"
pushd     "build"

# The following only works if the executing user has write access to ".ccache" of MXE, as that is
# used by default. Might make sense to add a group like "mxe_ccache_use" and put user in there, so
# that write permissions can be managed easily for all users.
#
# https://github.com/mxe/mxe/issues/2311#issuecomment-622369525
i686-w64-mingw32.shared-cmake ".."
make -j$(nproc --ignore=1)

# Build the installer and make it easily accessible publicly. The additional tools have been a 
# submodule in the past, but it seems easier currently to simply get those as necessary, being most
# up-to-date this way and not polluting builds which don't need them.
make install
pushd "release"
git clone https://github.com/fwbuilder/w32-bin.git
makensis "fwbuilder.nsi"
find "." -name "${LNK_FNAME}" -exec ln --force -t "${LNK_DEST}" {} +
popd
popd
