#include<iostream>

using namespace std;

class A

{

public:

  A() { cout<<"A::A()"<<endl; }

  ~A() { cout<<"A::~A()"<<endl; }

  int a;

};



class B : public A

{

public:

  B() { cout<<"B::B()"<<endl; }

  ~B() {cout<<"B::~B()"<<endl; }

  int b;

};



void f()

{

  B b;

}

int main()
{
    f();
    return 0;
}
