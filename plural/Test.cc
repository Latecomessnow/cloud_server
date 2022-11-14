#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>

using namespace std;

class plural
{
public:
	plural()
	{}

	plural(int real, int image)
		: _x(real)
		, _y(image)
	{}

	void Print() const
	{
		if (_x == 0 && _y == 0)
		{
			cout << "0" << endl;
		}
		else if (_x == 0 && _y != 0)
		{
			cout << _y << "i" << endl;
		}
		else if (_x > 0 && _y > 0)
		{
			cout << _x << "+" << _y << "i" << endl;
		}
		else
		{
			cout << _x << _y << "i" << endl;
		}
	}

private:
	int _x = 0;
	int _y = 0;
};

int main()
{
	plural p1;
	plural p2(0, 1);
	plural p3(0, -2);
	plural p4(1, -1);
	plural p5(1, 2);
	p1.Print();
	p2.Print();
	p3.Print();
	p4.Print();
	p5.Print();
	return 0;
}
