/*
 * @Author: wangpeiying04 wangpeiying04@countrygarden.com.cn
 * @Date: 2023-07-23 02:07:25
 * @LastEditors: wangpeiying04 wangpeiying04@countrygarden.com.cn
 * @LastEditTime: 2023-08-07 10:37:39
 * @FilePath: /ProgramPractice/unclassified/Timer.cpp
 * @Description: 
 * 
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved. 
 */
#include <iostream>
#include <thread>
#include <chrono>
#include <functional>


// 回调函数可以接受一个任意类型的函数,和变量.
// 1.编译失败.
// 这个功能是可以借鉴thread初始化时的实现,看了一得引入了比较多东西.现在没有非要不可的程度,暂不去考虑.


class Timer {
public:
    Timer() : m_expired(true) {}

    template <typename Function, typename... Args>
    void start(int interval, Function&& func, Args&&... args) {
        m_expired = false;
        std::thread([=]() {
            while (true) {
                if (m_expired) break;
                std::this_thread::sleep_for(std::chrono::milliseconds(interval));
                func(std::forward<Args>(args)...);
            }
        }).detach();
    }

    void stop() {
        m_expired = true;
    }

private:
    bool m_expired;
};

void callbackFunction(int value) {
    std::cout << "Callback with value: " << value << std::endl;
}

struct CallableObject {
    void operator()(const std::string& message) const {
        std::cout << "Callable object: " << message << std::endl;
    }
};

int main()
{
    Timer timer;

    // Using a regular function as callback
    timer.start(1000, callbackFunction, 123);

    std::this_thread::sleep_for(std::chrono::seconds(3));

    timer.stop();
    std::cout << "Timer stopped!" << std::endl;

    // Using a callable object as callback
    CallableObject callable;
    timer.start(500, callable, "Hello, World!");

    std::this_thread::sleep_for(std::chrono::seconds(3));

    timer.stop();
    std::cout << "Timer stopped!" << std::endl;

    return 0;
}