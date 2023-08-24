set(GTest_DIR ${PROJECT_SOURCE_DIR}/3rdparty/googletest-main/build/bin/lib/cmake/GTest/)
find_package(GTest REQUIRED)

enable_testing()

function(add name)
  add_executable(${name} ${name}.cc)
  target_link_libraries(${name} GTest::gtest_main)
endfunction()

function(add_example name)
  add_executable(${name} ${name}.cc ${name}_unittest.cc )
  target_link_libraries(${name} GTest::gtest_main)
endfunction()

add(hello_test)
add_example(sample1)

include(GoogleTest)
gtest_discover_tests(hello_test)