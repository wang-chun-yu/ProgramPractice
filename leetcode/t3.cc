#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "t3.h"

// 策略模式:使用者可以方便的更换各种策略


std::string MeanbaseA::Mean(std::string line)
{
    bool flag_start = false;
    bool desired_fuhao = 0;
    std::string ss;
    std::string ss_result;
   
    for(int i=0; i<line.size(); i++)
    {
        char ch = line[i];
        // std::cout << "ch:" << ch << std::endl;
        if( ch == '0' && !flag_start) // 开始计数
        {    
            ss+='0';
            flag_start = true;
            desired_fuhao = 1;
            // std::cout << "start:" << ss << std::endl;
        }
        else if(flag_start) // 计算中
        {
            if( (ch-'0') == desired_fuhao) // 目标符号
            {
                ss+=ch;
                desired_fuhao = !desired_fuhao;
                // std::cout << "desired_fuhao:" << desired_fuhao << std::endl;
                // std::cout << "calculate:" << ss << std::endl;

                // 最后一个的处理
                if(i == (line.size()-1))
                {
                    if(ch == '1')
                    {
                        ss.pop_back();
                    }
                    if( ( ss_result.size() < ss.size() )
                    && (ss.size()>=3) )
                    {
                        ss_result = ss;
                        // std::cout << "result:" << ss_result << std::endl;
                        ss.clear();
                    }
                }
            }   
            else 
            {
                // std::cout << "check" << std::endl;
                if(ch == '1')
                {
                    ss.pop_back();
                }

                if( ( ss_result.size() < ss.size() )
                   && (ss.size()>=3) )
                {
                    ss_result = ss;
                    // std::cout << "result:" << ss_result << std::endl;
                }

                ss.clear();

                if (ch == '0')
                {
                    ss+='0';
                    desired_fuhao = 1;
                }
                else
                {
                    flag_start = false;
                }
            }
        }
    }

    
    if(ss_result.size()==0)
    {
        return std::string("-1");
    }
    else
    {
        return std::move(ss_result);
    }    
}



std::string MeanbaseB::Mean(std::string line)
{
    std::string line_add_waves;
    std::vector<std::string> ss_buf;
    int max_num = -1; 

    line_add_waves.push_back(line[0]);
    for(int i=1; i<line.size(); i++)
    {
        if(line[i] == line[i-1])
        {
            line_add_waves.push_back('~');          
        }
        line_add_waves.push_back(line[i]);
    }

    std::stringstream line_stream(line_add_waves);
    std::string ss;
    while(getline(line_stream, ss, '~'))
    {
        ss_buf.push_back(ss);
    }

    for(auto ch : ss_buf)
    {
        if(ch.size()>=3)
        {
            int size_temp = ch.size();
            if(ch.front()=='1') { --size_temp;}; 
            if(ch.back()=='1') { -- size_temp;}; 
            if(size_temp>=3 && size_temp >= max_num)
            {
                max_num = size_temp;
            }
        }
    }

    if(max_num == -1)
    {
        return std::string("-1");
    }
    else
    {
        std::string tmp;
        for(int i=0; i<(max_num-1)/2; i++)
        {
            tmp.push_back('0');
            tmp.push_back('1');
        }
        tmp.push_back('0');
        return std::move(tmp);
    }
}

std::string MeanbaseC::Mean(std::string line)
{
    // 在连续的零字符中加入~
    std::string line_add_waves;
    std::vector<std::string> line_buf;
    std::string result{"-1"};
    int16_t max_num = -1;
    line_add_waves.push_back(line[0]);
    for(int i=1; i<line.size(); ++i)
    {
        if (line[i] == line[i-1])
        {    
            if(line[i] == '0')
            {
                line_add_waves.push_back('~');
            }
            else
            {
                line_add_waves.push_back('/');
            }
        }    
        line_add_waves.push_back(line[i]);
    }
    std::stringstream line_add_waves_stream(line_add_waves);
    std::string tmp;
    while(getline(line_add_waves_stream, tmp, '~'))
    {
        line_buf.push_back(tmp);
    }
    for(auto it : line_buf)
    {
        int16_t cur_size = it.size();
        if(cur_size>=3 && max_num <= cur_size)
        {
            bool flag_rightseq{true};
            for(auto ch:it)
            {
                if(ch == '/') {flag_rightseq = false; break;};
            }
            if(flag_rightseq)
            {
                max_num = cur_size;
                result = it;
            }
        }
    }
    return result;
};