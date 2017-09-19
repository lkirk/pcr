cmake_minimum_required(VERSION 3.1.0)

project(pcr C)
set (PCR_VERSION "0.1.0")

include(ExternalProject)

configure_file (
  "${CMAKE_BINARY_DIR}/src/config.h.in"
  "${CMAKE_BINARY_DIR}/config.h"
  )

ExternalProject_Add(zlib
  PREFIX ${CMAKE_BINARY_DIR}/vendor/zlib
  GIT_REPOSITORY "https://github.com/madler/zlib.git"
  GIT_TAG "v1.2.11"
  BUILD_IN_SOURCE 1
  CONFIGURE_COMMAND ${CMAKE_BINARY_DIR}/vendor/zlib/src/zlib/configure --prefix=${CMAKE_BINARY_DIR}/vendor/zlib --static
  INSTALL_DIR ${CMAKE_BINARY_DIR}/vendor/zlib
  )

ExternalProject_Add(htslib
  PREFIX ${CMAKE_BINARY_DIR}/vendor/htslib
  GIT_REPOSITORY "https://github.com/samtools/htslib.git"
  GIT_TAG "1.3.1"
  BUILD_IN_SOURCE 1
  CONFIGURE_COMMAND ""
  BUILD_COMMAND make
  INSTALL_COMMAND make install prefix=${CMAKE_BINARY_DIR}/vendor/htslib
  )

include_directories(${CMAKE_BINARY_DIR}/vendor/zlib/include)
set(zlib_static ${CMAKE_BINARY_DIR}/vendor/zlib/lib/libz.a)
set(htslib_static ${CMAKE_BINARY_DIR}/vendor/htslib/lib/libhts.a)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_BINARY_DIR}/vendor/htslib/include)

file(GLOB SOURCES "src/*.c")

add_executable(pcr src/main.c)

add_dependencies(htslib zlib)
add_dependencies(pcr htslib)

target_link_libraries(pcr pthread ${htslib_static} ${zlib_static})
