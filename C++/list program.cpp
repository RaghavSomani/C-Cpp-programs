#include<iostream>
#include<list>
#include<algorithm>
using namespace std;
int main()
{
	list<int> mylist;
	list<int>::iterator itr,itra,itrb;
	int i,a;
	for(i=0;i<5;i++)
	{
		cin>>a;
		mylist.push_back(a);
	}
	itra=find(mylist.begin(),mylist.end(),1);
	itrb=find(mylist.begin(),mylist.end(),4);
	mylist.erase(itra,itrb);
	mylist.sort();
	for(itr=mylist.begin();itr!=mylist.end();itr++)
		cout<<*itr;
}
