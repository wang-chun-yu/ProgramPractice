
set(Eigen3_DIR ${PROJECT_SOURCE_DIR}/3rdparty/eigen/build/bin/share/eigen3/cmake)
find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

message("EIGEN3_INCLUDE_DIR:"${EIGEN3_INCLUDE_DIR})

add_executable(test1 test1.cpp)
add_executable(VariableParameter VariableParameter.cpp)
