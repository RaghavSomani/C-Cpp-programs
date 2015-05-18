#include <iostream>
#include <list>
#include <vector>
#include <fstream>
#include <algorithm>
#include <climits>
using namespace std;
enum Color {BLACK, GRAY, WHITE};
class Node
{
public:
	int key;
	char data;
	Color color;
	int dist;
	int d;
	int f;
	Node* p;
	Node(int k=0)		{	key=k;	};
	Node(int k, char d)	{	key=k;	data=d;	};
	Node(const Node& v)	{	key=v.key;	data=v.data;	};
};
class Graph
{
public:
	int n;
	bool dir;
	int time;
	vector<list<pair<Node*,int> > > Adj;
	vector<Node*> V;
	list<Node*> TopoSort;
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
	}
	void addEdge(Node* v, Node* w, int wt=0)
	{
		if(v->key>=n||w->key>=n)
			return;
		Adj[v->key].push_back(make_pair(w,wt));
		if(!dir)
			Adj[w->key].push_back(make_pair(v,wt));
	}
	void printGraph(void)
	{
		cout<<"\n";
		for(int i=0;i<n;i++)
		{
			cout<<i<<" -> ";
			for(auto j:Adj[i])
				cout<<j.first->key<<" ";
			cout<<"\n";
		}
	}
	void TS_DFS(void)
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
	}
	void TS_DFS_Visit(Node* u)
	{
		u->d=++time;
		u->color=GRAY;
		for(auto v:Adj[u->key])
			if(v.first->color==WHITE)
			{
				v.first->p=u;
				TS_DFS_Visit(v.first);
			}
		u->color=BLACK;
		u->f=++time;
		TopoSort.push_front(u);
	}
	void Initialize(Node* s)
	{
		for(auto v:V)
		{
			v->dist = INT_MAX;
			v->p = NULL;
		}
		s->dist = 0;
	}
	void Relax(Node* u, Node* v, int w)
	{
		if(u->dist != INT_MAX)					//imp as inf + anything is not inf in C++
			if(v->dist > (u->dist + w))
			{
				v->dist = u->dist + w;
				v->p = u;
			}
	}
	void DAG_Shortest_Path(Node* s)
	{
		TS_DFS();
		Initialize(s);
		for(auto u:TopoSort)
			for(auto v:Adj[u->key])
				Relax(u,v.first,v.second);
	}
	void Print_Path(Node* s, Node* v)
	{
		if(v!=s && v->p!=NULL)
		{
			Print_Path(s,v->p);
			cout<<v->data<<" ";
		}
		else if(v->dist!=INT_MAX)
			cout<<v->data<<" ";
	}
};
int main()
{
	int n,m;
	char c;
	ifstream fp("DAG shortest path input.txt");
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
	Node* s = G.V[1];
	G.DAG_Shortest_Path(s);
	for(auto v:G.V)
	{
		cout<<v->data<<" ";
		if(v->dist!=INT_MAX)
			cout<<v->dist;
		else
			cout<<"Not Reachable";
		cout<<endl;
	}
	cout<<endl;
	for(auto v:G.V)
	{
		cout<<v->data<<" -> ";
		G.Print_Path(s,v);
		cout<<endl;
	}
	return 0;
}