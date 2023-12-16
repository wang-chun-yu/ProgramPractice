#include <iostream>
#include <algorithm>
#include <array>

using namespace std;

int main(int argc, char** argv)
{
    const uint16_t wallHeight[10] = {10,9,4,7,6,5,4,3,2,1};
    const array<uint16_t,10> arr_wallHeight{10,9,4,7,6,5,4,3,2,1};
    uint16_t result = 0;
    // 从i和j中取最小值
    auto getMin = [wallHeight](int i, int j)->uint16_t
    {
        uint16_t min = wallHeight[i];
        for(int cnt=i+1; cnt<j+1; cnt++)
        {
            if(min > wallHeight[cnt])
            {
                min = wallHeight[cnt];
            }
        }
        return min;  
    }; 
    

    for(int i=0; i<9; i++)
    {
        for(int j=i+1; j<10;j ++)
        {
            uint16_t temp = getMin(i,j)*(j-i);
            result = temp>result ? temp:result;
        }
    }
    cout << result << endl;
    return 0;
}