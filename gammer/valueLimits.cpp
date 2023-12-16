#include <limits>
#include <iostream>

int main()
{
    std::cout << std::numeric_limits<int16_t>::epsilon() << std::endl;
    std::cout << std::numeric_limits<uint16_t>::epsilon() << std::endl;
    std::cout << std::numeric_limits<float>::epsilon() << std::endl;
    std::cout << std::numeric_limits<double>::epsilon() << std::endl;
    return 0; 
}

