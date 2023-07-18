/*
 * @Author: wangpeiying04 wangpeiying04@countrygarden.com.cn
 * @Date: 2023-06-16 11:23:06
 * @LastEditors: wangpeiying04 wangpeiying04@countrygarden.com.cn
 * @LastEditTime: 2023-06-20 15:41:00
 * @FilePath: /DesignMode/Single/Single_staicClassMember.cpp
 * @Description: 饿汉式
 * 
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved. 
 */
#include <iostream>
#include <thread>
#include <ctime>
#include <unistd.h>
#include <mutex>

#define THREAD_NUM 100

class Singleton01
{
private: // 禁止构造函数被显式调用，保证get_instance()是唯一的获取入口
    Singleton01(){};
    Singleton01(const Singleton01 &) = delete;            // 禁用复制构造函数，在编译阶段起提醒作用。
    Singleton01 &operator=(const Singleton01 &) = delete; // 禁用赋值构造函数，在编译阶段起提醒作用。
public:
    static Singleton01* get_instance()
    {
        std::this_thread::sleep_for(std::chrono::seconds(1)); //不在同一个时间获取，避免不同线程同时获取实例
        static Singleton01 singleton01; // 保存该对象的指向
        return &singleton01;
    }
private:
    static std::mutex mtx;
};

//静态成员变量必须类外初始化
std::mutex Singleton01::mtx;

void threadFun1(int i)
{
    // std::this_thread::sleep_for(std::chrono::seconds(1)); //不在同一个时间获取，避免不同线程同时获取实例
    auto ptr = Singleton01::get_instance();
    printf("cur thread name: %d\n", std::this_thread::get_id());
    printf("ptr%d: %lx\n", i,ptr);
}

int main(int, char**)
{
// #define INIT    
#ifdef INIT
    threadFun1(0);
#endif
    std::thread threads[THREAD_NUM];
    for (auto i=0; i<THREAD_NUM; i++)
    {
        threads[i] = std::thread(threadFun1,i); 
    }
    for(auto i=0; i<THREAD_NUM; i++)
    {
        threads[i].join();
    }
    return 0;
}