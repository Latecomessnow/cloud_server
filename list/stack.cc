#include<iostream>
#include<stack>

using namespace std;


int main()

{

stack<char> S;

char x,y;

x='n';y='g';

S.push(x);S.push('i');S.push(y);

S.pop();S.push('r');S.push('t');S.push(x);

S.pop();S.push('s');

while(!S.empty())

{

x = S.top();

S.pop();

cout<<x;

};

cout<<y;

cout << endl;
}
