# Always debug
set(CMAKE_BUILD_TYPE="Debug")

add_executable(test_vitter_a src/test_vitter_a.cpp)
target_link_libraries(test_vitter_a bs)
add_executable(test_vitter_d src/test_vitter_d.cpp)
target_link_libraries(test_vitter_d bs)
add_executable(test_vitter_d_speed src/test_vitter_d_speed.cpp)
target_link_libraries(test_vitter_d_speed bs)
add_executable(test_simple_sample src/test_simple_sample.cpp)
target_link_libraries(test_simple_sample bs)
add_executable(test_histogram src/test_histogram.cpp)
target_link_libraries(test_histogram bs)
add_executable(test_str src/test_str.cpp)
target_link_libraries(test_str bs)
add_executable(test_desc src/test_desc.cpp)
target_link_libraries(test_desc bs)

set_property(TARGET test_vitter_a PROPERTY CXX_STANDARD 11)
set_property(TARGET test_vitter_d PROPERTY CXX_STANDARD 11)
set_property(TARGET test_vitter_d_speed PROPERTY CXX_STANDARD 11)
set_property(TARGET test_simple_sample PROPERTY CXX_STANDARD 11)
set_property(TARGET test_histogram PROPERTY CXX_STANDARD 11)
set_property(TARGET test_str PROPERTY CXX_STANDARD 11)
set_property(TARGET test_desc PROPERTY CXX_STANDARD 11)

add_test("VitterA_10_from_100" test_vitter_a 100 10)
add_test("VitterA_10_from_1000" test_vitter_a 1000 10)
add_test("VitterA_10_from_10000" test_vitter_a 10000 10)
add_test("VitterA_100_from_100" test_vitter_a 100 100)
add_test("VitterA_fail_1000_from_10" test_vitter_a 10 1000)
add_test("VitterD_10_from_100" test_vitter_d 100 10)
add_test("VitterD_10_from_1000" test_vitter_d 1000 10)
add_test("VitterD_10_from_10000" test_vitter_d 10000 10)
add_test("VitterD_100_from_100" test_vitter_d 100 100)
add_test("VitterD_fail_1000_from_10" test_vitter_d 10 1000)
add_test("VitterD_speed_1000000_from_1000000000" test_vitter_d 1000000000 1000000)
add_test("SimpleSample_1000_from_10" test_simple_sample 10 10000)
add_test("Histogram" test_histogram)
add_test("String_manip" test_str)
add_test("Sescribe" test_desc)

set_tests_properties(
VitterA_fail_1000_from_10 
VitterD_fail_1000_from_10
PROPERTIES WILL_FAIL TRUE
)