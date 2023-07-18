/*
 * @Author: wangpeiying04 wangpeiying04@countrygarden.com.cn
 * @Date: 2023-07-12 11:17:54
 * @LastEditors: wangpeiying04 wangpeiying04@countrygarden.com.cn
 * @LastEditTime: 2023-07-12 11:35:30
 * @FilePath: /DesignMode/gammer/bitOperator.cpp
 * @Description: 
 * 
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved. 
 */
#include <iostream>

#define GetBit(v, n) (bool)((v) & ((uint32_t)1 << (n))) //获取v 的第 n 位
#define SetBit(v, n) (bool)((v) |= ((uint32_t)1 << (n)))//将v的第n位置1
#define ClearBit(v, n) (bool)((v) &= (~(uint32_t)1 << (n)))//将v的第n位清0

void func(std::string s)
{
    s = "buhao";
}

int main()
{
    uint16_t val = 0x0011;
    for(int i=0;i<16;i++)
    {
        std::cout << GetBit(val, i) << std::endl;
    }

    std::string a = "nihao";
    func(a);
    std::cout << a;
    
    return 0;
}