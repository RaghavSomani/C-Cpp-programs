#include <iostream>
#include <deque>
using namespace std;
int main()
{
	deque<float> coll;      			//deque container for floating-point elements
	for (int i=1; i<=6; ++i)
    	coll.push_front(i*1.1);        //insert at the front... push_back() to add the other way
	for (int i=0; i<coll.size(); ++i)
		cout << coll[i] << ' ';
	cout << endl;
}
