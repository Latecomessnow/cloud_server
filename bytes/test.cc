#include<iostream>
#include<map>

using namespace std;

int main()
{
    void* ptr = nullptr;
    int a = 0;
    int* ptr2 = &a;
    map<string, int> m;
    map<string, int>* ptr3 = &m;
    ptr3->insert(make_pair("sort", 1));
    cout << sizeof(ptr) << endl;
    cout << sizeof(ptr2) << endl;
    cout << sizeof(ptr3) << endl;
    return 0;
}
