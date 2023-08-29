# set(GOOGLE_TEST_FIRST_BUILD OFF)
# set(GOOGLE_TEST_ZIP_FILE ${PROJECT_SOURCE_DIR}/3rdpartyZip/googletest-main.zip)
# set(GOOGLE_TEST_UNZIP_DIR ${PROJECT_SOURCE_DIR}/3rdparty/)
# set(GOOGLE_TEST_UNZIP_NAME googletest-main)

# if(GOOGLE_TEST_FIRST_BUILD)
#     function(extract_file filename extract_dir)
#         message(STATUS "Extract ${filename} to ${extract_dir} ...")
#         set(temp_dir ${extract_dir})
#         if(EXISTS ${temp_dir})
#             file(REMOVE_RECURSE ${temp_dir})
#         endif()
#         file(MAKE_DIRECTORY ${temp_dir})
#         execute_process(COMMAND ${CMAKE_COMMAND} -E tar -xf ${filename}
#                 WORKING_DIRECTORY ${temp_dir})
#     endfunction()

#     extract_file(${GOOGLE_TEST_ZIP_FILE} ${GOOGLE_TEST_UNZIP_DIR})
#     execute_process(COMMAND sh -c "mkdir build && cd build && cmake -DCMAKE_INSTALL_PREFIX=./bin .. && make -j4 && make install"
#     WORKING_DIRECTORY ${GOOGLE_TEST_UNZIP_DIR}/${GOOGLE_TEST_UNZIP_NAME})
# endif()


find_package(GTest REQUIRED PATHS "${GOOGLE_TEST_UNZIP_DIR}/${GOOGLE_TEST_UNZIP_NAME}/build/bin/lib/cmake/GTest/" )
# set(GTest_DIR "${PROJECT_SOURCE_DIR}/3rdparty/googletest-main/build/bin/lib/cmake/GTest/")
# find_package(GTest REQUIRED)

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