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
export CMAKE_OSX_DEPLOYMENT_TARGET=10.15
export CMAKE_OSX_ARCHITECTURES=arm64

sh feather-tk/etc/macOS/macos-build-gha.sh $BUILD_TYPE
