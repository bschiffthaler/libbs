cmake_minimum_required(VERSION 3.0)
project (bs)

enable_testing()

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -fno-omit-frame-pointer -fsanitize=address -fsanitize=undefined")

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -fno-omit-frame-pointer -fsanitize=address -fsanitize=undefined")

set(LIBSOURCES src/aux.cpp src/vitter_a.cpp 
    src/vitter_d.cpp src/str_manip.cpp)
set(HEADERS src/aux.h src/common.h src/histogram.h src/vitter_a.h 
    src/vitter_d.h src/simple_sample.h src/describe.h src/str_manip.h)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

add_library(bs SHARED ${LIBSOURCES})
add_library(bs_S STATIC ${LIBSOURCES})

set_target_properties(bs_S PROPERTIES OUTPUT_NAME bs)

set_property(TARGET bs PROPERTY CXX_STANDARD 11)
set_property(TARGET bs_S PROPERTY CXX_STANDARD 11)

if (BUILD_TEST_EXECS)
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)
endif()

if (BUILD_APPS)
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/apps)
endif()