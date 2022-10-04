#include<iostream>
#include<vector>
#include<list>
#include<deque>

using namespace std;

int main()

{

//Container cont = { 1, 2, 3, 4, 5};

vector<int> cont;
cont.push_back(1);
cont.push_back(2);
cont.push_back(3);
cont.push_back(4);
cont.push_back(5);
vector<int>::iterator iter, tempIt;

for (iter = cont.begin(); iter != cont.end();)

{



tempIt = iter;



++iter;



cont.erase(tempIt);

}

}
