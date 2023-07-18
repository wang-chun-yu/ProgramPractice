/*
 * @Author: wangpeiying04 wangpeiying04@countrygarden.com.cn
 * @Date: 2023-06-16 14:29:47
 * @LastEditors: wangpeiying04 wangpeiying04@countrygarden.com.cn
 * @LastEditTime: 2023-06-21 09:52:01
 * @FilePath: /DesignMode/Single/include/SingleTemplate1.h
 * @Description: 
 * 
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved. 
 */
#ifndef __SINGLE_TEMPLATE1_H__
#define __SINGLE_TEMPLATE1_H__
#include <memory>



template<typename T>
class Instance
{
private:
    Instance(){};
    Instance(const Instance & )=delete; 
    Instance& operator=(const Instance)=delete;   
public:
    static std::shared_ptr<T> getInstance() //调用唯一入口
    {
        static std::shared_ptr<T> instance = std::make_shared<T>();
        // std::lock_guard<std::mutex> lck(mtx);
        return instance;
    }
private:
    // static std::mutex mtx;
};

// template<typename T>
// std::mutex Instance<T>::mtx;


#endif
