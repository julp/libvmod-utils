cmake_minimum_required(VERSION 2.8.3)

project(libvmod-utils C)

# cmake . -DVARNISHSRC:PATH=$HOME/Downloads/varnish-4.0.0/

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})
include(VarnishMOD)

declare_vmod(
    INSTALL
    NAME utils
    VCC ${PROJECT_SOURCE_DIR}/src/vmod_utils.vcc
    SOURCES ${PROJECT_SOURCE_DIR}/src/vmod_utils.c
)
