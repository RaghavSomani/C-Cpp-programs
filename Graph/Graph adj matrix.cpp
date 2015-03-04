#include <iostream>
using namespace std;
class Graph
{
public:
	int n;
	int** A;
	Graph(int n=1)
	{
		A=new int* [n];
		for(int i=0;i<n;i++)
			A[i]=new int [n];
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				A[i][j]=0;
	};
	~Graph()
	{
		for(int i=0;i<n;i++)
			delete [] A[i];
		delete [] A;
	}
};
int main()
{
	int n,m;
	cout<<"Number of nodes : ";
	cin>>n;
	Graph G(n);
	cout<<"Number of edges : ";
	cin>>m;
	int v1,v2,v;
	for(int i=0;i<m;i++)
	{
		cin>>v1>>v2;
		G.A[v1][v2]=1;
		G.A[v2][v1]=1;
	}
	cout<<"Find neighbours of : ";
	cin>>v;
	for(int i=0;i<n;i++)
		if(G.A[v][i]==1)
			cout<<i<<" ";
	cout<<endl;
	return 0;
}