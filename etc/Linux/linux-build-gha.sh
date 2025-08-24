#!/bin/sh

set -x

BUILD_TYPE=$1

JOBS=4

cmake \
    -S feather-tk/etc/SuperBuild \
    -B sbuild-$BUILD_TYPE \
    -DCMAKE_BUILD_TYPE=$BUILD_TYPE \
    -DCMAKE_INSTALL_PREFIX=$PWD/install-$BUILD_TYPE \
    -DCMAKE_PREFIX_PATH=$PWD/install-$BUILD_TYPE \
    -Dfeather_tk_API=$FEATHER_TK_API \
    -Dfeather_tk_nfd=$FEATHER_TK_NFD \
    -Dfeather_tk_PYTHON=$FEATHER_TK_PYTHON
cmake --build sbuild-$BUILD_TYPE -j $JOBS --config $BUILD_TYPE

cmake \
    -S feather-tk \
    -B build-$BUILD_TYPE \
    -DCMAKE_INSTALL_PREFIX=$PWD/install-$BUILD_TYPE \
    -DCMAKE_PREFIX_PATH=$PWD/install-$BUILD_TYPE \
    -DCMAKE_BUILD_TYPE=$BUILD_TYPE \
    -Dfeather_tk_API=$FEATHER_TK_API \
    -Dfeather_tk_nfd=$FEATHER_TK_NFD \
    -Dfeather_tk_PYTHON=$FEATHER_TK_PYTHON \
    -Dfeather_tk_TESTS=$FEATHER_TK_TESTS \
    -Dfeather_tk_EXAMPLES=$FEATHER_TK_EXAMPLES \
    -Dfeather_tk_GCOV=$FEATHER_TK_GCOV
cmake --build build-$BUILD_TYPE -j $JOBS --config $BUILD_TYPE
cmake --build build-$BUILD_TYPE --config $BUILD_TYPE --target install
