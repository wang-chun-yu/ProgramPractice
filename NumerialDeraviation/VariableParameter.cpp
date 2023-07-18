/*
 * @Author: wangpeiying04 wangpeiying04@countrygarden.com.cn
 * @Date: 2023-06-30 15:24:14
 * @LastEditors: wangpeiying04 wangpeiying04@countrygarden.com.cn
 * @LastEditTime: 2023-07-06 15:09:34
 * @FilePath: /DesignMode/NumerialDeraviation/VariableParameter.cpp
 * @Description: 
 * 
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved. 
 */
#include <iostream>
#include <functional>

// #define BASE
// #define RECURSION
// #define TEST1

#ifdef BASE

template<class... T>
void f(T... args){
    std::cout << sizeof...(args) << std::endl; //sizeof...(args) 取得可变参数的个数
}

int main(int argc, char** argv)
{
    f();
    f(1, 2);
    f(1, 2.3, "hello");
}

#endif


#ifdef RECURSION

// 递归终止函数
void print(){
    std::cout << "empty" <<std::endl;
}
// 展开函数
template<typename T, typename... A>
void print(T head, A... rest){
    std::cout << "parameter = " << head << std::endl;
    print(rest...);
}

int main(int argv,char **argc){
    print(1,2,3,4);
    //当调用print(1,2,3,4)时，先后调用print(2,3,4), print(3,4),print(4),最终调用print()终止。
    return 0;
}
#endif

#ifdef TEST1

#include <cstdarg>
//可变参数的函数
void vair_fun(int count, ...)
{
    va_list args;
    va_start(args, count);
    for (int i = 0; i < count; ++i)
    {
        int arg = va_arg(args, int);
        std::cout << arg << " ";
    }
    va_end(args);
}

void vair_fund(int count, ...)
{
    va_list args;
    va_start(args, count);
    for (int i = 0; i < count; ++i)
    {
        double arg = va_arg(args, double);
        std::cout << arg << " ";
    }
    va_end(args);
}

int main()
{
    //可变参数有 4 个，分别为 10、20、30、40
    vair_fun(4, 10, 20, 30,40);
    vair_fund(4, 10.1, 20.2, 30.3,40.4);
    return 0;
}

#endif

#define TEST2
#ifdef TEST2

#include <cstdarg>
//可变参数的函数
void vair_fun(int count, ...)
{
    va_list args;
    va_start(args, count);
    for (int i = 0; i < count; ++i)
    {
        int a = va_arg(args, int);
        std::cout << a << " ";
    }
    va_end(args);
}

int main()
{
    //可变参数有 4 个，分别为 10、20、30、40
    vair_fun(4, "10", "20", "30", "40");
    return 0;
}

#endif

#ifdef TEST3
void fun(){};
template <typename T,typename... B>
void fun(T arg1, B... arg)
{
    std::cout << arg1 << std::endl;
    fun(arg...);
};



int main()
{
    fun("Y1", "Y2", "Y3");
}

#endif