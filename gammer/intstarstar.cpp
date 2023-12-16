#include <iostream>

using namespace std;

int main()
{
    int a = 10;
    int *b = &a; 
    int **c = &b;
    cout << "a_adress:" << &a << endl;
    cout << "b:" << b << endl;
    cout << "b_adress:" << &b << endl;
    cout << "c:" << c << endl;
    cout << "a:" << **c << endl;

    // 二維數組
    int **ptr2dim = new int* [10];
    ptr2dim[0] = new int [10]{0,1,2,3,5,6,7,8,9};
    cout << ptr2dim[0][5] << endl;
    
    return 0;
}