#include<iostream>
#include<stdlib.h>
#include<sys/time.h>
int randomized_select(int a[],int p,int r,int i);
int random_partition(int a[],int p,int r);
using namespace std;
int main()
{
	int n,i;
	cout<<"Size of array : ";
	cin>>n;
	int a[n];
	for(i=0;i<n;i++)
		cin>>a[i];
	cout<<"Order : ";
	cin>>i;
	cout<<randomized_select(a,0,n-1,i);
}
int randomized_select(int a[],int p,int r,int i)
{
	if(p==r)
		return a[p];
	int q=random_partition(a,p,r);
	int k=q-p+1;
	if(i==k)
		return a[q];
	else if(i<k)
		return randomized_select(a,p,q-1,i);
	else
		return randomized_select(a,q+1,r,i-k);
}
int random_partition(int a[],int p,int r)
{
	int temp=rand()%(r-p+1)+p;
	a[temp]=(a[r]+a[temp])-(a[r]=a[temp]);
	int i=p-1;
	for(int j=p;j<r;j++)
		if(a[j]<=a[r])
		{
			i++;
			a[i]=(a[j]+a[i])-(a[j]=a[i]);
		}
	a[i+1]=(a[r]+a[i+1])-(a[r]=a[i+1]);
	return i+1;
}
