cmake_minimum_required(VERSION 3.0)
project (bs)

add_executable(print_histogram src/print_histogram.cpp)
target_link_libraries(print_histogram bs)

add_executable(print_stats src/print_stats.cpp)
target_link_libraries(print_stats bs)