#include <iostream>
#include <map>
#include <string>
using namespace std;
class comp
{
public:
	bool operator()(string a,string b)
	{
		return (a.length()<b.length());
	};
};
int main()
{
	map<string,int,comp> M;
	M.insert(pair<string,int>("hello",5));
	M.insert(pair<string,int>("hi",10));
	M["hey"]=15;
	map<string,int,comp>::iterator it;
	for(it=M.begin();it!=M.end();++it)
		cout<<(*it).second<<endl;
	return 0;
}