#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main()
{
    vector<int> ret;
    int n = 0;
    cin >> n;
    long long sum = 0;
    for (int i = 0; i < (3 * n); i++)
    {
        int val = 0;
        cin >> val;
        ret.push_back(val);
    }
    sort(ret.begin(), ret.end());
    int count = n;
    while (count--)
    {
        sum += ret[n];
        n += 2;
    }
    cout << sum << endl;
    return 0;
}
