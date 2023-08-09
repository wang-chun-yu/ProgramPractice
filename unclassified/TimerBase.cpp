/*
 * @Author: wangpeiying04 wangpeiying04@countrygarden.com.cn
 * @Date: 2023-07-23 21:30:41
 * @LastEditors: wangpeiying04 wangpeiying04@countrygarden.com.cn
 * @LastEditTime: 2023-08-07 10:54:24
 * @FilePath: /ProgramPractice/unclassified/TimerBase.cpp
 * @Description: 
 * 
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved. 
 */
#include <iostream>
#include <thread>
#include <chrono>
#include <unistd.h>
#include <functional>

// breif：简单粗略计算时间，回调函数耗时太大会影响计时精度
// breif：定时器的线程被分离了，定时器类析构了定时任务还在执行。
// breif:

class Timer {
public:
    Timer() : m_expired(true) {}
    ~Timer() {
        stop(); 
        // std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        std::cout << "disconstruct" << std::endl;};

    void start(int interval, std::function<void()> callback) {
        m_expired = false;
        std::thread([=]() {
            while (true) {
                if (m_expired) break;
                printf("this:%x",this);
                // if (this == nullptr) break;
                // 开始计时
                auto start = std::chrono::high_resolution_clock::now();

                // 这里可以放需要计时的代码段
                std::this_thread::sleep_for(std::chrono::milliseconds(interval));

                // 结束计时
                auto end = std::chrono::high_resolution_clock::now();

                // 计算耗时
                std::chrono::duration<double> elapsedTime = end - start;
                
                callback();
                // 输出耗时（以秒为单位）
                std::cout << "耗时: " << elapsedTime.count() << "秒" << std::endl;        
            }
        });//.detach();
        sleep(5);
    }

    void stop() {
        m_expired = true;
    }

private:
    bool m_expired;
};

// int main()
// {
//     Timer timer;
//     timer.start(1000, []() {
//         std::cout << "Timer expired!" << std::endl;
//     });

//     std::this_thread::sleep_for(std::chrono::seconds(20));

//     timer.stop();
//     std::cout << "Timer stopped!" << std::endl;

//     return 0;
// }

int main()
{
    auto p1 = new Timer;
    p1->start(1000, []() {
        std::cout << "Timer1 expired!" << std::endl;
    });

    // auto p2 = new Timer;
    // p2->start(2000, []() {
    //     std::cout << "Timer2 expired!" << std::endl;
    // });
   
    // std::this_thread::sleep_for(std::chrono::seconds(5));
    sleep(2);
    // delete p1;

    // std::this_thread::sleep_for(std::chrono::seconds(5));

    // p->stop();
    
    std::cout << "Timer stopped!" << std::endl;

    return 0;
}