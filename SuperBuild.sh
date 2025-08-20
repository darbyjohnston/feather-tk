#!/bin/bash

set -x

BUILD_TYPE=Release
if [ "$#" -eq 1 ]; then
    BUILD_TYPE=$1
fi

FEATHER_TK_API=GL_4_1
FEATHER_TK_NFD=OFF
FEATHER_TK_PYTHON=ON
FEATHER_TK_TESTS=ON
FEATHER_TK_EXAMPLES=ON
FEATHER_TK_GCOV=ON

bash feather-tk/etc/Linux/linux-build-gha.sh $BUILD_TYPE
