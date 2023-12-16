#include <iostream>
#include <vector>
#include <memory>

using namespace std;

static int a = 10;
shared_ptr<vector<int>> v_ptr(make_shared<vector<int>>(5));

void func()
{
    static vector<int> v{1,2,3,4,5,6,7,8,9};
    v.push_back(10);
}


int main()
{
    func();
    v_ptr->push_back(100);
    return 0;
}
