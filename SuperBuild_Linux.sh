#!/bin/sh

set -x

BUILD_TYPE=Release
if [ "$#" -eq 1 ]; then
    BUILD_TYPE=$1
fi

export FEATHER_TK_API=GL_4_1
export FEATHER_TK_NFD=OFF
export FEATHER_TK_PYTHON=OFF
export FEATHER_TK_TESTS=ON
export FEATHER_TK_EXAMPLES=ON
export FEATHER_TK_GCOV=OFF

sh feather-tk/etc/Linux/linux-build-gha.sh $BUILD_TYPE
