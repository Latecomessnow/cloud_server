#include<iostream>

using namespace std;

void QuickSort(int* a, int begin, int end)
{

   // 当区间只有一个值或者区间不存在就不需要再递归了
   if (begin >= end)
       return;
   int left = begin, right = end;
   // 因为如果写成key = a[left],交换key的时候交换的是是一个局部变量，而不是key所在的最左位置的值
   int keyi = left; 
   while (left < right)
   {
       // 一般选最左边或者最右边作为key值,把key值设置为下标比较好
       // 右边先走找小,注意需要加上等于，否者可能会遇上这种情况
       // [5 5 5 ... 5],这样就死循环了，还有注意越界情况
       while (left < right && a[right] >= a[keyi])
       {
           // 右边先走，右边先停下来，这样才能保证相遇交换key时，相遇位置的值一定比key小
           right--;
       }
       // 左边再走
       while (left < right && a[left] <= a[keyi])
       {
            left++;
       }
       swap(a[left], a[right]);
   }
   swap(a[keyi], a[left]);
   // 交换keyi后，此时keyi位置的值已经是有序了，只需要再递归keyi两边的区间
   // [begin, keyi - 1] keyi [keyi + 1， end]
   keyi = left;
   QuickSort(a, begin, keyi - 1);
   QuickSort(a, keyi + 1, end);
}

void Print(int* a, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
}

int main()
{
    int a1[] = {5, 5, 2, 4, 1, 7, 10, 2, 3, 5, 9, 5};
    Print(a1, sizeof(a1) / sizeof(int));
    QuickSort(a1, 0, sizeof(a1) / sizeof(int) - 1);
    Print(a1, sizeof(a1) / sizeof(int));
    return 0;
}
