cmake_minimum_required(VERSION 3.0)
project (bs)

set (CMAKE_CXX_STANDARD 11)

find_package(Boost 1.55.0 REQUIRED COMPONENTS program_options)

include_directories(${Boost_INCLUDE_DIRS})

add_executable(summary src/summary.cpp)
target_link_libraries(summary bs ${Boost_LIBRARIES})