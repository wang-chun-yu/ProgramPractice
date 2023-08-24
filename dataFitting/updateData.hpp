/*
 * @Author: wangpeiying04 wangpeiying04@countrygarden.com.cn
 * @Date: 2023-08-16 10:09:50
 * @LastEditors: wangpeiying04 wangpeiying04@countrygarden.com.cn
 * @LastEditTime: 2023-08-16 11:16:43
 * @FilePath: /ProgramPractice/dataFitting/updateData.hpp
 * @Description: 
 * 
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved. 
 */

// 以一定的频率监控数据的变化.
// 1.需要的数据:转速,测量时间,重量变化,重量变化/测量时间
// 2.计算周期:转速不变的持续时间.转速变化,重新计算.
// 3.记录数据,数据示例:
// {
    
//     "data":
//     {
//         "rpm_start": 500,
//         [
//             // 按照时间先后排序.
//             {
//                 "rpm" : 531,
//                 "period" : 120,
//                 "weight" : 0.8, //重量变化越大的占权重越大,因为称重的误差越小.
//             },
//             {
//                 "rpm" : 671,
//                 "period" : 170,
//                 "weight" : 1.5, 
//             }
//         ]
//     }
// }
// 4.数据更新,每个区间维持在一定数据量.剔除发生时间在前面的
#include <vector>
#include <map>

class UpdateData
{
public:
    UpdateData(){};
    void getCurRpm(int _cur_rpm);  // 需要周期更新
    void getCurWeight(float weight); // 需要周期更新
private:
    int cur_rpm{0};
    int during_time{0}; // sec
    float weight_init{0}; // kg
    float weight_increment{0}; // kg
};

class DataUnit  
{
    int rpm{0};
    int during_time{0};
    float weight_increament{0};
};

// 数据拟合模块

class Statistics
{
private:
    const std::string file_path = ""; 
public:
    Statistics(){};
    void getMeasureData(std::string _brand)// 根据品牌从文件读取数据
    {
        if(_brand!=brand)
        {
            // 从文件能找到brand名字,将数据保存
            brand = _brand;
        }
    }
private:
    UpdateData update_data_module;
    std::map<int,std::vector<DataUnit>> measure_data; // 周期:数据组
    std::string brand = ""; // 当前品牌

};