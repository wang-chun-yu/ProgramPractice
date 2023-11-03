#include <iostream>
#include <string>
#include <sstream>
#include <cassert>

int main(int argv, char** argc)
{
    std::string s,ss;
    getline(std::cin, ss, '\n'); // 获取一行数据
    std::stringstream ss_stream(ss); // 装换成流对象
    getline(ss_stream, s, ' ');
    uint16_t num = stoi(s); // 将string类型转化为int类型 

    char a;
    int b;
    float c;
    std::cin >> a >> b >> c;  // 会自动进行类型转换，跳过空格 

    int sss = std::cin.get(); // 能获取空格，换行，回车，制表，终止符．
                              // 需要用int类型
}