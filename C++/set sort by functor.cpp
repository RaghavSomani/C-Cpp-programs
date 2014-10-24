#include<iostream>
#include<set>
#include<algorithm>
using namespace std;
class Lsb_less
{
	public:
		bool operator()(int x, int y)
		{
			return (x%10)<(y%10);
		}
			
};
int main()
{
	int x,i;
	set<int, Lsb_less> myset;
	set<int, Lsb_less>::iterator it=myset.begin();
	for(i=0;i<5;i++)
	{
		cin>>x;
		myset.insert(x);
	}
	for(it=myset.begin() ; it!=myset.end() ; it++)
		cout<<(*it)<<" ";
}
