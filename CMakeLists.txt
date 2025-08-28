cmake_minimum_required(VERSION 3.31)
cmake_policy(SET CMP0091 NEW)
cmake_policy(SET CMP0114 NEW)
if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()

set(feather_tk_VERSION_MAJOR "0")
set(feather_tk_VERSION_MINOR "5")
set(feather_tk_VERSION_PATCH "0")
set(feather_tk_VERSION ${feather_tk_VERSION_MAJOR}.${feather_tk_VERSION_MINOR}.${feather_tk_VERSION_PATCH})
add_definitions(-Dfeather_tk_VERSION_MAJOR=${feather_tk_VERSION_MAJOR})
add_definitions(-Dfeather_tk_VERSION_MINOR=${feather_tk_VERSION_MINOR})
add_definitions(-Dfeather_tk_VERSION_PATCH=${feather_tk_VERSION_PATCH})
add_definitions(-Dfeather_tk_VERSION="${feather_tk_VERSION}")

project(
    feather-tk
    VERSION ${feather_tk_VERSION}
    LANGUAGES CXX C)

#-------------------------------------------------------------------------------
# Options

set(feather_tk_UI_LIB ON CACHE BOOL "Build the user interface library")
set(feather_tk_API "GL_4_1" CACHE STRING "Graphics API (GL_4_1, GL_4_1_Debug, GLES_2)")
set(feather_tk_nfd_DEFAULT OFF)
if(WIN32 OR APPLE)
    set(feather_tk_nfd_DEFAULT ON)
endif()
set(feather_tk_nfd ${feather_tk_nfd_DEFAULT} CACHE BOOL "Enable support for native file dialogs")
set(feather_tk_PYTHON OFF CACHE BOOL "Enable support for Python")
set(feather_tk_TESTS ON CACHE BOOL "Enable tests")
set(feather_tk_EXAMPLES ON CACHE BOOL "Enable examples")
if(APPLE)
    set(feather_tk_IGNORE_PREFIX_PATH_DEFAULT /opt/homebrew)
endif()
set(feather_tk_IGNORE_PREFIX_PATH ${feather_tk_IGNORE_PREFIX_PATH_DEFAULT} CACHE STRING "Ignore the given prefix path")
set(feather_tk_BUILD "default" CACHE STRING "Build configuration: 'default', 'SuperBuild', 'vcpkg'")
set(feather_tk_GCOV OFF CACHE BOOL "Enable gcov code coverage")
set(feather_tk_GPROF OFF CACHE BOOL "Enable gprof code profiling")

#-------------------------------------------------------------------------------
# Configuration

if(feather_tk_BUILD STREQUAL "SuperBuild")
    set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/Modules)
endif()

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

if(WIN32)
elseif(APPLE)
    set(CMAKE_INSTALL_RPATH "@executable_path/../lib")
    # \bug Should this be set automatically?
    if(CMAKE_BUILD_TYPE MATCHES "^Debug$")
        set(CMAKE_BUILD_RPATH "@executable_path/../../../install-Debug/lib")
    elseif (CMAKE_BUILD_TYPE MATCHES "^RelWithDebInfo$")
        set(CMAKE_BUILD_RPATH "@executable_path/../../../install-RelWithDebInfo/lib")
    elseif (CMAKE_BUILD_TYPE MATCHES "^Release$")
        set(CMAKE_BUILD_RPATH "@executable_path/../../../install-Release/lib")
    endif()
else()
    set(CMAKE_INSTALL_RPATH "$ORIGIN/../lib")
endif()

if(feather_tk_UI_LIB)
    add_definitions(-DFEATHER_TK_UI_LIB)
endif()

if(CMAKE_BUILD_TYPE MATCHES "^Debug$")
    add_definitions(-DFEATHER_TK_ASSERT)
endif()

if(feather_tk_TESTS)
    set(CTEST_OUTPUT_ON_FAILURE ON)
    enable_testing()
endif()

if(feather_tk_GCOV)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -fprofile-update=atomic")# -fkeep-inline-functions")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage -fprofile-update=atomic")# -fkeep-inline-functions")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage -fprofile-update=atomic")
endif()
if(feather_tk_GPROF)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pg")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pg")
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include_directories(lib)
if(feather_tk_TESTS)
    include_directories(tests)
endif()

#-------------------------------------------------------------------------------
# Dependencies

find_package(Threads REQUIRED)
find_package(ZLIB REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(PNG REQUIRED)
find_package(Freetype REQUIRED)
find_package(lunasvg REQUIRED)

if(feather_tk_UI_LIB)
    if ("${feather_tk_API}" STREQUAL "GL_4_1")
        include_directories(${PROJECT_SOURCE_DIR}/deps/glad_GL_4_1)
    elseif ("${feather_tk_API}" STREQUAL "GL_4_1_Debug")
        include_directories(${PROJECT_SOURCE_DIR}/deps/glad_GL_4_1_Debug)
    elseif ("${feather_tk_API}" STREQUAL "GLES_2")
        include_directories(${PROJECT_SOURCE_DIR}/deps/glad_GLES_2)
    endif()
    if ("${feather_tk_API}" STREQUAL "GL_4_1" OR
        "${feather_tk_API}" STREQUAL "GL_4_1_Debug" OR
        "${feather_tk_API}" STREQUAL "GLES_2")
        find_package(OpenGL REQUIRED)
        find_package(SDL2 REQUIRED)
        add_subdirectory(deps/glad_${feather_tk_API})
    endif()
    add_definitions(-DFEATHER_TK_API_${feather_tk_API})
    if(${feather_tk_API} STREQUAL "GL_4_1_Debug")
        add_definitions(-DFEATHER_TK_API_GL_4_1)
    endif()

    if(feather_tk_nfd)
        find_package(nfd)
        if(nfd_FOUND)
            add_definitions(-DFEATHER_TK_NFD)
        endif()
    endif()

    if(feather_tk_PYTHON)
        include_directories(python/lib)
        if(feather_tk_TESTS)
            include_directories(python/tests)
        endif()
        add_definitions(-DFEATHER_TK_PYTHON)
        find_package(Python3 REQUIRED Interpreter Development)
        find_package(pybind11 REQUIRED)
    endif()
endif()

#-------------------------------------------------------------------------------
# Subdirectories

add_subdirectory(bin/feather-tk-res)
add_subdirectory(lib/feather-tk)
if(feather_tk_UI_LIB AND feather_tk_PYTHON)
    add_subdirectory(python)
endif()
if(feather_tk_TESTS)
    add_subdirectory(tests)
endif()
if(feather_tk_UI_LIB AND feather_tk_EXAMPLES)
    add_subdirectory(examples)
endif()

install(
    FILES LICENSE.txt
    DESTINATION share/feather-tk)

if(feather_tk_BUILD STREQUAL "SuperBuild")
    install(
        FILES cmake/Modules/FindZLIB.cmake
        DESTINATION share/feather-tk)
    install(
        FILES cmake/Modules/FindPNG.cmake
        DESTINATION share/feather-tk)
    if(feather_tk_UI_LIB)
        install(
            FILES cmake/Modules/Findnfd.cmake
            DESTINATION share/feather-tk)
    endif()
endif()
include(CMakePackageConfigHelpers)
set(INCLUDE_INSTALL_DIR include)
configure_package_config_file(
    feather-tkConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/feather-tkConfig.cmake
    INSTALL_DESTINATION share/feather-tk
    PATH_VARS INCLUDE_INSTALL_DIR)
install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/feather-tkConfig.cmake
    DESTINATION share/feather-tk)
