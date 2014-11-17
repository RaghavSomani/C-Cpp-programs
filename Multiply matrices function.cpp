#include<iostream>
using namespace std;
void multiply(int a[10][10], int b[10][10], int c[10][10], int m, int n, int p)
{
	for(int i=0;i<m;++i)
		for(int j=0;j<p;++j)
			for(int k=0;k<n;++k)
				c[i][j]+=a[i][k]*b[k][j];
}
int main()
{
	int m,n,p,i,j,k;
	cout<<"Multiply m x n matrix with n x p matrix\n";
	cout<<"Enter m : ";
	cin>>m;
	cout<<"Enter n : ";
	cin>>n;
	cout<<"Enter p : ";
	cin>>p;
	int a[10][10],b[10][10],c[10][10]={{}};
	cout<<"Matrix A :\n";
	for(i=0;i<m;++i)
		for(j=0;j<n;++j)
			cin>>a[i][j];
	cout<<"Matrix B :\n";
	for(i=0;i<n;++i)
		for(j=0;j<p;++j)
			cin>>b[i][j];
	multiply(a,b,c,m,n,p);
	cout<<"Matrix AB :\n";
	for(i=0;i<m;++i)
	{
		for(j=0;j<p;++j)
			cout<<c[i][j]<<" ";
		cout<<endl;
	}
	return 0;
}
