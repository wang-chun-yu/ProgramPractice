/*
 * @Author: wangpeiying04 wangpeiying04@countrygarden.com.cn
 * @Date: 2023-08-04 10:44:22
 * @LastEditors: wangpeiying04 wangpeiying04@countrygarden.com.cn
 * @LastEditTime: 2023-08-07 10:39:54
 * @FilePath: /ProgramPractice/unclassified/perfertSend.cpp
 * @Description:
 * 
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved. 
 */
#include <iostream>
#include <functional>
#include <utility>


//std::invoke 需要C++17以上支持

void myFunction(int a, double b, const std::string& c) {
    std::cout << "a: " << a << ", b: " << b << ", c: " << c << std::endl;
}

template<typename... Args>
void callFunction(Args&&... args) {
    std::function<void(Args...)> func = myFunction;

    // 通过完美转发调用函数
    func(std::forward<Args>(args)...);
    // std::invoke(func, std::forward<Args>(args)...);
}

int main() {
    int a = 10;
    double b = 3.14;
    std::string c = "Hello";

    // 调用函数
    callFunction(a, b, c);

    return 0;
}