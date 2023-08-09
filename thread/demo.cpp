/*
 * @Author: wangpeiying04 wangpeiying04@countrygarden.com.cn
 * @Date: 2023-07-25 08:54:02
 * @LastEditors: wangpeiying04 wangpeiying04@countrygarden.com.cn
 * @LastEditTime: 2023-08-07 11:21:18
 * @FilePath: /ProgramPractice/thread/demo.cpp
 * @Description: 
 * 
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved. 
 */
#include <thread>
#include <unistd.h>
#include <iostream>
#include <chrono>

// breif: 推荐写法,先申请线程对象,方便控制线程对象生命周期.

// 如果不分离线程,不使用join()等待线程,会报错:terminate called without an active exception.
// #define TEST1
#ifdef TEST1
int main(int argc, char** argv)
{
    std::thread th1 = std::thread([]
        {
            int i= 10;
            while(i--)
            {
                std::this_thread::sleep_for(std::chrono::microseconds(1));
                std::cout << i <<" : running..." << std::endl;
            }
            std :: cout << "end" << std::endl;
            // return;
        });

    // th1.join();

    std :: cout << "main_end" << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(5));
    return 0;
}
#endif

#define TEST2
#ifdef TEST2
void func()
{
    std::thread thread([]
        {
            sleep(1);
            std::cout << "running..." << std::endl;
            return 0;
        });
    sleep(5); //5秒后流程不结束会报错
}

// 这种写法不分离马上会报错
void func1(std::function<void()> callback) {
    std::thread([=]() {
        callback();
    });//.detach(); //不分离会报错
    sleep(5);
}

// 推荐写法,先申请线程对象,方便控制线程对象周期.
std::thread th1;
void func2(std::function<void()> callback) {
    th1 = std::thread([=]() {
        callback();
    });
    sleep(5);
}

int main(int argc, char** argv)
{
    // func();//函数内部局部线程，如果没有detach()分离，生命周期不能超过函数。

    func1([](){std::cout << "running..." << std::endl;}); //使用std::function<void()>封装函数，不分离马上会报错
    // func2( [](){std::cout << "running..." << std::endl;} );

    sleep(20);
    
    return 0;
}
#endif