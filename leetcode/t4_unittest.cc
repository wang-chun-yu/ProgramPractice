# include "t3.h"
# include "gtest/gtest.h"
// 提取字符串特征
// 开始标志,中间标志,结束标志.

// 特殊求解方法,观察到字符一定满足0101间隔.
// 1. 进行分割,相同的字符间加入~(如果当成流处理只处理一遍,如上面的做法,比较麻烦,需要同时注意开始/中间/结尾的判断.)
// 2. 将字符串进行处理,保证0开头,0结尾.
// 3. 找到最大数组
// 0~0101~101~10~0101010~0~01~10~0101010~0~0101~1010~010~0101~101
// 010101010101010011100101010101001000111010100101010101

std::string case1 = "00101010101100001010010";
std::string result1 = "01010";
std::string case2 = "00101010101000010100100";
std::string result2 = "01010101010";

TEST(MyString, case1) 
{    
    User user1(new MeanbaseC);
    std::cout << user1.useMean(case1) << std::endl;
    
    EXPECT_EQ(0, strcmp(user1.useMean(case1).c_str(), result1.c_str()));
    
    EXPECT_EQ(0, strcmp(user1.useMean(case2).c_str(), result2.c_str()));


} 
