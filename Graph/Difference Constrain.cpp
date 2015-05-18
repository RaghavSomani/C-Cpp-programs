#include <iostream>
#include <list>
#include <vector>
#include <fstream>
#include <algorithm>
#include <climits>
using namespace std;
class Node
{
public:
	int key;
	int d;
	Node* p;
	Node(int k=0)		{	key=k;	};
	Node(const Node& v)	{	key=v.key;	};
};
class Edge
{
public:
	Node* s;
	Node* d;
	int w;
	Edge(Node* sc, Node* ds, int wt=0)	{	s=sc;	d=ds;	w=wt;	};
	Edge(const Edge &e)					{	s=e.s;	d=e.d;	w=e.w;	};
};
class Graph
{
public:
	int n;
	vector<list<Node*> > Adj;
	vector<Node*> V;
	vector<Edge> E;
	Graph(int v=1)
	{
		n=v;
		for(int i=0;i<n;i++)
		{
			list<Node*> l;
			Node* v = new Node(i);
			V.push_back(v);
			Adj.push_back(l);
		};
	};
	Graph(const Graph& G)
	{
		n=G.n;
		for(int i=0;i<n;i++)
		{
			list<Node*> l;
			Adj.push_back(l);
			Node* v = new Node(*G.V[i]);
			V.push_back(v);
		};
	}
	~Graph()
	{
		for(int i=0;i<n;i++)
			delete V[i];
	}
	void addEdge(Node* v, Node* w, int wt=0)
	{
		if(v->key>=n||w->key>=n)
			return;
		Adj[v->key].push_back(w);
		Edge e(v,w,wt);
		E.push_back(e);
	}
	void printGraph(void)
	{
		cout<<"\n";
		for(int i=0;i<n;i++)
		{
			cout<<i<<" -> ";
			for(auto j:Adj[i])
				cout<<j->key<<" ";
			cout<<"\n";
		}
	}
	void Initialize(Node* s)
	{
		for(auto v:V)
		{
			v->d = INT_MAX;
			v->p = NULL;
		}
		s->d = 0;
	}
	void Relax(Edge& e)
	{
		if(e.s->d != INT_MAX)					//imp as inf + anything is not inf in C++
			if(e.d->d > (e.s->d + e.w))
			{
				e.d->d = e.s->d + e.w;
				e.d->p = e.s;
			}
	}
	bool Bellman_Ford(Node* s)
	{
		Initialize(s);
		for(int i=0;i<(V.size()-1);i++)
			for(auto e:E)
				Relax(e);
		for(auto e:E)
			if(e.d->d > (e.s->d + e.w))
				return false;
		return true;
	}
};
int main()
{
	int n,m;
	char c;
	ifstream fp("Difference Constrain input.txt");
	cout<<"Number of nodes : ";
	fp>>n;
	Graph G(n+1);

	int v1, v2, v, w;
	while(!fp.eof())
	{
		fp>>v2>>v1>>w;
		G.addEdge(G.V[v1],G.V[v2],w);
	}
	for(int i=1;i<=n;i++)
		G.addEdge(G.V[0],G.V[i],0);
	cout<<"\n";

	cout<<endl;
	Node* s = G.V[0];
	bool a = G.Bellman_Ford(s);
	if(a)
		for(int i=1;i<=n;i++)
			cout<<"x"<<i<<" = "<<G.V[i]->d<<" + d"<<endl;
	else
		cout<<"No solution!"<<endl;
	return 0;
}