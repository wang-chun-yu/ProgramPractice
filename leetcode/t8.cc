#include <iostream>
#include <vector>

using namespace std;

// 全排列组合问题
void get(vector<uint16_t> v, int n, vector<uint16_t>& buf, vector<vector<uint16_t>>& combination) 
{
    if(n == 0)
    {
        combination.push_back(buf);
        return;
    }
    
    for(int i=0;i<v.size();i++)  
    {
        buf.push_back(v[i]);
        vector<uint16_t> temp(v);
        temp.erase(temp.begin()+i);
        get(temp, n-1, buf, combination);
        buf.pop_back();
    }
}


int main(int argc, char** argv)
{
    vector<uint16_t> v{3,5,6,7};
    vector<uint16_t> buf;
    vector<vector<uint16_t>> combination;
    get(v, 2 , buf, combination);
    for(auto it : combination)
    {
        for(auto itt: it)
        {
            cout << itt;
        }
        cout << endl;
    }

// 计算

    return 0;
}
