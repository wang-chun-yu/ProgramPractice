/*
 * @Author: wangpeiying04 wangpeiying04@countrygarden.com.cn
 * @Date: 2022-11-16 14:40:00
 * @LastEditors: wangpeiying04 wangpeiying04@countrygarden.com.cn
 * @LastEditTime: 2023-06-20 15:59:15
 * @FilePath: /DesignMode/Single/Single_staticLocalVar.cpp
 * @Description: 懒汉式
 * 
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved. 
 */
#include <iostream>
#include <thread>
#include <ctime>
#include <unistd.h>

#define NUM 100

class Singleton01 
{
    private:
        static Singleton01* singleton01;//保存该对象的指向
    private:                            //禁止构造函数被显式调用，保证get_instance()是唯一的获取入口
        Singleton01(){}; 
        Singleton01(const Singleton01 &) = delete; //禁用复制构造函数，在编译阶段起提醒作用。
        Singleton01& operator=(const Singleton01 &) = delete;//禁用赋值构造函数，在编译阶段起提醒作用。
    public:
        static Singleton01* get_instance() 
        {
            if(singleton01 == nullptr)
            {
                std::this_thread::sleep_for(std::chrono::seconds(1));//把实例化的时间延长，方便得到实验结果。
                singleton01 = new Singleton01();
            }
            return singleton01;
        }
};

#define INIT1
#ifdef INIT1
    Singleton01* Singleton01::singleton01 = Singleton01::get_instance(); //初始化
#else
    Singleton01* Singleton01::singleton01 = nullptr; //未初始化
#endif

void threadFun1(int i)
{
    // std::this_thread::sleep_for(std::chrono::seconds(1)); //不在同一个时间获取，避免不同线程同时获取实例
    // Singleton01 example;
    auto ptr = Singleton01::get_instance();
    printf("cur thread name: %d\n", std::this_thread::get_id());
    printf("ptr%d: %lx\n", i,ptr);
}

int main(int, char**)
{
#ifndef INIT1        
/* ======提前进行初始化，避免了多线程同时进行第一次赋值时都检测到未初始化 ======*/
    auto ptr = Singleton01::get_instance();
    std::cout << "ptr=" << ptr << std::endl;
/* ======提前进行初始化，避免了多线程同时进行第一次赋值时都检测到未初始化 ======*/
#endif
    std::thread threads[NUM];
    for (auto i=0; i<NUM; i++)
    {
        threads[i] = std::thread(threadFun1,i); 
    }
    for(auto i=0; i<NUM; i++)
    {
        threads[i].join();
    }
    return 0;
}