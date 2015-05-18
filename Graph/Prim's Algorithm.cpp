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
	Node* p;
	int d;
	int pos;
	Node(int k=0)		{	key=k;	pos=k;	};
	Node(int k, char d)	{	key=k;	data=d;	pos=k;	};
	Node(const Node& v)	{	key=v.key;	data=v.data;	};
};

class Priority_Queue
{
public:
	vector<Node*> V;
	int n;
	void build_min_heap(void)
	{
		n = V.size();
		for(int i=(n-2)/2;i>=0;i--)
			min_heapify(i);
		for(int i=0;i<n;i++)
			V[i]->pos=i;
	};
	void min_heapify(int i)
	{
		n = V.size();
		int l, r, smallest;
		while(1)
		{
			l=(2*i)+1;
			r=(2*i)+2;
			if(l<n && (V[l]->d < V[i]->d))
				smallest=l;
			else
				smallest=i;
			if(r<n && (V[r]->d < V[smallest]->d))
				smallest=r;
			if(smallest==i)
				break;
			swap(V[smallest],V[i]);
			V[smallest]->pos=smallest;
			V[i]->pos=i;
			i=smallest;
		}
	};
	void decrease_key(int i, int k)
	{
		V[i]->d=k;
		while(i>0 && (V[(i-1)/2]->d > V[i]->d))
		{
			swap(V[i],V[(i-1)/2]);
			V[i]->pos=i;
			V[(i-1)/2]->pos=(i-1)/2;
			i=(i-1)/2;
		}
	}
	Node* extract_min(void)
	{
		Node* min=V[0];
		V[0]=V[V.size()-1];
		V[0]->pos=0;
		V.pop_back();
		min_heapify(0);
		n=V.size();
		return min;
	}
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
				cout<<(j.first)->key<<" ";
			cout<<"\n";
		}
	}
	void Prim(int r)
	{
		for(auto v:V)
		{
			v->d = INT_MAX;
			v->p = NULL;
		}
		V[r]->d = 0;

		Priority_Queue Q;
		Q.V.resize(n);
		for(int i=0;i<n;i++)
			Q.V[i]=V[i];
		Q.build_min_heap();
		bool A[n];
		for(int i=0;i<n;i++)
			A[i]=true;
		
		Node* u;
		while(!Q.V.empty())
		{
			u = Q.extract_min();
			A[u->key]=false;
			for(auto v:Adj[u->key])
				if(A[v.first->key] && (v.second < v.first->d))
				{
					v.first->p = u;
					Q.decrease_key(v.first->pos,v.second);
				}
		}
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
	G.Prim(0);
	cout<<endl;

	for(auto v:G.V)
		if(v->p != NULL)
			cout<<v->data<<" "<<v->p->data<<endl;

	return 0;
}