/*
 * @Author: wangpeiying04 wangpeiying04@countrygarden.com.cn
 * @Date: 2022-11-16 14:40:00
 * @LastEditors: wangpeiying04 wangpeiying04@countrygarden.com.cn
 * @LastEditTime: 2023-06-20 15:59:15
 * @FilePath: /DesignMode/Single/Single_staticLocalVar.cpp
 * @Description: 懒汉式(需要使用才申请，同时用可变参数和完美转发实现初始化）
 * 
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved. 
 */
# pragma once

#include <iostream>
#include <thread>
#include <ctime>
#include <unistd.h>
#include <mutex>

template <typename T>
class Instance 
{
    private:
        static T* InstancePtr;//保存该对象的指向
        static std::mutex mtx;
    private:                            //禁止构造函数被显式调用，保证get_instance()是唯一的获取入口
        Instance(){}; 
        Instance(const Instance &) = delete; //禁用复制构造函数，在编译阶段起提醒作用。
        Instance& operator=(const Instance &) = delete;//禁用赋值构造函数，在编译阶段起提醒作用。
    public:
        template <typename T1,typename... T2>
        static T* get_instance(T1&& arg1, T2&&...arg2)
        {
            std::lock_guard<std::mutex> tp_lock(mtx);
            if(InstancePtr == nullptr)
            {
                std::this_thread::sleep_for(std::chrono::seconds(1));//把实例化的时间延长，方便得到实验结果。
                InstancePtr = new T(std::forward<T1>(arg1), std::forward<T2>(arg2)...);
            }
            return InstancePtr;
        }

        static T* get_instance()
        {
            std::lock_guard<std::mutex> tp_lock(mtx);
            if(InstancePtr == nullptr)
            {
                std::this_thread::sleep_for(std::chrono::seconds(1));//把实例化的时间延长，方便得到实验结果。
                InstancePtr = new T();
            }
            return InstancePtr;
        }

};

template<typename T>
T* Instance<T>::InstancePtr = nullptr; 

template<typename T>
std::mutex Instance<T>::mtx;

// Instance* Instance::Instance = Instance::get_instance(); //初始化


