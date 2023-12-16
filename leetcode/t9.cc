#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
    string s1 = "dsfgthe";
    string s2 = "snfsdfhet";
    int16_t start_seq = s2.size();
    for(int i=0; i<s1.size(); i++)
    {
        int16_t  seq=s2.find(s1[i]);
        if(seq < s2.size())
        {
            if(seq<start_seq)
            {
                start_seq = seq;
            }
            continue;
        }
        else
        {
            start_seq = s2.size();
            break;
        }

    }    
    

    if(start_seq == s2.size())
    {
        start_seq = -1;
    }
    
    cout << start_seq << endl;

    return 0;

}