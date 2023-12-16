#include <iostream>

void func2(const int& x)
{
    std::cout << "rvalue" << std::endl;
} 

void func2(int& x)
{
    std::cout << "lvalue" << std::endl;
}

template <typename T>
void func1(T&& x)
{
    func2(std::forward<T>(x));
}



int main(int argc, char** argv)
{
    func1(5);
    int x = 10;
    func1(x);
    return 0;
}