find_package(GTest REQUIRED PATHS "${GOOGLE_TEST_UNZIP_DIR}/${GOOGLE_TEST_UNZIP_NAME}/build/bin/lib/cmake/GTest/" )

enable_testing()

function(add name)
  add_executable(${name} ${name}.cc)
  target_link_libraries(${name} GTest::gtest_main)
endfunction()

function(add_example name)
  add_executable(${name} ${name}.cc ${name}_unittest.cc )
  target_link_libraries(${name} GTest::gtest_main)
endfunction()

add_example(t1)
add_example(t2)

# add_executable(t2 t2.cc)
