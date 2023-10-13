#include <iostream>
#include <unistd.h>

using namespace std;

int main()
{
    char buffer[1024];
    while (true)
    {
        // 从标准输入中读取数据
        ssize_t s = read(0, buffer, sizeof(buffer) - 1);
        if (s > 0)
        {
            buffer[s] = '\0';
            cout << "echo# " << buffer << endl;
        }
        else
        {
            // TODO 
            cout << "read \"error\"" << endl;
        }
    }
    return 0;
}