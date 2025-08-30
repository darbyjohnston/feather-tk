#!/bin/sh

set -x

BUILD_TYPE=Release
if [ "$#" -eq 1 ]; then
    BUILD_TYPE=$1
fi

export FTK_API=GL_4_1
export FTK_NFD=OFF
export FTK_PYTHON=OFF
export FTK_TESTS=ON
export FTK_EXAMPLES=ON
export FTK_GCOV=OFF

sh feather-tk/etc/Linux/linux-build-gha.sh $BUILD_TYPE
