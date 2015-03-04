#include <iostream>
#include <string>
#include <vector>
using namespace std;
vector<string> explode(string s, const char c);
int main()
{
	string s{"the quick brown fox jumps over the lazy dog"};
	vector<string> v=explode(s,' ');
	for(auto i:v)
		cout<<i<<endl;
	return 0;
}
vector<string> explode(string s, const char c)
{
	string buff{""};
	vector<string> v;
	for(auto i:s)
	{
		if(i!=c)
			buff+=i;
		else if(i==c && buff!="")
		{
			v.push_back(buff);
			buff="";
		}
	}
	if(buff!="")
		v.push_back(buff);
	return v;
}