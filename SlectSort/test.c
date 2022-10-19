#include<stdio.h>

void Swap(int* p1, int* p2)
{
    int tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
}

void SlectSort(int* a, int n)
{
    int left = 0, right = n - 1;
    while (left < right)
    {
        int begin = left, end = right;
        int min = left, max = left;
        int i = 0;
        for (i = begin + 1; i <= end; i++)
        {
            if (a[i] < a[min])
                min = i;
            if (a[i] > a[max])
                max = i;
        }
        Swap(&a[min], &a[begin]);
        if (max == begin)
            max = min;
        Swap(&a[max], &a[end]);
        left++;
        right--;
    }
}

int main()
{
    int a[] = {2, 4, 1, 6, 19, 23, 0, 4, 2, 6, 10 };
    int i = 0;
    for (i = 0; i < sizeof(a) / sizeof(int); i++)
    {
        printf("%d ", a[i]);
    }
    putchar('\n');
    SlectSort(a, sizeof(a) / sizeof(int));
    int j = 0;
    for (j = 0; j < sizeof(a) / sizeof(int); j++)
    {
        printf("%d ", a[j]);
    }
    putchar('\n');
    return 0;
}
