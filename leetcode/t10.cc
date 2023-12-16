#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    auto getmax = [](vector<uint16_t> _v)->uint16_t{
        uint16_t res = 0;
        for(auto ch :_v)
        {
            if (ch > res)
            {
                res = ch;
            }
            
        }
        return res;
    };
    auto getmin = [](vector<uint16_t> _v)->uint16_t{
        uint16_t res = UINT16_MAX;
        for(auto ch :_v)
        {
            if (ch < res)
            {
                res = ch;
            }
            
        }
        return res;
    };
    vector<vector<uint16_t>> v{{20,30,40},{55,2,99}, {22,56, 65}};
    vector<uint16_t> v_result; 
    for(int i=0;i<v.size();i++)
    {
        v_result.push_back(getmax(v[i]));
    }     
    cout << getmin(v_result) << endl;
    
    return 0;
}

