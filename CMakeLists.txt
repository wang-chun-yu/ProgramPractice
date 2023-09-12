cmake_minimum_required(VERSION 3.0.0)
project(program_practice VERSION 0.1.0)

set(DEFAULT_BUILD_TYPE "Debug")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-w")
set(CMAKE_CXX_FLAGS_RELEASE "-02 -g -ggdb ${CMAKE_CXX_FLAGS}") # 设置在release编译下的优化设置
set(CMAKE_CXX_FLAGS_DEBUG "-g ${CMAKE_CXX_FLAGS}")

set(GOOGLE_TEST_FIRST_BUILD ON)
set(GOOGLE_TEST_ZIP_FILE ${PROJECT_SOURCE_DIR}/3rdpartyZip/googletest-main.zip)
set(GOOGLE_TEST_UNZIP_DIR ${PROJECT_SOURCE_DIR}/3rdparty/)
set(GOOGLE_TEST_UNZIP_NAME googletest-main)

if(GOOGLE_TEST_FIRST_BUILD)
    function(extract_file filename extract_dir)
        message(STATUS "Extract ${filename} to ${extract_dir} ...")
        set(temp_dir ${extract_dir})
        if(EXISTS ${temp_dir})
            file(REMOVE_RECURSE ${temp_dir})
        endif()
        file(MAKE_DIRECTORY ${temp_dir})
        execute_process(COMMAND ${CMAKE_COMMAND} -E tar -xf ${filename}
                WORKING_DIRECTORY ${temp_dir})
    endfunction()

    if(EXISTS ${GOOGLE_TEST_UNZIP_DIR}/${GOOGLE_TEST_UNZIP_NAME})
        message(STATUS "${GOOGLE_TEST_UNZIP_DIR}/${GOOGLE_TEST_UNZIP_NAME} is existed")
    else()
        extract_file(${GOOGLE_TEST_ZIP_FILE} ${GOOGLE_TEST_UNZIP_DIR})
        execute_process(COMMAND sh -c "mkdir build && cd build && cmake -DCMAKE_INSTALL_PREFIX=./bin .. && make -j4 && make install"
        WORKING_DIRECTORY ${GOOGLE_TEST_UNZIP_DIR}/${GOOGLE_TEST_UNZIP_NAME})
    endif()
endif()


# add_subdirectory(Single)
# add_subdirectory(NumerialDeraviation)
add_subdirectory(gammer)
add_subdirectory(unclassified)
add_subdirectory(thread)
add_subdirectory(image)
add_subdirectory(leetcode)
add_subdirectory(testscript)
add_subdirectory(fsm)


