#include <iostream>
#include <list>
#include <vector>
#include <fstream>
#include <algorithm>
#include <climits>
#include <queue>
#define NIL -1;
using namespace std;
enum Color {BLACK, GRAY, WHITE};
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
	pair<int,int>* BFS(int s)
	{
		if(s>=n)
			return NULL;
		Color color[n];
		pair<int,int>* dp = new pair<int,int>[n];
		int u;
		for(int i=0;i<n;i++)
		{
			if(i!=s)
			{
				color[i] = WHITE;
				dp[i].first = INT_MAX;
			}
			dp[i].second = NIL;
		}
		color[s] = GRAY;
		dp[s].first = 0;
		queue<int> Q;
		Q.push(s);
		while(!Q.empty())
		{
			u = Q.front();
			Q.pop();
			for(auto v:Adj[u])
			{
				if(color[v]==WHITE)
				{
					color[v]=GRAY;
					dp[v].first=dp[u].first+1;
					dp[v].second=u;
					Q.push(v);
				}
			}
			color[u]=BLACK;
		}
		return dp;
	}
};
int main()
{
	int n, m;
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
	cout<<endl;
	pair<int,int>* dp = G.BFS(1);
	cout<<"i d p\n";
	for(int i=0;i<n;i++)
		cout<<i<<" "<<dp[i].first<<" "<<dp[i].second<<endl;
	delete [] dp; 
	return 0;
}