#include<iostream>
#include<map>
using namespace std;
int main()
{
	map<char,int> mymap;
	mymap.insert(pair<char,int>('a',100));
	mymap.insert(pair<char,int>('z',500));
	mymap.insert(pair<char,int>('b',200));
	map<char,int>::iterator it=mymap.begin();
	for(it=mymap.begin();it!=mymap.end();it++)
		cout<<(*it).first<<" => "<<(*it).second<<endl;
	it=mymap.find('b');
	(*it).second=300;				//only second can be changed
	cout<<endl;
	for(it=mymap.begin();it!=mymap.end();it++)
		cout<<(*it).first<<" => "<<(*it).second<<endl;
}
