#include<iostream>
#include<vector>
using namespace std;
int main(int argc, char const *argv[])
{
	vector<int> vec;
	vec.push_back(4);
	vec.push_back(1);
	vec.push_back(8);
	cout<<"size="<<vec.size()<<endl;
	for(vector<int>::iterator itr=vec.begin();itr!=vec.end();++itr)
		cout<<*itr<<endl;
	int*p = &vec[0];
	cout<<"*(p+2)="<<*(p+2)<<endl;
	return 0;
}