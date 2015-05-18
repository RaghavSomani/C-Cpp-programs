//CLRS page 613
#include <iostream>
#include <list>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#define NIL -1;
enum Color {BLACK, GRAY, WHITE};
using namespace std;
class Node
{
public:
	int key;
	string data;
	Color color;
	int d;
	int f;
	Node* p;
	Node(int k=0)		{	key=k;	data="";	};
	Node(int k, string d)	{	key=k;	data=d;	};
	Node(const Node& v)	{	key=v.key;	data=v.data;	};
};
class Edge
{
public:
	Node* s;
	Node* d;
	Edge(Node* sc, Node* ds)	{	s=sc;	d=ds;	};
	Edge(const Edge &e)			{	s=e.s;	d=e.d;	};
};
class Graph
{
public:
	int n;
	bool dir;
	int time;
	vector<list<Node*> > Adj;
	vector<Node*> V;
	vector<Edge> E;
	list<Node*> TopoSort;
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
	Graph(const Graph &G)
	{
		n=G.n;
		dir=G.dir;
		for(int i=0;i<n;i++)
		{
			list<Node*> l;
			Adj.push_back(l);
			V.push_back(G.V[i]);
		};
	}
	~Graph()
	{
		for(int i=0;i<n;i++)
			delete V[i];
	}
	void addEdge(Node* v, Node* w)
	{
		if(v->key>=n||w->key>=n)
			return;
		Adj[v->key].push_back(w);
		if(!dir)
			Adj[w->key].push_back(v);
	}
	//DFS to return Topological Sorted order
	list<Node*> TS_DFS(void)
	{
		for(auto v:V)
		{
			v->color=WHITE;
			v->p=NULL;
		}
		time=0;
		for(auto u:V)
			if(u->color==WHITE)
				TS_DFS_Visit(u);
		return TopoSort;
	}
	void TS_DFS_Visit(Node* u)
	{
		u->d=++time;
		u->color=GRAY;
		for(auto v:Adj[u->key])
			if(v->color==WHITE)
			{
				v->p=u;
				TS_DFS_Visit(v);
			}
		u->color=BLACK;
		u->f=++time;
		TopoSort.push_front(u);
	}
};
int main()
{
	int n,m;
	char c;
	ifstream fp("Topological Sort input.txt");
	cout<<"Number of nodes : ";
	fp>>n;
	Graph G(n);
	cout<<"Directed Graph? (Y/N) : ";
	fp>>c;
	G.dir=(c=='y'||c=='Y')?true:false;

	//to add data
	for(int i=0;i<n;i++)
		fp>>(G.V[i]->data);

	int v1, v2, v;
	while(!fp.eof())
	{
		fp>>v1>>v2;
		G.addEdge(G.V[v1],G.V[v2]);
	}
	cout<<"\n";

	list<Node*> TS = G.TS_DFS();
	for(auto v:TS)
		cout<<v->data<<" "<<v->f<<endl;
	cout<<endl;
	return 0;
}