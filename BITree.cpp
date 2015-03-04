#include <iostream>
void update(int bit[],int i,int x,int n);
int sum(int bit[],int i);
using namespace std;
int main()
{
	cout<<"Number of elements : ";
	int n,i,j;
	cin>>n;
	int a[n+1],bit[n+1];
	for(int i=1;i<=n;i++)
		bit[i]=0;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		update(bit,i,a[i],n+1);
	}
	//for(int i=1;i<n+1;i++)
	//	cout<<bit[i]<<" ";
	cout<<endl;
	cout<<"Sum between index [i j] : ";
	cin>>i>>j;
	cout<<"Sum between index "<<i<<" and "<<j<<" is : "<<sum(bit,j)-sum(bit,i-1);
	return 0;
}
void update(int bit[],int i,int x,int n)
{
	while(i<=n)
	{
		bit[i]+=x;
		i+=(i&(-i));
	}
}
int sum(int bit[],int i)
{
	int ans=0;
	while(i)
	{
		ans+=bit[i];
		i-=(i&(-i));
	}
	return ans;
}