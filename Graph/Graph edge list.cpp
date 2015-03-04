#include <iostream>
#include <vector>
using namespace std;
class Graph
{
public:
	int n;
	vector<int> V;
	vector<pair<int,int>> E;
	Graph(int n=1)
	{
		for(int i=0;i<n;i++)
			V.push_back(i);
	};
};
int main()
{
	int n,m;
	cout<<"Number of nodes : ";
	cin>>n;
	Graph G(n);
	cout<<"Number of edges : ";
	cin>>m;
	int p1,p2,v;
	pair<int,int> p;
	for(int i=0;i<m;i++)
	{
		cin>>p1>>p2;
		p={p1,p2};
		G.E.push_back(p);
		p={p2,p1};
		G.E.push_back(p);
	}
	cout<<"Find adjacent nodes of : ";
	cin>>v;
	for(auto e:G.E)
		if(e.first==v)
			cout<<e.second<<endl;
	return 0;
}