#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

int main()
{
    auto isexistedstr = [](string s1, string s2)->bool{
        bool mark = true;
        for(auto ch : s1)
        {
            if(s2.find(ch) < s2.size())
            {
                mark = false;
                break;
            }
        }
        return mark;
    };

    vector<string> ss{"ab", "bcd", "efg", "hecgi", "xyzl"};
    int result = 0;
    for(int i=0; i<ss.size()-1; i++)
    {
        for(int j=i+1; j<ss.size(); j++)
        {
            if(isexistedstr(ss[i].c_str(),ss[j].c_str()))
            {
                int temp = ss[i].size()*ss[j].size();
                result = result>temp ? result : temp;
            }
        }
    }
    cout << result << endl;
    cout << strcmp("fidjf","ifi");
    return 0;
}