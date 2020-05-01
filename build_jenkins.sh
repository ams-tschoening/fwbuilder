#!/bin/bash

set -e -x
export HOME=${WORKSPACE}

LNK_SRC="${WORKSPACE}/release/install-root"
LNK_DEST="/home/Datenserver/Software/System Management/fwbuilder"
LNK_FNAME=fwbuilder-*.exe

./build_mxe-w32.sh all
find "${LNK_SRC}" -name "${LNK_FNAME}" -exec ln --force -t "${LNK_DEST}" {} +

