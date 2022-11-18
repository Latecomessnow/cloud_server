#include<iostream>
#include<iomanip>
#include<string>

using namespace std;

class Student
{
public:
	friend void Display(Student s);

	friend class Teacher;

	Student(const string& id = "0000", const string& name = "LiHua", const int& score = 0)
		: _id(id)
		, _name(name)
		, _score(score)
	{}

private:
	string _id;
	string _name;
	int _score;
};

class Teacher
{
public:
	void Display(const Student& s) const
	{
		if (s._score >= 90)
			cout << left << setw(20) << s._name << setw(20)
			<< s._score << setw(20) << "优秀" << endl;
		else if (s._score >= 80 && s._score <= 89)
			cout << left << setw(20) << s._name << setw(20)
			<< s._score << setw(20) << "良好" << endl;
		else if (s._score >= 70 && s._score <= 79)
			cout << left << setw(20) << s._name << setw(20)
			<< s._score << setw(20) << "中等" << endl;
		else if (s._score >= 60 && s._score <= 69)
			cout << left << setw(20) << s._name << setw(20)
			<< s._score << setw(20) << "合格" << endl;
		else
			cout << left << setw(20) << s._name << setw(20)
			<< s._score << setw(20) << "不合格" << endl;
	}

	void Modifly(const int& score, Student& s) const
	{
		s._score = score;
	}
};

void Menu()
{
	cout << left << setw(20) << "姓名" << setw(20)
		<< "成绩" << setw(20) << "等级" << endl;
	cout << "--------------------------------------------" << endl;
}

int main()
{
	Menu();
	Teacher t;
	Student s1("0512", "HuiGu", 90);
	Student s3("0514", "LiHua", 80);
	Student s4("0515", "DaMing", 77);
	const Student s2("0513", "LingLing", 80);
	t.Display(s1);
	t.Display(s2);
	t.Modifly(80, s1);
	t.Display(s1);
	t.Display(s3);
    t.Display(s4);
	return 0;
}
