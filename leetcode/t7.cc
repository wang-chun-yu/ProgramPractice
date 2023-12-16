#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

// void generateCombinations(const std::vector<std::string>& numStrings, int k, int start,
//                           std::vector<int>& current, std::vector<std::vector<int>>& combinations) {
//     if (k == 0) {
//         combinations.push_back(current);
//         return;
//     }

//     for (int i = start; i <= numStrings.size() - k; i++) {
//         current.push_back(std::stoi(numStrings[i]));
//         generateCombinations(numStrings, k - 1, i + 1, current, combinations);
//         current.pop_back();
//     }
// }

// int main() {
//     std::string input;
//     std::getline(std::cin, input);
//     std::vector<std::string> numStrings;

//     std::stringstream ss(input);
//     std::string num;
//     while (std::getline(ss, num, ',')) {
//         numStrings.push_back(num);
//     }

//     int n;
//     std::cin >> n;

//     std::vector<std::vector<int>> combinations;
//     std::sort(numStrings.begin(), numStrings.end());

//     for (int i = n; i <= numStrings.size(); i++) {
//         std::vector<int> current;
//         generateCombinations(numStrings, i, 0, current, combinations);
//     }

//     if (!combinations.empty()) {
//         for (const auto& combination : combinations) {
//             std::string combinationString;
//             for (int num : combination) {
//                 combinationString += std::to_string(num) + ",";
//             }
//             combinationString.pop_back();
//             std::cout << combinationString << std::endl;
//         }
//     } else {
//         std::cout << "None" << std::endl;
//     }

//     return 0;
// }

void get(vector<int>& source, int start, int n, vector<int>& buf, vector<vector<int>>& ss_buf)
{
    if(n == 0)
    {
        ss_buf.push_back(buf);
        return;
    }

    for(int i=start; i<source.size()-n+1; i++)
    {
        buf.push_back(source[i]);
        get(source,i+1,n-1,buf,ss_buf);
        buf.pop_back();
    }
}


int main()
{
    using namespace std;
    vector<int> nums{1,2,3,4,5,6,7,8,9};
    // for (int i = 0; i < nums.size()-2; i++)
    // {
    //     for(int j= i+1; j < nums.size()-1; j++)
    //     {
    //         for(int k=j+1; k < nums.size(); k++)
    //         {
    //             std::cout << nums[i] << nums[j] << nums[k] << endl;
    //         }
    //     }
    // }
// 递归的方法 0 3 5

    vector<int> buf;
    vector<vector<int>> ss_buf;
    get(nums, 0, 3, buf, ss_buf);
    for(auto ch : ss_buf)
    {
        for(auto c : ch)
        {
            cout << c;
        }
        cout << endl;
    }

}

