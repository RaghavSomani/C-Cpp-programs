#include <iostream>
#include <list>
using namespace std;
int main()
{
	list<char> coll;         //list container for character elements
    for (char c='a';c<='z'; c++)
		coll.push_back(c);
    while (!coll.empty())
	{
		cout << coll.front() << ' ';
		coll.pop_front();
	}
	cout << endl;
}
