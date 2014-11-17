#include<iostream>
using namespace std;
int comb(int n, int r)
{
	int a[n+1][r+1];
	for(int i=0;i<=n;i++)
	{
		for(int j=0;j<=r;j++)
		{
			if(j>i)
				a[i][j]=0;
			else if(j==0||i==j)
				a[i][j]=1;
			else
				a[i][j]=a[i-1][j]+a[i-1][j-1];
		}
	}
	return a[n][r];
}
int main()
{
	int n,r;
	cin>>n>>r;
	if(n<0||r<0)
		return 0;
	if(n==r||r==0)
		cout<<1;
	else if(n>r)
	{
		if(r<n/2)
			cout<<comb(n,r);
		else
			cout<<comb(n,n-r);
	}
}
