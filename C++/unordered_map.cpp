#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;
int main()
{
	unordered_map<string,int> H;
	H.insert({{"Raghav",1},{"Sumeet",2},{"Desh",3}});
	H.insert({{"Bhuvnesh",1},{"Siddharth",5}});
	H["Minkush"]=6;
	for(int i=0;i<H.bucket_count();i++)
	{
		cout<<i<<" : ";
		for(auto it=H.begin(i);it!=H.end(i);it++)
			cout<<(it->first)<<" ";
		cout<<endl;
	}
	auto it=H.find("Bhuvnesh");
	cout<<it->first<<" "<<it->second<<endl;
	return 0;
}