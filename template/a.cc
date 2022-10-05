#include<iostream>

using namespace std;

class A

{

public:

  void f(){ cout<<"A::f()"<<endl; }

  int a;   

};



class B : public A

{

public:

  void f(int i){cout<<"B::f()"<<endl;}

  int b;

};



int main()

{

  B b;

  b.f(10);

  return 0;

}
