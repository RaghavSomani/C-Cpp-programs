#include<iostream>
using namespace std;
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
	int a[m][n],b[n][p],c[m][p];
	cout<<"Matrix A :\n";
	for(i=0;i<m;++i)
		for(j=0;j<n;++j)
			cin>>a[i][j];
	cout<<"Matrix B :\n";
	for(i=0;i<n;++i)
		for(j=0;j<p;++j)
			cin>>b[i][j];	
	for(i=0;i<m;++i)
		for(j=0;j<p;++j)
		{
			c[i][j]=0;
			for(k=0;k<n;++k)
				c[i][j]+=a[i][k]*b[k][j];
		}
	cout<<"Matrix AB :\n";
	for(i=0;i<m;++i)
	{
		for(j=0;j<p;++j)
			cout<<c[i][j]<<" ";
		cout<<endl;
	}
	return 0;
}
