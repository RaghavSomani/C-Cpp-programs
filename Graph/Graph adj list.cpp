#include <iostream>
#include <list>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;
class Graph
{
public:
	int n;
	bool dir;
	vector<list<int> > Adj;
	Graph(int v=1)
	{
		n=v;
		for(int i=0;i<n;i++)
		{
			list<int> l;
			Adj.push_back(l);
		};
	};
	void addEdge(int v, int w)
	{
		if(v>=n||w>=n)
			return;
		Adj[v].push_back(w);
		if(!dir)
			Adj[w].push_back(v);
	}
	bool isEdgePresent(int v, int w)
	{
		if(v>=n||w>=n)
			return false;
		return (find(Adj[v].begin(),Adj[v].end(),w)!=Adj[v].end());
	}
	void printGraph(void)
	{
		cout<<"\n";
		for(int i=0;i<n;i++)
		{
			cout<<i<<" -> ";
			for(auto j:Adj[i])
				cout<<j<<" ";
			cout<<"\n";
		}

	}
	Graph Transpose(void)
	{
		Graph T(n);
		for(int i=0;i<n;i++)
			for(auto j:Adj[i])
				T.Adj[j].push_back(i);
		return T;
	}
	int degree(int v)
	{
		if(v>=n)
			return 0;
		return Adj[v].size();
	}
};
int main()
{
	int n,m;
	char c;
	ifstream fp("input.txt");
	cout<<"Number of nodes : ";
	fp>>n;
	Graph G(n);
	cout<<"Directed Graph? (Y/N) : ";
	fp>>c;
	G.dir=(c=='y'||c=='Y')?true:false;
	int v1,v2,v;
	while(!fp.eof())
	{
		fp>>v1>>v2;
		G.addEdge(v1,v2);
	}
	cout<<"\n";
	
	/*cout<<"Find neighbours of : ";
	cin>>v;
	for(auto i:G.Adj[v])
			cout<<i<<" ";
	*/

	/*cout<<"\nSearch for edge : ";
	cin>>v1>>v2;
	G.isEdgePresent(v1,v2)?cout<<"Edge present":cout<<"Edge not present";
	*/

	/*G.printGraph();
	Graph T=G.Transpose();
	T.printGraph();
	*/

	/*cout<<"Get degree of : ";
	cin>>v1;
	cout<<G.degree(v1);
	*/
	
	return 0;
}