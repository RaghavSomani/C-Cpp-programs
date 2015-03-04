#include <iostream>
#include <list>
#include <vector>
using namespace std;
class Graph
{
public:
	int n;
	vector<list<int> > V;
	Graph(int n=1)
	{
		for(int i=0;i<n;i++)
		{
			list<int> l;
			V.push_back(l);
		};
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
	int v1,v2,v;
	for(int i=0;i<m;i++)
	{
		cin>>v1>>v2;
		G.V[v1].push_back(v2);
		G.V[v2].push_back(v1);
	}
	cout<<"Find neighbours of : ";
	cin>>v;
	for(auto i:G.V[v])
	{
			cout<<i<<" ";
	}
	return 0;
}