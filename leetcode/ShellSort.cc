#include<iostream>
#include<string.h>

using namespace std;

void ShellSort(int* a, int n)
{
	int gap = n;
	while (gap >= 1)
	{
		gap = gap / 2;
		for (int i = 0; i < n - gap; i++)
		{
			int end = i;
			int tmp = a[end + gap];
			while (end >= 0)
			{
				if (tmp < a[end])
				{
					a[end + gap] = a[end];
					end -= gap;
				}
				else
					break;
			}
			a[end + gap] = tmp;
		}
	}
	//int gap = 3;
	//for (int j = 0; j < gap; j++)
	//{
	//	for (int i = j; i < n - gap; i += gap)
	//	{
	//		int end = i;
	//		int tmp = a[end + gap];
	//		while (end >= 0)
	//		{
	//			if (tmp < a[end])
	//			{
	//				a[end + gap] = a[end];
	//				end -= gap;
	//			}
	//			else
	//				break;
	//		}
	//		a[end + gap] = tmp;
	//	}
	//}
}

int main()
{
	int arr[] = { 19, 2, 3, 45, 3, 2, 6, 0, 4, 1, 2, 23, 19, 20 };
	int a[] = { 9, 1, 2, 5, 7, 4, 8, 6, 3, 5, 10, 20, 12, 3 };
	ShellSort(a, sizeof(a) / sizeof(int));
	for (int i = 0; i < sizeof(a) / sizeof(int); i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
	ShellSort(arr, sizeof(arr) / sizeof(int));
	for (int i = 0; i < sizeof(arr) / sizeof(int); i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
	return 0;
}
