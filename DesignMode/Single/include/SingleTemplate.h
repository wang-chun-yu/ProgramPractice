/*
 * @Author: wangpeiying04 wangpeiying04@countrygarden.com.cn
 * @Date: 2023-06-16 14:29:47
 * @LastEditors: wangpeiying04 wangpeiying04@countrygarden.com.cn
 * @LastEditTime: 2023-06-21 09:01:43
 * @FilePath: /DesignMode/Single/include/SingleTemplate.h
 * @Description: 
 * 
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved. 
 */
#ifndef __SINGLE_TEMPLATE_H__
#define __SINGLE_TEMPLATE_H__

template<typename T>
class Instance
{
private:
    Instance(){};
    Instance(const Instance & )=delete; 
    Instance& operator=(const Instance)=delete;   
public:
    static T* getInstance() //调用唯一入口
    {
        static T instance;
        return &instance;
    }
};
#endif
