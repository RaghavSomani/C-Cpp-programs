#include<iostream>
using namespace std;
int main()
{
	int n,k;
	cin>>n>>k;
	int a[n],b[k];
	for(int i=0;i<k;i++)
		b[i]=0;
	b[0]=1;
	cin>>a[0];
	a[0]=a[0]%k;
	b[a[0]]++;
	for(int i=1;i<n;i++)
	{
		cin>>a[i];
		a[i]=a[i]%k;
		a[i]=(a[i]+a[i-1]+k)%k;
		b[a[i]]++;
	}
	int ans=0;
	for(int i=0;i<k;i++)
		ans+=(b[i]*(b[i]-1))/2;
	cout<<ans;
}
