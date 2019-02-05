cmake_minimum_required(VERSION 3.0)
project (bs)

enable_testing()

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(LIBSOURCES src/aux.cpp src/common.cpp src/histogram.cpp src/vitter_a.cpp 
    src/vitter_d.cpp src/describe.cpp)
set(HEADERS src/aux.h src/common.h src/histogram.h src/vitter_a.h 
    src/vitter_d.h src/simple_sample.h src/describe.h)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

add_library(bs SHARED ${LIBSOURCES})
set_property(TARGET bs PROPERTY CXX_STANDARD 11)

if (BUILD_TEST_EXECS)
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)
endif()

if (BUILD_APPS)
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/apps)
endif()