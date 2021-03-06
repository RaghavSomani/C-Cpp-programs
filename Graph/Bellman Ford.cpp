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
	char data;
	int d;
	Node* p;
	Node(int k=0)		{	key=k;	};
	Node(int k, char d)	{	key=k;	data=d;	};
	Node(const Node& v)	{	key=v.key;	data=v.data;	};
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
	void addEdge(Node* v, Node* w, int wt=0)
	{
		if(v->key>=n||w->key>=n)
			return;
		Adj[v->key].push_back(w);
		Edge e(v,w,wt);
		E.push_back(e);
		if(!dir)
		{
			Adj[w->key].push_back(v);
			Edge e(w,v,wt);
			E.push_back(e);
		}
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
	void Print_Path(Node* s, Node* v)
	{
		if(v!=s && v->p!=NULL)
		{
			Print_Path(s,v->p);
			cout<<v->data<<" ";
		}
		else if(v->d!=INT_MAX)
			cout<<v->data<<" ";
	}
};
int main()
{
	int n,m;
	char c;
	ifstream fp("Bellman Ford input.txt");
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
	cout<<endl;
	Node* s = G.V[0];
	bool a = G.Bellman_Ford(s);
	if(a)
	{
		for(auto v:G.V)
			cout<<v->data<<" "<<v->d<<endl;
		cout<<endl;
		for(auto v:G.V)
		{
			cout<<v->data<<" -> ";
			G.Print_Path(s,v);
			cout<<endl;
		}
	}
	return 0;
}