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
add_example(t3)

add_executable(t4 t4.cc)
add_executable(t5 t5.cc)
add_executable(t6 t6.cc)
add_executable(t7 t7.cc)
add_executable(t8 t8.cc)
add_executable(t9 t9.cc)
add_executable(t10 t10.cc)
add_executable(t11 t11.cc)
add_executable(t12 t12.cc)