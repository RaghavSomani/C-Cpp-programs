#include <iostream>
#include <list>
#include <vector>
#include <fstream>
#include <algorithm>
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
	Node(int k=0)		{	key=k;	color=WHITE;	};
	Node(int k, char d)	{	key=k;	data=d;	color=WHITE;	};
	Node(const Node& v)	{	key=v.key;	data=v.data;	color=v.color;	};
};
class Graph
{
public:
	int n;
	bool dir;
	int time;
	vector<list<Node*> > Adj;
	vector<Node*> V;
	list<int> TopoSort;
	vector<list<Node*> > SCC;
	Graph(int v=1)
	{
		n=v;
		dir=false;
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
		dir=G.dir;
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
	void addEdge(Node* v, Node* w)
	{
		if(v->key>=n||w->key>=n)
			return;
		Adj[v->key].push_back(w);
		if(!dir)
			Adj[w->key].push_back(v);
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
	Graph* Transpose(void)
	{
		Graph* T = new Graph(*this);
		for(int i=0;i<n;i++)
			for(auto j:Adj[i])
				T->Adj[j->key].push_back(T->V[i]);
		return T;
	}
	list<int> TS_DFS(void)
	{
		for(auto v:V)
			v->color=WHITE;
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
				TS_DFS_Visit(v);
		u->color=BLACK;
		u->f=++time;
		TopoSort.push_front(u->key);
	}
	//DFS in a Topological Sorted order
	void SCC_DFS(list<int> TS)
	{
		for(auto v:V)
			v->color=WHITE;
		time=0;
		for(auto i:TS)
			if(V[i]->color==WHITE)
			{
				list<Node*> l;
				l.push_back(V[i]);
				SCC.push_back(l);
				SCC_DFS_Visit(V[i]);
			}
	}
	void SCC_DFS_Visit(Node* u)
	{
		u->d=++time;
		u->color=GRAY;
		for(auto v:Adj[u->key])
			if(v->color==WHITE)
			{
				SCC[SCC.size()-1].push_back(v);
				SCC_DFS_Visit(v);
			}
		u->color=BLACK;
		u->f=++time;
	}
	Graph* SCComponents(void)
	{
		list<int> TS = TS_DFS();
		Graph* T = Transpose();
		T->SCC_DFS(TS);
		return T;
	}
};
int main()
{
	int n,m;
	char c;
	ifstream fp("Strongly Connected input.txt");
	cout<<"Number of nodes : ";
	fp>>n;
	Graph G(n);
	cout<<"Directed Graph? (Y/N) : ";
	fp>>c;
	G.dir=(c=='y'||c=='Y')?true:false;
	//to add data
	for(int i=0;i<n;i++)
		fp>>(G.V[i]->data);
	int v1, v2;
	while(!fp.eof())
	{
		fp>>v1>>v2;
		G.addEdge(G.V[v1],G.V[v2]);
	}
	cout<<"\n";
	Graph* T = G.SCComponents();
	vector<list<Node*> > S = T->SCC;
	cout<<endl;
	for(auto i:S)
	{
		for(auto v:i)
			cout<<v->data<<" ";
		cout<<endl;
	}
	delete T;
	return 0;
}