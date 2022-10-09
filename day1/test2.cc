#include<iostream>
#include<stdio.h>
#include<vector>
#include<string>

using namespace std;

int main()
{
	string s1;
	string s2;
	string s3;
	while (1)
	{
		char ch = 0;
		ch = getchar();
		if (ch == '\n')
			break;
		s1.push_back(ch);
	}
	while (1)
	{
		char ch = 0;
		ch = getchar();
		if (ch == '\n')
			break;
		s2.push_back(ch);
	}
	int flag = 1;
	for (int i = 0; i < s1.size(); i++)
	{
		for (int j = 0; j < s2.size(); j++)
		{
			if (s1[i] == s2[j])
			{
				flag = 0;
				break;
			}
		}
		if (flag == 1)
			s3.push_back(s1[i]);
		flag = 1;
	}
	cout << s3 << endl;
	return 0;
}
