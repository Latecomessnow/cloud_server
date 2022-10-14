#include<iostream>
#include<string>

using namespace std;

int main() {
    string str, res, cur;
    cin >> str;
    //     for (int i = 0; i <= str.length(); i++) {
    // // 数字+=到cur
    //         if (str[i] >= '0' && str[i] <= '9') {
    //             cur += str[i];
    //         } 
    //         else {
    // // 找出更长的字符串，则更新字符串
    //             if (res.size() < cur.size())
    //                 res = cur;
    //             cur.clear();
    //         }
    //     }
    int i = 0;
    // 这里一定不能少了等号，因为有可能最长数字字符串是在最后面的i指向\0时才能把cur赋给res
    while (i <= str.size())
    {
        if (str[i] >= '0' && str[i] <= '9') {
            cur += str[i];
        }
        else
        {
            if (res.size() < cur.size()) {
                res = cur;
            }
            else
                cur.clear();
        }
        i++;
    }
    cout << res << endl;
    return 0;
}
