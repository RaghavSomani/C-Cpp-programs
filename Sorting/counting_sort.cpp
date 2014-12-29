#include<iostream>
void count_sort(int a[],int p,int q);
using namespace std;
int main()
{
	int n;
	cout<<"Size of array : ";
	cin>>n;
	int a[n];
	for(int i=0;i<n;i++)
		cin>>a[i];
	count_sort(a,1,n-1);
	for(int i=0;i<n;i++)
		cout<<a[i]<<" ";
}
void count_sort(int a[],int p,int q)
{
	int n=q-p+1,k=a[p];
	for(int i=p;i<=q;i++)
		if(a[i]>=k)
			k=a[i];
	int c[k+1];
	for(int i=0;i<=k;i++)
		c[i]=0;
	for(int i=p;i<=q;i++)
		c[a[i]]++;
	for(int i=1;i<=k;i++)
		c[i]+=c[i-1];
	int b[n];
	for(int i=q;i>=p;i--)
	{
		b[c[a[i]]-1]=a[i];
		c[a[i]]--;
	}
	for(int i=p;i<=q;i++)
		a[i]=b[i-p];
}
