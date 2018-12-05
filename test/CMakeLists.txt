add_executable(test_vitter_a src/test_vitter_a.cpp)
target_link_libraries(test_vitter_a bs)
add_executable(test_vitter_d src/test_vitter_d.cpp)
target_link_libraries(test_vitter_d bs)

add_test("VitterA_10_from_100" test_vitter_a 100 10)
add_test("VitterA_10_from_1000" test_vitter_a 1000 10)
add_test("VitterA_10_from_10000" test_vitter_a 10000 10)
add_test("VitterA_fail_1000_from_10" test_vitter_a 10 1000)
add_test("VitterD_10_from_100" test_vitter_d 100 10)
add_test("VitterD_10_from_1000" test_vitter_d 1000 10)
add_test("VitterD_10_from_10000" test_vitter_d 10000 10)
add_test("VitterD_fail_1000_from_10" test_vitter_d 10 1000)


set_tests_properties(
VitterA_fail_1000_from_10 
VitterD_fail_1000_from_10
PROPERTIES WILL_FAIL TRUE
)