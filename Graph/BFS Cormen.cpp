//CLRS page 596 graph
#include <iostream>
#include <list>
#include <vector>
#include <fstream>
#include <algorithm>
#include <climits>
#include <queue>
#define NIL -1;
enum Color {BLACK, GRAY, WHITE};
using namespace std;
class Node
{
public:
	int key;
	char data;
	int d;
	Node* p;
	Color color;
	Node(int k=0)		{	key=k;	data=0;	color=WHITE;};
	Node(int k, int d)	{	key=k;	data=d;	color=WHITE;};
	Node(const Node& v)	{	key=v.key;	data=v.data;	color=v.color;};
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
	void BFS(Node* s)
	{
		if(s->key>=n)
			return;
		for(auto v:V)
		{
			if(v!=s)
			{
				v->color = WHITE;
				v->d = INT_MAX;
			}
			v->p = NULL;
		}
		s->color = GRAY;
		s->d = 0;
		Node* u;
		queue<Node*> Q;
		Q.push(s);
		while(!Q.empty())
		{
			u = Q.front();
			Q.pop();
			for(auto v:Adj[u->key])
				if(v->color==WHITE)
				{
					v->color = GRAY;
					v->d = u->d + 1;
					v->p = u;
					Q.push(v);
				}
			u->color = BLACK;
		}
	}
};
int main()
{
	int n,m;
	char c;
	ifstream fp("BFS Cormen input.txt");
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
		fp>>v1>>v2;
		G.addEdge(G.V[v1],G.V[v2]);
	}
	cout<<"\n";

	G.BFS(G.V[1]);
	cout<<"i d p\n";
	for(auto v:G.V)
	{
		cout<<v->data<<" "<<v->d<<" ";
		if(v->p!=NULL)
			cout<<(v->p)->data;
		else
			cout<<"NULL";
		cout<<endl;
	}
	return 0;
}