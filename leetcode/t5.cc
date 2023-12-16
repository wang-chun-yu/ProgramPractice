#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include <string>
#include <set>

using namespace std;


int main(int argc, char **argv)
{

    multimap<char, uint16_t> once_zimu, mult_zimu;
    char a;
    string line_add_waves;
    cin >> a;
    line_add_waves.push_back(a);
    while( (a=cin.get())!= '\n')
    {
        cout << a << endl;
        if(a!=line_add_waves.back())
        {
            line_add_waves.push_back('~');
        }
        line_add_waves.push_back(a);
    }
    
    stringstream ss(line_add_waves);
    string s_temp;
    while(getline(ss, s_temp, '~'))
    {   
        char cur_zimu = s_temp[0];
        if(s_temp.size()==1)
        {   
            int num = once_zimu.count(cur_zimu);
            if(num!=0)
            {
                auto iter=once_zimu.find(cur_zimu);
                for(int i=0;i<num;i++,iter++)
                {
                    iter->second++;
                }
            }
            once_zimu.insert(make_pair(cur_zimu,0));
        }
        else
        {
            {
                int num = once_zimu.count(cur_zimu);
                if(num!=0)
                {
                    auto iter=once_zimu.find(cur_zimu);
                    for(int i=0;i<num;i++,iter++)
                    {
                        iter->second+=s_temp.size();
                    }
                }
            }
            mult_zimu.insert(make_pair(cur_zimu, s_temp.size()));
        }
    }

    for(auto unit:mult_zimu)
    {
        once_zimu.emplace(unit);
    }

    // for(auto unit:once_zimu)
    // {
    //     cout << unit.first << unit.second;
    // }

    // multimap<uint16_t, char, greater<uint16_t>> sort_buf;
    // for(auto it : once_zimu)
    // {
    //     sort_buf.emplace(make_pair(it.second, it.first));
    // }
    // for(auto it: sort_buf)
    // {
    //     cout << it.second << it.first;
    // }

    map<uint16_t, set<char>, greater<uint16_t>> sort_buf;
    for(auto it : once_zimu)
    {
        sort_buf[it.second].insert(it.first);
    }
    for(auto it: sort_buf)
    {
        for(auto itt :it.second)
        {
            cout << itt << it.first;
        }
        
    }


    return 0;
}




