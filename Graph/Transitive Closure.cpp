#include <iostream>
#include <list>
#include <vector>
#include <fstream>
#include <algorithm>
#define NIL -1
#define INF 2147483647
using namespace std;
class Node
{
public:
	int key;
	int data;
	Node(int k=0)		{	key=k;	data=0;	};
	Node(int k, int d)	{	key=k;	data=d;	};
	Node(const Node& v)	{	key=v.key;	data=v.data;	};
};
class Graph
{
public:
	int n;
	bool dir;
	vector<Node*> V;
	bool** T;
	Graph(int v=1)
	{
		n=v;
		T = new bool* [n];
		for(int i=0;i<n;i++)
		{
			Node* v = new Node(i);
			V.push_back(v);
			T[i] = new bool [n];
			for(int j=0;j<n;j++)
				T[i][j] = (i==j)?true:false;
		};
	};
	Graph(const Graph& G)
	{
		n=G.n;
		dir=G.dir;
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;i++)
				T[i][j] = G.T[i][j];
			Node* v = new Node(*G.V[i]);
			V.push_back(v);
		}
	}
	~Graph()
	{
		for(int i=0;i<n;i++)
		{	
			delete [] T[i];
			delete V[i];
		}
		delete T;
	}
	void addEdge(Node* v, Node* w)
	{
		if(v->key>=n||w->key>=n)
			return;
		T[v->key][w->key] = true;
		if(!dir)
			T[w->key][v->key] = true;
	}
	void printGraph(void)
	{
		cout<<"\n";
		for(int i=0;i<n;i++)
		{
			cout<<i<<" -> ";
			for(int j=0;j<n;j++)
				if(T[i][j]==true && i!=j)
					cout<<j<<" ";
			cout<<"\n";
		}
		cout<<endl;
	}
	void Transitive_Closure(void)
	{
		bool P[n][n];
		for(int k=0;k<n;k++)
		{
			for(int i=0;i<n;i++)
				for(int j=0;j<n;j++)
					P[i][j] = T[i][j]||(T[i][k]&&T[k][j]);
			for(int i=0;i<n;i++)
				for(int j=0;j<n;j++)
					T[i][j]=P[i][j];
		}
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

	int v1, v2, v;
	while(!fp.eof())
	{
		fp>>v1>>v2;
		G.addEdge(G.V[v1],G.V[v2]);
	}
	cout<<"\n";

	G.printGraph();

	G.Transitive_Closure();
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			cout<<G.T[i][j]<<" \n"[j==n-1];
	return 0;
}