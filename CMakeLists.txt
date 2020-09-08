cmake_minimum_required(VERSION 3.17)
project(dynamon)

set(CMAKE_C_STANDARD 90)

option(BUILD_SHARED_LIBS "Determines whether or not it's shared or static" OFF)
option(INSTALL_LOCAL "Whether or not the installation will be local or global" ON)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(HEADERS include/dynamon.h)
set(SOURCES ${HEADERS} src/dynamon.c)
if(BUILD_SHARED_LIBS)
    set(dnm_type SHARED)
else()
    set(dnm_type STATIC)
endif()
add_library(dynamon ${dnm_type}
        ${SOURCES}
        )
include_directories(include)

if (WIN32)
    message(STATUS "Adding Windows-specific libraries")
    find_package(dlfcn-win32 REQUIRED)
    target_link_libraries(dynamon PRIVATE dlfcn-win32::dl)
endif()

include(dynamon_install)