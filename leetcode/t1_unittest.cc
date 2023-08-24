#include "t1.h"
#include "gtest/gtest.h"

const string path = "/home//foo/";

TEST(MyString, case1) 
{
    Solution A;
    A.simplifyPath(path);
    EXPECT_EQ(0, strcmp(A.simplifyPath(path).c_str(), "/home/foo"));
}