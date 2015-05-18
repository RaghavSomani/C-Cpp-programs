#include <iostream>
#include <list>
#include <vector>
#include <fstream>
#include <algorithm>
#define INF 2147483647
using namespace std;
template <class T>
class Matrix
{
public:
	int n;
	T** A;
	Matrix(int n=1)
	{
		this->n=n;
		A = new T* [n];
		for(int i=0;i<n;i++)
			A[i] = new T [n];
	};
	Matrix(const Matrix& B)
	{
		if(this!=&B)
		{
			n = B.n;
			A = new T* [n];
			for(int i=0;i<n;i++)
				A[i] = new T [n];
			for(int i=0;i<n;++i)
				for(int j=0;j<n;j++)
					A[i][j]=B.A[i][j];
		}
	}
	Matrix& operator = (const Matrix& P)
	{
		if(this!=&P)
		{
			for(int i=0;i<n;i++)
				delete [] A[i];
			delete [] A;
			n=P.n;
			A = new int* [n];
			for(int i=0;i<n;++i)
				A[i]=new int [n];
			for(int i=0;i<n;++i)
				for(int j=0;j<n;j++)
					A[i][j]=P.A[i][j];
		}
		return *this;
	}
	~Matrix()
	{
		for(int i=0;i<n;i++)
			delete [] A[i];
		delete [] A;
	}
	void Muliply(Matrix& P, Matrix& Q)
	{
		if(P.n==Q.n)
		{
			T** X=P.A;
			T** Y=Q.A;
			T** Z=A;
			for(int i=0;i<n;i++)
				for(int j=0;j<n;j++)
				{
					Z[i][j] = INF;
					for(int k=0;k<P.n;k++)
						if(X[i][k]!=INF&&Y[k][j]!=INF)
							if(Z[i][j] > X[i][k]+Y[k][j])
								Z[i][j] = X[i][k]+Y[k][j];
				}
		}
	}
};

class Node
{
public:
	int key;
	int data;
	Node(int k=0)		{	key=k;	data=0;	};
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
	vector<Node*> V;
	Matrix<int>* W;
	Graph(int v=1)
	{
		n=v;
		W = new Matrix<int>(n);
		for(int i=0;i<n;i++)
		{
			Node* v = new Node(i);
			V.push_back(v);
			for(int j=0;j<n;j++)
				W->A[i][j] = (i==j)?0:INF;
		};
	};
	Graph(const Graph& G)
	{
		n=G.n;
		dir=G.dir;
		for(int i=0;i<n;i++)
		{
			Node* v = new Node(*G.V[i]);
			V.push_back(v);
			for(int j=0;j<n;j++)
				W->A[i][j] = G.W->A[i][j];
		}
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
		W->A[v->key][w->key]=wt;
		if(!dir)
			W->A[w->key][v->key]=wt;
	}
	void printGraph(void)
	{
		cout<<"\n";
		for(int i=0;i<n;i++)
		{
			cout<<i<<" -> ";
			for(int j=0;j<n;j++)
				if(W->A[i][j]!=0&&W->A[i][j]!=INF)
					cout<<j<<" ";
			cout<<"\n";
		}
	}
	Matrix<int>* All_Pair_Matrix(void)
	{
		int m=1;
		Matrix<int>* L = new Matrix<int>(*W);
		while(m<n-1)
		{
			Matrix<int> T(n);
			T.Muliply(*L,*L);
			*L=T;
			m=m<<1;
		}
		return L;
	}
};
int main()
{
	int n,m;
	char c;
	ifstream fp("All pair shortest path input.txt");
	cout<<"Number of nodes : ";
	fp>>n;
	Graph G(n);
	cout<<"Directed Graph? (Y/N) : ";
	fp>>c;
	G.dir=(c=='y'||c=='Y')?true:false;

	// to add data
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
	Matrix<int>* L = G.All_Pair_Matrix();
	cout<<endl;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
			cout<<L->A[i][j]<<" ";
		cout<<endl;
	}
	cout<<endl;
	delete L;
	return 0;
}