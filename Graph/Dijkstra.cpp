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
	int dist;
	int pos;
	Node* p;
	Node(int k=0)		{	key=k;	};
	Node(int k, char d)	{	key=k;	data=d;	};
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
			if(l<n && (V[l]->dist < V[i]->dist))
				smallest=l;
			else
				smallest=i;
			if(r<n && (V[r]->dist < V[smallest]->dist))
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
		V[i]->dist=k;
		while(i>0 && (V[(i-1)/2]->dist > V[i]->dist))
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
	void Initialize(Node* s)
	{
		for(auto v:V)
		{
			v->dist = INT_MAX;
			v->p = NULL;
		}
		s->dist = 0;
	}
	void Relax(Priority_Queue& Q, Node* u, Node* v, int w)
	{
		if(u->dist != INT_MAX)
			if(v->dist > (u->dist + w))
			{
				Q.decrease_key(v->pos,(u->dist + w));
				v->p = u;
			}
	}
	void Dijkstra(Node* s)
	{
		Node* u;
		Initialize(s);
		Priority_Queue Q;
		Q.V.resize(n);
		for(int i=0;i<n;i++)
			Q.V[i]=V[i];
		Q.build_min_heap();
		while(!Q.V.empty())
		{
			u = Q.extract_min();
			for(auto v:Adj[u->key])
				Relax(Q,u,v.first,v.second);
		}
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
	ifstream fp("Dijkstra input.txt");
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
	G.Dijkstra(s);
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