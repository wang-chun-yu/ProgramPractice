/*
 * @Author: wangpeiying04 wangpeiying04@countrygarden.com.cn
 * @Date: 2023-06-20 10:53:23
 * @LastEditors: wangpeiying04 wangpeiying04@countrygarden.com.cn
 * @LastEditTime: 2023-06-21 09:40:18
 * @FilePath: /DesignMode/Single/main.cpp
 * @Description: 
 * 
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved. 
 */
#include "SingleTemplate1.h"
#include <cstdint>
#include <string>
#include <thread>

#define NUM 100

class  student
{
private:
    uint16_t m_age;
    std::string m_name;
public:
     student(){};
     student(uint16_t age, std::string name): m_age(age),m_name(name){};
     void set_age(uint16_t age){m_age=age;};
     void set_m_name(std::string name){m_name=name;};
     void show_info()
     {
        printf("age:%d\n",m_age);
        printf("name:%s\n",m_name.c_str());
     }
    ~ student(){};
};

int main(int argc, char **argv)
{
    // Instance<student> A; //禁止该操作，编译器会提醒.
    std::thread thd[NUM];
    for(int i=0;i<NUM;i++)
    {
        thd[i] = std::thread([](int i){
            auto ptr = Instance<student>::getInstance();
            printf("cur thread name: %d\n", std::this_thread::get_id());
            printf("ptr%d: %lx\n", i,ptr);
            printf("use ptr_num:%d\n",ptr.use_count());
            },i);
    }

    for(int i=0;i<NUM;i++)
    {
        thd[i].join();
    }

    auto ptr = Instance<student>::getInstance();
    printf("use ptr_num:%d",ptr.use_count());
    // ptr->set_age(11);
    // ptr->set_m_name("xiaoli");
    // ptr->show_info();

    return 0;
}

