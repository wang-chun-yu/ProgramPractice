cmake_minimum_required(VERSION 3.0.0)
project(Designmode VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 11)

include(CTest)
enable_testing()

include_directories(${PROJECT_SOURCE_DIR}/include)
message("PROJECT_SOURCE_DIR:${PROJECT_SOURCE_DIR}")

add_executable(Single_staticClassMember Single_staticClassMember.cpp)
add_executable(Single_staticLocalVar Single_staticLocalVar.cpp)
add_executable(main main.cpp)
target_link_libraries(Single_staticClassMember pthread)
target_link_libraries(Single_staticLocalVar pthread)
target_link_libraries(main pthread)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
