cmake_minimum_required(VERSION 3.0.0)
project(program_practice VERSION 0.1.0)

set(DEFAULT_BUILD_TYPE "Debug")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-w")
set(CMAKE_CXX_FLAGS_RELEASE "-02 -g -ggdb ${CMAKE_CXX_FLAGS}") # 设置在release编译下的优化设置
set(CMAKE_CXX_FLAGS_DEBUG "-g ${CMAKE_CXX_FLAGS}")

add_subdirectory(Single)
add_subdirectory(NumerialDeraviation)
add_subdirectory(gammer)




