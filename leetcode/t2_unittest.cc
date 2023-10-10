#include "t2.h"
#include "gtest/gtest.h"

std::vector<int> nums{1,1,1,2,3,4,4,5,6,6,7,7,7,9};

TEST(MyString, case1) 
{
    EXPECT_EQ(3, findnum(nums,0,nums.size()-1,2));
    EXPECT_EQ(12, findnum(nums,0,nums.size()-1,8));
    EXPECT_EQ(13, findnum(nums,0,nums.size()-1,9));
    EXPECT_EQ(-1, findnum(nums,0,nums.size()-1,0));
}