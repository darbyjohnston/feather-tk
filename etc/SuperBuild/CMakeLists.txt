cmake_minimum_required(VERSION 3.31)
cmake_policy(SET CMP0091 NEW)
cmake_policy(SET CMP0114 NEW)
if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()

project(feather-tk-SuperBuild)

#-------------------------------------------------------------------------------
# Options

set(feather_tk_UI_LIB ON CACHE BOOL "Build the user interface library")
set(feather_tk_API "GL_4_1" CACHE STRING "Graphics API (GL_4_1, GL_4_1_Debug, GLES_2)")
set(feather_tk_ZLIB ON CACHE BOOL "Build ZLIB")
set(feather_tk_nlohmann_json ON CACHE BOOL "Build nlohmann_json")
set(feather_tk_PNG ON CACHE BOOL "Build PNG")
set(feather_tk_Freetype ON CACHE BOOL "Build Freetype")
set(feather_tk_lunasvg ON CACHE BOOL "Build lunasvg")
set(feather_tk_SDL2 TRUE CACHE BOOL "Enable support for SDL2")
set(feather_tk_SDL3 FALSE CACHE BOOL "Enable support for SDL3")
set(feather_tk_nfd_DEFAULT OFF)
if(WIN32 OR APPLE)
    set(feather_tk_nfd_DEFAULT ON)
endif()
set(feather_tk_nfd ${feather_tk_nfd_DEFAULT} CACHE BOOL "Build support for native file dialogs")
set(feather_tk_PYTHON OFF CACHE BOOL "Build support for Python")
set(feather_tk_TESTS ON CACHE BOOL "Enable tests")
set(feather_tk_EXAMPLES ON CACHE BOOL "Enable examples")
if(APPLE)
    set(feather_tk_IGNORE_PREFIX_PATH_DEFAULT /opt/homebrew)
endif()
set(feather_tk_IGNORE_PREFIX_PATH ${feather_tk_IGNORE_PREFIX_PATH_DEFAULT} CACHE STRING "Ignore the given prefix path")
set(feather_tk_TOOLS_INSTALL "bin" CACHE STRING "Destination where tools will be installed")
set(feather_tk_GCOV FALSE CACHE BOOL "Enable gcov code coverage")
set(feather_tk_GPROF FALSE CACHE BOOL "Enable gprof code profiling")

#-------------------------------------------------------------------------------
# Configuration

list(PREPEND CMAKE_MODULE_PATH
    ${PROJECT_SOURCE_DIR}/../../cmake/Modules
    ${PROJECT_SOURCE_DIR}/cmake/Modules)

if(NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 17)
endif()
if(NOT BUILD_SHARED_LIBS)
    set(BUILD_SHARED_LIBS OFF)
endif()
if(NOT CMAKE_POSITION_INDEPENDENT_CODE)
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)
endif()
if(feather_tk_IGNORE_PREFIX_PATH)
    set(CMAKE_IGNORE_PREFIX_PATH ${feather_tk_IGNORE_PREFIX_PATH})
endif()
if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY MultiThreaded$<$<CONFIG:Debug>:Debug>DLL)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /MP")
endif()
if(APPLE)
    set(CMAKE_FIND_FRAMEWORK LAST)
endif()

# https://stackoverflow.com/questions/45414507/pass-a-list-of-prefix-paths-to-externalproject-add-in-cmake-args
string(REPLACE ";" "|" CMAKE_MODULE_PATH_TMP "${CMAKE_MODULE_PATH}")
string(REPLACE ";" "|" CMAKE_PREFIX_PATH_TMP "${CMAKE_PREFIX_PATH}")

set(feather_tk_DEPS_ARGS
    -DCMAKE_MODULE_PATH=${CMAKE_MODULE_PATH_TMP}
    -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}
    -DCMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH_TMP}
    -DCMAKE_IGNORE_PREFIX_PATH=${CMAKE_IGNORE_PREFIX_PATH}
    -DCMAKE_POLICY_DEFAULT_CMP0091:STRING=NEW
    -DCMAKE_POLICY_DEFAULT_CMP0114:STRING=NEW
    -DCMAKE_FIND_FRAMEWORK=${CMAKE_FIND_FRAMEWORK}
    -DCMAKE_CXX_STANDARD=${CMAKE_CXX_STANDARD}
    -DCMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}
    -DCMAKE_C_FLAGS=${CMAKE_C_FLAGS}
    -DCMAKE_MSVC_RUNTIME_LIBRARY=${CMAKE_MSVC_RUNTIME_LIBRARY}
    -DCMAKE_VERBOSE_MAKEFILE=${CMAKE_VERBOSE_MAKEFILE}
    -DCMAKE_OSX_DEPLOYMENT_TARGET=${CMAKE_OSX_DEPLOYMENT_TARGET}
    -DCMAKE_OSX_ARCHITECTURES=${CMAKE_OSX_ARCHITECTURES}
    -DBUILD_SHARED_LIBS=${BUILD_SHARED_LIBS}
    -DCMAKE_POSITION_INDEPENDENT_CODE=${CMAKE_POSITION_INDEPENDENT_CODE})
string(REPLACE ";" " " feather_tk_DEPS_ARGS_TMP "${feather_tk_DEPS_ARGS}")
message("feather_tk_DEPS_ARGS: " ${feather_tk_DEPS_ARGS_TMP})

#-------------------------------------------------------------------------------
# Build

if(feather_tk_ZLIB)
    include(BuildZLIB)
endif()
if(feather_tk_nlohmann_json)
    include(Buildnlohmann_json)
endif()
if(feather_tk_PNG)
    include(BuildPNG)
endif()
if(feather_tk_Freetype)
    include(BuildFreetype)
endif()
if(feather_tk_lunasvg)
    include(Buildlunasvg)
endif()
if(feather_tk_UI_LIB)
    if(feather_tk_SDL2)
        include(BuildSDL2)
    endif()
    if(feather_tk_SDL3)
        include(BuildSDL3)
    endif()
    if(feather_tk_nfd)
        include(Buildnfd)
    endif()
    if(feather_tk_PYTHON)
        include(Buildpybind11)
    endif()
endif()
