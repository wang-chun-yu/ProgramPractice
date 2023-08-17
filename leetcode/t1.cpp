/*
 * @Author: wangpeiying04 wangpeiying04@countrygarden.com.cn
 * @Date: 2023-08-17 15:23:22
 * @LastEditors: wangpeiying04 wangpeiying04@countrygarden.com.cn
 * @LastEditTime: 2023-08-17 20:09:11
 * @FilePath: /ProgramPractice/leetcode/t1.cpp
 * @Description: 
 * 
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved. 
 */

#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    string simplifyPath(string path) {
        auto split = [](const string& s, char delim) -> vector<string> {
            vector<string> ans;
            string cur;
            for (char ch: s) {
                if (ch == delim) {
                    ans.push_back(move(cur));
                    cur.clear();
                }
                else {
                    cur += ch;
                }
            }
            ans.push_back(move(cur));
            return ans;
        };

        vector<string> names = split(path, '/');
        vector<string> stack;
        for (string& name: names) {
            if (name == "..") {
                if (!stack.empty()) {
                    stack.pop_back();
                }
            }
            else if (!name.empty() && name != ".") {
                stack.push_back(move(name));
            }
        }
        string ans;
        if (stack.empty()) {
            ans = "/";
        }
        else {
            for (string& name: stack) {
                ans += "/" + move(name);
            }
        }
        return ans;
    }
};

int main()
{
    // string path = "/a/./b/../../c/";
    // string path = "/home/";
    // string path = "/../";
    string path = "/home//foo/";
    Solution A;
    A.simplifyPath(path);
    return 0;
}