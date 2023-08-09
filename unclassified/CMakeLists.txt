# add_executable(timer Timer.cpp)
add_executable(timerbase TimerBase.cpp)
add_executable(perfertSend perfertSend.cpp)
# target_link_libraries(timer pthread)
target_link_libraries(timerbase pthread)

add_executable(threadObj threadObj.cpp)
target_link_libraries(threadObj pthread)