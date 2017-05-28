cmake_minimum_required( VERSION 3.5 )

PROJECT( target )

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${target_SOURCE_DIR}/cmake")
set(BIN_DIR ${target_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
include_directories(include)

ADD_SUBDIRECTORY( src )

if ( CMAKE_COMPILER_IS_GNUCC )
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall")
endif ( CMAKE_COMPILER_IS_GNUCC )
