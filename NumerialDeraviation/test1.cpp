/*
 * @Author: wangpeiying04 wangpeiying04@countrygarden.com.cn
 * @Date: 2023-06-21 11:15:11
 * @LastEditors: wangpeiying04 wangpeiying04@countrygarden.com.cn
 * @LastEditTime: 2023-07-06 16:33:40
 * @FilePath: /DesignMode/NumerialDeraviation/test1.cpp
 * @Description: 
 * 
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved. 
 */
#include <iostream>
#include <Eigen/Core>
#include <unordered_map>
#include <map>
#include <functional>
#include <cstdarg>
#include <string>
#include <utility>
// #include <boost/type_index.hpp>
#include <cassert>
#include <float.h>
#include <vector>

static float min = 0.0001; //这个数值不是越小越好
static float min2 = min*2;
static double min_inf = DBL_MIN; //这个数值不是越小越好


// 数值求导，任意添加多项式求雅克比矩阵
class DeraviationSlove
{
public:
    using x_arg = std::unordered_map<std::string, double>;
    using item_function = std::function<double(x_arg arg)>;
    using forumal_function = std::vector<item_function>;
public:
    DeraviationSlove(){};
    template <typename s, typename... ss>
    bool Y_add(s arg1, ss... arg2);
    bool Y_add(){};
    void Y_show()
    {
        for(auto iter:Y_name)
        {
            std::cout << iter << std::endl;
        }
    };
    void X_show()
    {
        for(auto iter:X)
        {
            std::cout << iter.first << "=" << iter.second << std::endl;
        }        
    }
    bool X_add(std::string name, double value);
    double XVaule(std::string _x_name, x_arg arg);                   // 指定变量
    void item_add(std::string _y_name, item_function _func);         // 添加多项式
    double DeraciationCal(std::string _y_name, std::string _x_name); // 计算指定偏导数
    Eigen::MatrixXd DeraciationCalMatrix();                          // 计算雅克比矩阵

private:
    std::unordered_map<std::string, forumal_function> Y;
    x_arg X;
    std::vector<std::string> Y_name;  
    std::vector<std::string> X_name;
    
    // std::funcion 无法封装可变参数列表的函数
    // std::unordered_map<std::string, std::function<double(double arg1, ... )>> A; 
};

template <typename s, typename... ss>
bool DeraviationSlove::Y_add(s arg1, ss... arg2)
{
    forumal_function f_temp;
    std::string str(arg1);
    Y_name.push_back(str);
    std::pair<std::string,forumal_function> single(str,f_temp);
    Y.insert(single);
    // std::cout << str << std::endl;
    // 打印变量类型
    // std::cout << boost::typeindex::type_id_with_cvr<decltype(arg1)>().pretty_name() << std::endl;
    Y_add(arg2...);
}

bool DeraviationSlove::X_add(std::string name, double value)
{
    X_name.push_back(name);
    X.insert(std::make_pair(name,value));
}

double DeraviationSlove::XVaule(std::string _x_name, x_arg arg)
{
    x_arg::iterator iter = arg.find(_x_name);
    if(iter == arg.end())
    {
        std::cout << "没有找到该X元素！" << std::endl;
        assert(0);
    }
    else
    {
        double temp = (iter->second);
        return temp;
    }
};

void DeraviationSlove::item_add(std::string _y_name, item_function _func)
{
    auto iter = Y.find(_y_name);
    if(iter == Y.end())
    {
        Y_add(_y_name);
    }

    Y.find(_y_name)->second.push_back(_func);
};

// 微分计算
double DeraviationSlove::DeraciationCal(std::string _y_name, std::string _x_name)
{
    auto iter = Y.find(_y_name);
    if(iter == Y.end())
    {
        std::cout << "没有找到Y元素" << std::endl;
        assert(0);
    }
    double result1 = 0, result2 = 0; 
    x_arg temp(X);
    auto x_iter = temp.find(_x_name);
    x_iter->second+=min;
    // 检查是否有0值，加上一个double的无穷小
    for( auto &x_value : temp)
    {
        if(x_value.second == 0)
        {
            x_value.second+=min_inf;
        } 
    }

    for(auto iter:temp)
    {
        std::cout << iter.first << "=" << iter.second << std::endl;
    }        


    for (auto item : iter->second)
    {
        result1 += item(temp);
    }
    x_iter->second-=min2;
    for (auto item : iter->second)
    {
        result2 += item(temp);
    }

    return (result1-result2)/min2;
}

// 计算雅克比矩阵
Eigen::MatrixXd DeraviationSlove::DeraciationCalMatrix()
{
    int row = Y_name.size();
    int col = X_name.size();
    Eigen::MatrixXd M;
    M.resize(row,col);
    for(int i=0; i<row; i++)
    {
        for(int j=0; j<col; j++)
        {
            M(i,j) = DeraciationCal(Y_name[i],X_name[j]);
            // std::cout << DeraciationCal(Y_name[i],X_name[j]) << std::endl;
        }
    }
    return M;
}

int main(int argc, char** argv)
{
    DeraviationSlove H;

    // H.Y_add("Y1", "Y2", "Y3");
    // H.Y_show();

    DeraviationSlove::item_function temp=[&](DeraviationSlove::x_arg arg)->double
    {
        return 5 * H.XVaule("X1", arg) * H.XVaule("X1", arg);
    };    
    H.item_add("Y1",temp);
    temp = [&](DeraviationSlove::x_arg arg)->double
    {
        return 6*H.XVaule("X1", arg) +6*H.XVaule("X2", arg );
    };    
    H.item_add("Y1",temp);

    temp = [&](DeraviationSlove::x_arg arg)->double
    {
        return 2*H.XVaule("X1", arg)*H.XVaule("X1", arg) + 5*H.XVaule("X3", arg );
    };    
    H.item_add("Y2",temp);

    temp = [&](DeraviationSlove::x_arg arg)->double
    {
        return 2*H.XVaule("X1", arg)*H.XVaule("X1", arg) + 5*H.XVaule("X3", arg );
    };    
    H.item_add("Y2",temp);

    temp = [&](DeraviationSlove::x_arg arg)->double
    {
        return 8*H.XVaule("X2", arg)*H.XVaule("X3", arg) + H.XVaule("X3", arg );
    };    
    H.item_add("Y3",temp);

    temp = [&](DeraviationSlove::x_arg arg)->double
    {
        return 8*H.XVaule("X2", arg)/H.XVaule("X3", arg) + H.XVaule("X3", arg );
    };    
    H.item_add("Y4",temp);    

    // case 1
    // H.X_add("X1",5);
    // H.X_add("X2",4);
    // H.X_add("X3",2); 

    // case 2
    H.X_add("X1",5);
    H.X_add("X2",4);
    H.X_add("X3",0); 

    // 计算指定偏导数
    // std::cout << H.DeraciationCal("Y1", "X1") << std::endl;

    Eigen::MatrixXd M = H.DeraciationCalMatrix();
    std::cout << M <<std::endl;

    double test= 8/min_inf;
    std::cout << "test = " << test << std::endl;

    test= 8.0/0.0; // 浮点数x.0/0.0得到inf，而不是nan。x不为0。
    std::cout << "test = " << test << std::endl;

    return 0;
}

// map自动排序，unordered_map hash存储，顺序不定。
// 如果要使用按插入顺序的键值对
// 成员函数前面加上_m
// 关键的实现就是表达式如何表示，表达式是一个多项式，如5*x_1^{3} + 6*x_1*x_2 + x_1*x_2*x_3;
// x_1,x_2,x_3在具体计算时需要传值进来，那么很自然的，我们将这个表达式定义为一个函数。但是因为不止一个多项式，每一个多项式都需要传入参数。那么很自然就是每个多项式都传入一个参数的全集。
// 因为参数类型为double，所以要解析这个参数集只能靠约定好这个参数集中参数的顺序中的意义。这样其实不方便加入和修改，所以使用了键值对<std::string,double>将变量名称和变量值进行绑定。
// nan (not a number的简写)，计算出错时会得到。 如inf-inf
// case2优化