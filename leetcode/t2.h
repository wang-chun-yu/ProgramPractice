// 二分查找
// 升序排列，查找与目标值最接近的数，且其序列号要尽可能的大。
#include <vector>
#include <iostream>




// 考虑边界
int findnum(std::vector<int> nums, int start, int end, int target)
{
    if(target > nums[end])
    {
        return -1;
    }
    else if(target == nums[end])
    {
        return end;
    }

    if(target <nums[start])
    {
        return -1;
    }

    int mid = ( start + end )/2;
    if(mid == start)
    {
        return mid;
    }
    if(target < nums[mid])
    {
        return findnum(nums, start, mid, target);
    }
    else
    {
        return findnum(nums, mid, end, target);
    }
}

// int main()
// {
//     std::vector<int> nums{1,1,1,2,3,4,4,5,6,6,7,7,7,9};
//     std::cout << findnum(nums,0,nums.size()-1,2) << std::endl;
//     std::cout << findnum(nums,0,nums.size()-1,8) << std::endl;
//     std::cout << findnum(nums,0,nums.size()-1,9) << std::endl;
//     std::cout << findnum(nums,0,nums.size()-1,0) << std::endl;
// }