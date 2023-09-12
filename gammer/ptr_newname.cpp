/*
 * @Author: wangpeiying04 wangpeiying04@countrygarden.com.cn
 * @Date: 2023-09-06 15:31:28
 * @LastEditors: wangpeiying04 wangpeiying04@countrygarden.com.cn
 * @LastEditTime: 2023-09-06 17:31:45
 * @FilePath: /ProgramPractice/gammer/ptr_newname.cpp
 * @Description: 使用typedef定义别名
 * 
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved. 
 */
#include <string>
#include <unistd.h>
#include <iostream>

// 为结构体定义别名
struct stu 
{
    stu(std::string _name, int _age): name(_name),age(_age){}; 
    stu(){};
    std::string name;
    int age;
};
typedef struct stu STU;

// 为数组定义别名
typedef int ARRARY[20]; 

// 为指针定义别名
typedef int (*PTR_TO_ARR)[4]; // PTR_TO_ARR为一个一维数组的指针类型

// 为函数定义别名
typedef int (*PRT_TO_FUN)(int, int);
int sum(int a ,int b)
{
    return a+b;
}


int main()
{
    struct stu stu1("小明",18);
    STU stu2("小红",17);

    ARRARY arry1;
    arry1[0] = 0;
    arry1[1] = 1;
    arry1[2] = 2;

    static PTR_TO_ARR p1;
    // for(int i=0; i<3; i++)
    // {
    //     for(int j=0; j<4; j++)
    //     {
    //         *p1[i][j] = (i+1)*(j+1);
    //     }
    // }
    PRT_TO_FUN calculate = sum;
    std::cout << calculate(5, 6) << std::endl;
    
    sleep(1);
    
    return 0;
}

