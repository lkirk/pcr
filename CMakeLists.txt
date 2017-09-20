cmake_minimum_required(VERSION 3.1.0)

project(pcr C)
set(PCR_VERSION "0.1.0")
set(PCR_BUG_ADDRESS "github.com/lloydkirk/pcr/issues")
set(PCR_DOC_STRING "An insilico pcr implementation")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pedantic -Wextra")

include(ExternalProject)

configure_file(
  "${CMAKE_BINARY_DIR}/src/config.h.in" "${CMAKE_BINARY_DIR}/src/config.h"
  )

set(ZLIB_DIR ${CMAKE_BINARY_DIR}/vendor/zlib)
ExternalProject_Add(zlib
  PREFIX ${CMAKE_BINARY_DIR}/vendor/zlib
  GIT_REPOSITORY "https://github.com/madler/zlib.git"
  GIT_TAG "v1.2.11"
  UPDATE_COMMAND ""
  BUILD_IN_SOURCE 1
  CONFIGURE_COMMAND ${ZLIB_DIR}/src/zlib/configure --prefix=${ZLIB_DIR} --static
  INSTALL_DIR ${ZLIB_DIR}
  )

set(HTSLIB_DIR ${CMAKE_BINARY_DIR}/vendor/htslib)
ExternalProject_Add(htslib
  PREFIX ${HTSLIB_DIR}
  GIT_REPOSITORY "https://github.com/samtools/htslib.git"
  GIT_TAG "1.3.1"
  BUILD_IN_SOURCE 1
  CONFIGURE_COMMAND ""
  BUILD_COMMAND make
  INSTALL_COMMAND make install prefix=${HTSLIB_DIR}
  )

include_directories(${ZLIB_DIR}/include)
set(zlib_static ${ZLIB_DIR}/lib/libz.a)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

include_directories(${HTSLIB_DIR}/include)
set(htslib_static ${HTSLIB_DIR}/lib/libhts.a)

file(GLOB SOURCES "src/*.c")

add_executable(pcr src/main.c)

add_dependencies(htslib zlib)
add_dependencies(pcr htslib)

target_link_libraries(pcr pthread ${htslib_static} ${zlib_static})
