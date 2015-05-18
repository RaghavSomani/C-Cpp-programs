//CLRS pg 648
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
	Node(int k=0)		{	key=k;	};
	Node(int k, int d)	{	key=k;	data=d;	};
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
	vector<list<pair<Node*,int> > > Adj;
	vector<Node*> V;
	vector<Edge> E;
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
	};
	Graph(const Graph &G)
	{
		n=G.n;
		dir=G.dir;
		for(int i=0;i<n;i++)
		{
			list<pair<Node*,int>> l;
			Adj.push_back(l);
			V.push_back(G.V[i]);
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
	bool isEdgePresent(int v, int w)
	{
		if(v>=n||w>=n)
			return false;
		return (find_if(Adj[v].begin(),Adj[v].end(),[&](pair<Node*,int> x){return (x.first)->key==w;})!=Adj[v].end());
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
	Graph* Transpose(void)
	{
		Graph* T = new Graph(*this);
		for(int i=0;i<n;i++)
			for(auto j:Adj[i])
				T->Adj[(j.first)->key].push_back(make_pair(T->V[i],j.second));
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
	ifstream fp("Graph Class input.txt");
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

	cout<<"Find neighbours of : ";
	cin>>v;
	for(auto i:G.Adj[v])
			cout<<(i.first)->key<<" ";

	cout<<"\nSearch for edge : ";
	cin>>v1>>v2;
	G.isEdgePresent(v1,v2)?cout<<"Edge present":cout<<"Edge not present";
	
	Graph* T=G.Transpose();
	T->printGraph();

	cout<<"Get degree of : ";
	cin>>v1;
	cout<<"Outdegree : "<<G.degree(v1)<<" Indegree : "<<T->degree(v1)<<endl;

	cout<<"Edge List\n";
	vector<Edge> E = G.CreateEdgeList();
	for(auto i:E)
		cout<<i.s->key<<" "<<i.d->key<<" "<<i.w<<endl;
	delete T;
	return 0;
}