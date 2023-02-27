#include <iostream>

int main()
{
    int a = 0;
    std::cout << a << std::endl;
    //int *p = nullptr;
    int *p = &a;
    *p = 100;
    std::cout << *p << std::endl;
    return 0;
}