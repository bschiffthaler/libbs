cmake_minimum_required(VERSION 3.0)
project (bs)

enable_testing()

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -fno-omit-frame-pointer -fsanitize=address -fsanitize=undefined")

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(LIBSOURCES src/aux.cpp src/common.cpp src/histogram.cpp src/vitter_a.cpp 
    src/vitter_d.cpp)
set(HEADERS src/aux.h src/common.h src/histogram.h src/vitter_a.h 
    src/vitter_d.h src/simple_sample.h)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_library(bs SHARED ${LIBSOURCES})
set_property(TARGET bs PROPERTY CXX_STANDARD 11)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)