#include <iostream>
#include <set>

using namespace std;

int main()
{
    auto fun1 = [](string ss, int i, int j)->bool{
        bool result = true;
        int sum = 0;
        for(int cnt=i;cnt<j+1;cnt++)
        {
            if(ss[cnt]=='0')
            {
                sum++;
            }
        }
        if(sum != (j-i+1)/2)
        {
            result = false;
        }
        return result;
    };

    string ss = "0101101110100101000101000";
    set<string> buf;
    for(int i=0; i<ss.size()-1; i++) //
    {
        for(int j=i+1; j<ss.size(); j+=2)
        {
            if(fun1(ss, i, j))
            {
                string temp = ss.substr(i,j-i+1);
                buf.emplace(temp);
            }
        }
    }
    for (auto ch : buf)
    {
        cout << ch << endl;
    }
    return 0;
}