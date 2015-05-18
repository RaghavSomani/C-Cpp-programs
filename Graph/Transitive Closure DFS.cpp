#include <iostream>
#include <list>
#include <vector>
#include <fstream>
#include <algorithm>
#define NIL -1;
enum Color {BLACK, GRAY, WHITE};
using namespace std;
class Node
{
public:
	int key;
	char data;
	Color color;
	int d;
	int f;
	Node* p;
	Node(int k=0)		{	key=k;	data=0;	color=WHITE;};
	Node(int k, int d)	{	key=k;	data=d;	color=WHITE;};
	Node(const Node& v)	{	key=v.key;	data=v.data;	color=v.color;};
};
class Graph
{
public:
	int n;
	bool dir;
	int time;
	vector<list<Node*> > Adj;
	vector<Node*> V;
	bool** TC;
	Graph(int v=1)
	{
		n=v;
		TC = new bool* [n];
		for(int i=0;i<n;i++)
		{
			list<Node*> l;
			Node* v = new Node(i);
			V.push_back(v);
			Adj.push_back(l);
			TC[i] = new bool [n];
			for(int j=0;j<n;j++)
				TC[i][j]=(i==j)?true:false;
		};
	};
	Graph(const Graph &G)
	{
		n=G.n;
		dir=G.dir;
		TC = new bool* [n];
		for(int i=0;i<n;i++)
		{
			list<Node*> l;
			Adj.push_back(l);
			V.push_back(G.V[i]);
			TC[i] = new bool [n];
			for(int j=0;j<n;j++)
				TC[i][j]=G.TC[i][j];
		};
	}
	~Graph()
	{
		for(int i=0;i<n;i++)
		{
			delete V[i];
			delete [] TC[i];
		}
		delete TC;
	}
	void addEdge(Node* v, Node* w)
	{
		if(v->key>=n||w->key>=n)
			return;
		Adj[v->key].push_back(w);
		TC[v->key][w->key]=true;
		if(!dir)
		{
			Adj[w->key].push_back(v);
			TC[w->key][v->key]=true;
		}
	}
	void DFS(Node* u)
	{
		for(auto v:V)
		{
			v->color=WHITE;
			v->p=NULL;
			v->d=-1;
			v->f=-1;
		}
		time=0;
		if(u->color==WHITE)
			DFS_Visit(u);
		for(auto v:V)
			if(v->d!=-1)
				TC[u->key][v->key]=true;
	}
	void DFS_Visit(Node* u)
	{
		u->d=++time;
		u->color=GRAY;
		for(auto v:Adj[u->key])
			if(v->color==WHITE)
			{
				v->p=u;
				DFS_Visit(v);
			}
		u->color=BLACK;
		u->f=++time;
	}
	void Transitive_Closure(void)
	{
		for(auto v:V)
			DFS(v);
	}
};
int main()
{
	int n,m;
	char c;
	ifstream fp("Transitive Closure input.txt");
	cout<<"Number of nodes : ";
	fp>>n;
	Graph G(n);
	cout<<"Directed Graph? (Y/N) : ";
	fp>>c;
	G.dir=(c=='y'||c=='Y')?true:false;

	int v1, v2;
	while(!fp.eof())
	{
		fp>>v1>>v2;
		G.addEdge(G.V[v1],G.V[v2]);
	}
	cout<<"\n";
	G.Transitive_Closure();

	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			cout<<G.TC[i][j]<<" \n"[j==n-1];
	return 0;
}