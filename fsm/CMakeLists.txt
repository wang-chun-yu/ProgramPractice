set(FSM_TEST_FIRST_BUILD ON)
set(ZIP_FILE ${PROJECT_SOURCE_DIR}/3rdpartyZip/scxmlcc-master.zip)
set(UNZIP_DIR ${PROJECT_SOURCE_DIR}/3rdparty)
set(UNZIP_NAME scxmlcc-master)

if(FSM_TEST_FIRST_BUILD)
    function(extract_file filename extract_dir)
        message(STATUS "Extract ${filename} to ${extract_dir} ...")
        set(temp_dir ${extract_dir}/${UNZIP_NAME})
        if(EXISTS ${temp_dir})
            file(REMOVE_RECURSE ${temp_dir})
        endif()
        # file(MAKE_DIRECTORY ${temp_dir})
        execute_process(COMMAND ${CMAKE_COMMAND} -E tar -xf ${filename}
                WORKING_DIRECTORY ${extract_dir})
    endfunction()

    if(EXISTS ${UNZIP_DIR}/${UNZIP_NAME})
        message(STATUS "${UNZIP_DIR}${UNZIP_NAME} is existed")
        if(EXISTS ${UNZIP_DIR}/${UNZIP_NAME}/build)
            message(STATUS "${UNZIP_DIR}${UNZIP_NAME}/build is existed")
        else()
            execute_process(COMMAND sh -c "mkdir build && cd build && cmake -DCMAKE_INSTALL_PREFIX=./bin .. && make -j4 && make install"
            WORKING_DIRECTORY ${UNZIP_DIR}/${UNZIP_NAME})
        endif()
    else()
        extract_file(${ZIP_FILE} ${UNZIP_DIR})
        execute_process(COMMAND sh -c "mkdir build && cd build && cmake -DCMAKE_INSTALL_PREFIX=./bin .. && make -j4 && make install"
        WORKING_DIRECTORY ${UNZIP_DIR}/${UNZIP_NAME})
    endif()
endif()


include( /home/chunyu/wpy_learning/ProgramPractice/fsm/share/cmake/Modules/scxmlcc_generator.cmake)

set( CMAKE_INCLUDE_CURRENT_DIR ON )

set(S ${CMAKE_CURRENT_SOURCE_DIR} )
scxmlcc_generator( ${S}/hello_world.scxml hello_gen_src )
# scxmlcc_generator( ${S}/timer_switch.scxml timer_gen_src )
# scxmlcc_generator( ${S}/microwave-01-cplusplus.scxml microwave_gen_src )
# scxmlcc_generator( ${S}/microwave-02-cplusplus.scxml microwave_gen_src )
# scxmlcc_generator( ${S}/vending_machine/vending_machine.scxml vending_gen_src )

set (CMAKE_CXX_STANDARD 17)

add_executable( hello_world
    hello_world.cpp
    ${hello_gen_src} 
    )

# add_subdirectory(examples)