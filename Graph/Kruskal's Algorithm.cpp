#include <iostream>
#include <list>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;
class Node
{
public:
	int key;
	char data;
	Node(int k=0)		{	key=k;	};
	Node(int k, char d)	{	key=k;	data=d;	};
	Node(const Node& v)	{	key=v.key;	data=v.data;	};
};
class Subset
{
public:
	int p;
	int rank;
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
	bool dir;
	vector<list<pair<Node*,int> > > Adj;
	vector<Node*> V;
	vector<Edge> E;
	Subset* subsets;
	Graph(int v=1)
	{
		n=v;
		for(int i=0;i<n;i++)
		{
			list<pair<Node*,int> > l;
			Node* v = new Node(i);
			V.push_back(v);
			Adj.push_back(l);
		};
		subsets = new Subset[n];
		for(int i=0;i<n;i++)
		{
			subsets[i].rank=0;
			subsets[i].p=i;
		}
	};
	Graph(const Graph& G)
	{
		n=G.n;
		dir=G.dir;
		for(int i=0;i<n;i++)
		{
			list<pair<Node*,int> > l;
			Adj.push_back(l);
			Node* v = new Node(*G.V[i]);
			V.push_back(v);
		};
	}
	~Graph()
	{
		for(int i=0;i<n;i++)
			delete V[i];
		delete [] subsets;
	}
	void addEdge(Node* v, Node* w, int wt=0)
	{
		if(v->key>=n||w->key>=n)
			return;
		Adj[v->key].push_back(make_pair(w,wt));
		if(!dir)
			Adj[w->key].push_back(make_pair(v,wt));
	}
	vector<Edge> CreateEdgeList()
	{
		for(int i=0;i<n;i++)
			for(auto j:Adj[i])
			{
				Edge e(V[i],j.first,j.second);
				E.push_back(e);
			}
		return E;
	}
	void printGraph(void)
	{
		cout<<"\n";
		for(int i=0;i<n;i++)
		{
			cout<<i<<" -> ";
			for(auto j:Adj[i])
				cout<<(j.first)->key<<" ";
			cout<<"\n";
		}
	}
	int Find(int i)
	{
		if(subsets[i].p!=i)
			subsets[i].p=Find(subsets[i].p);
		return subsets[i].p;
	}
	void Union(int x, int y)
	{
		int xroot = Find(x);
		int yroot = Find(y);
		if(subsets[xroot].rank < subsets[yroot].rank)
			subsets[xroot].p = yroot;
		else if(subsets[xroot].rank > subsets[yroot].rank)
			subsets[yroot].p = xroot;
		else
		{
			subsets[xroot].p = yroot;
			subsets[yroot].rank++;
		}
	}
	vector<Edge>* Kruskal(void)
	{
		vector<Edge>* MST = new vector<Edge>;
		vector<Edge> EdgeList = CreateEdgeList();
		sort(EdgeList.begin(), EdgeList.end(), [](Edge e1, Edge e2){ return (e1.w < e2.w); });
		for(auto e:EdgeList)
			if(Find(e.s->key)!=Find(e.d->key))
			{
				MST->push_back(e);
				Union(e.s->key,e.d->key);
			}
		return MST;
	}
};
int main()
{
	int n,m;
	char c;
	ifstream fp("Kruskal's Algorithm input.txt");
	cout<<"Number of nodes : ";
	fp>>n;
	Graph G(n);
	cout<<"Directed Graph? (Y/N) : ";
	fp>>c;
	G.dir=(c=='y'||c=='Y')?true:false;

	//to add data
	for(int i=0;i<n;i++)
		fp>>(G.V[i]->data);

	int v1, v2, v, w;
	while(!fp.eof())
	{
		fp>>v1>>v2>>w;
		G.addEdge(G.V[v1],G.V[v2],w);
	}
	cout<<"\n";
	G.printGraph();
	vector<Edge>* MST = G.Kruskal();
	cout<<endl;
	for(auto e:(*MST))
		cout<<e.s->data<<" "<<e.d->data<<" "<<e.w<<endl;
	delete MST;
	return 0;
}