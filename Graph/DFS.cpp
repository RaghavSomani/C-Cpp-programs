#include <iostream>
#include <list>
#include <vector>
#include <fstream>
#include <algorithm>
#define NIL -1;
using namespace std;
enum Color {BLACK, GRAY, WHITE};
class Graph
{
public:
	int n;
	bool dir;
	int time;
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
	pair<pair<int,int>,int>* DFS(void)
	{
		pair<pair<int,int>,int>* dfp = new pair<pair<int,int>,int>[n];
		Color color[n];
		for(int u=0;u<n;u++)
		{
			color[u]=WHITE;
			dfp[u].second=NIL;
		}
		time=0;
		for(int u=0;u<n;u++)
			if(color[u]==WHITE)
				DFS_Visit(u,color,dfp);
		return dfp;
	}
	void DFS_Visit(int u, Color color [], pair<pair<int,int>,int>* dfp)
	{
		dfp[u].first.first=++time;
		color[u]=GRAY;
		for(auto v:Adj[u])
			if(color[v]==WHITE)
			{
				dfp[v].second=u;
				DFS_Visit(v,color,dfp);
			}
		color[u]=BLACK;
		dfp[u].first.second=++time;
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
	pair<pair<int,int>,int>* dfp=G.DFS();
	cout<<"i d f p\n";
	for(int i=0;i<n;i++)
		cout<<i<<" "<<dfp[i].first.first<<" "<<dfp[i].first.second<<" "<<dfp[i].second<<endl;
	delete [] dfp;
	return 0;
}