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
	int** W;
	int** D;
	int** P;
	Graph(int v=1)
	{
		n=v;
		W = new int* [n];
		D = new int* [n];
		P = new int* [n];
		for(int i=0;i<n;i++)
		{
			Node* v = new Node(i);
			V.push_back(v);
			W[i] = new int [n];
			D[i] = new int [n];
			P[i] = new int [n];
			for(int j=0;j<n;j++)
			{
				D[i][j] = (i==j)?0:INF;
				W[i][j] = D[i][j];
				P[i][j] = (i==j)?NIL:i;
			};
		};
	};
	Graph(const Graph& G)
	{
		n=G.n;
		dir=G.dir;
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;i++)
			{
				W[i][j] = G.W[i][j];
				D[i][j] = G.D[i][j];
				P[i][j] = G.P[i][j];
			}
			Node* v = new Node(*G.V[i]);
			V.push_back(v);
		}
	}
	~Graph()
	{
		for(int i=0;i<n;i++)
		{
			delete [] W[i];
			delete [] D[i];
			delete [] P[i];
			delete V[i];
		}
		delete W;
		delete D;
		delete P;
	}
	void addEdge(Node* v, Node* w, int wt=0)
	{
		if(v->key>=n||w->key>=n)
			return;
		W[v->key][w->key] = wt;
		D[v->key][w->key] = W[v->key][w->key];
		P[v->key][w->key] = v->key;
		if(!dir)
		{
			D[w->key][v->key] = wt;
			W[w->key][v->key] = D[w->key][v->key];
			P[w->key][v->key] = w->key;
		}
	}
	void printGraph(void)
	{
		cout<<"\n";
		for(int i=0;i<n;i++)
		{
			cout<<i<<" -> ";
			for(int j=0;j<n;j++)
				if(W[i][j]!=0&&W[i][j]!=INF)
					cout<<j<<" ";
			cout<<"\n";
		}
		cout<<endl;
	}
	void Floyd_Warshall(void)
	{
		int T[n][n], Q[n][n];
		for(int k=0;k<n;k++)
		{
			for(int i=0;i<n;i++)
				for(int j=0;j<n;j++)
					if(D[i][k]!=INF&&D[k][j]!=INF)
					{
						if(D[i][j] <= D[i][k]+D[k][j])
						{
							T[i][j] = D[i][j];
							Q[i][j] = P[i][j];
						}
						else
						{
							T[i][j] = D[i][k]+D[k][j];
							Q[i][j] = P[k][j];
						}
					}
					else
					{
						T[i][j]=D[i][j];
						Q[i][j]=P[i][j];
					}
			for(int i=0;i<n;i++)
				for(int j=0;j<n;j++)
				{
					D[i][j]=T[i][j];
					P[i][j]=Q[i][j];
				}
		}
	}
	void Print_Shortest_Path(int i,int j)
	{
		if(i==j)
			cout<<V[i]->data<<" ";
		else if(P[i][j]==NIL)
			cout<<"No path from "<<V[i]->data<<" to "<<V[j]->data<<"exists.\n";
		else
		{
			Print_Shortest_Path(i,P[i][j]);
			cout<<V[j]->data<<" ";
		}
	}
};
int main()
{
	int n,m;
	char c;
	ifstream fp("Floyd Warshall input.txt");
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

	G.Floyd_Warshall();
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			cout<<G.D[i][j]<<" \n"[j==n-1];
	cout<<endl;
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			cout<<G.P[i][j]<<" \n"[j==n-1];

	cout<<"From Vertex ID : ";
	cin>>v1;
	cout<<"To Vertex ID : ";
	cin>>v2;
	cout<<"Path : ";
	G.Print_Shortest_Path(v1,v2);
	cout<<endl;
	cout<<"Path weight : "<<G.D[v1][v2]<<endl;
	return 0;
}