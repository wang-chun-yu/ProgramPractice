#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

int main(int argc, char** argv)
{
    uint8_t car_color;
    vector<uint16_t> buf_color;
    uint16_t during_time = 0;  
    uint16_t max = 0;
    // vector<uint16_t> color_sum{0,0,0};
    unordered_map<uint8_t, uint16_t> color_sum{
        {0,0},{1,0},{2,0}};
    while( (car_color =cin.get())!='\n')
    {
        if(car_color !=' ')
        {
            buf_color.push_back(car_color-'0');
        }
    }
    for(auto ch:buf_color)
    {
        cout << ch << endl;
    }
    cin >> during_time;

    // cout << "during_time:" << during_time << endl;

    // // 值传递只传递一次，以后每次使用都不会重新传值
    // auto getmax = [&color_sum, &max]{
    //     for(auto ch:color_sum)
    //     {
    //         cout << "==ch:" << ch.second << endl;
    //         if(ch.second > max)
    //         {
    //             max = ch.second;
    //         }
    //     }
    // };

    // if(during_time > buf_color.size())
    // {
    //     for(int i=0; i<buf_color.size(); i++)
    //     {
    //         color_sum.find(buf_color[i])->second++;
    //     }
    //     getmax();
    // }
    // else
    // {
    //     for(int i=0; i<during_time; i++)
    //     {
    //         color_sum.find(buf_color[i])->second++;
    //     }

    //     getmax();

    //     for(int i = during_time; i<buf_color.size();i++)
    //     {
    //         color_sum.find(buf_color[i])->second++;
    //         color_sum.find(buf_color[i-during_time])->second--;
    //         getmax();
    //     }
    // }

    for(int i = 0; i<buf_color.size();i++)
    {
        // color_sum.find(buf_color[i])->second++;
        color_sum[buf_color[i]]++;
        if(i>=during_time)
        {
            color_sum[buf_color[i-during_time]]--;
        }
        
        for(auto ch:color_sum)
        {
            cout << "2:" << ch.second << endl;
            if(ch.second > max)
            {
                max = ch.second;
            }
        }
    }    

    cout << max << endl;

    return 0;
}