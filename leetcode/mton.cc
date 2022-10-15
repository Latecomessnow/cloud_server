#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<algorithm>

using namespace std;

// 1. 计算糖果
//int main()
//{
//    int a, b, c, d;
//    cin >> a >> b >> c >> d;
//    int A = (a + c) / 2;
//    int B1 = (b + d) / 2;
//    int B2 = (c - a) / 2;
//    int C = (d - b) / 2;
//    if (B1 != B2)
//        cout << "No" << endl;
//    else
//        cout << A << " " << B1 << " " << C << endl;
//    return 0;
//}

// 2. 十进制转化成N进制

int main()
{
    int m, n;
    string s, table = "0123456789ABCDEF";
    cin >> m >> n;
    // 将m转换换成n进制的数，注意m有可能为负数
    bool flag = false;
    if (m < 0)
    {
        m = -m;
        flag = true;
    }
    while (m != 0)
    {
        s += table[m % n];
        m /= n;
    }
    if (flag == true)
        s += '-';
    reverse(s.begin(), s.end());
    cout << s << endl;
    return 0;
}
