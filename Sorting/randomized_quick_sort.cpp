#include<iostream>
#include<stdlib.h>
#include<sys/time.h>
int random_partition(int a[],int p,int r);
void quick_sort(int a[],int p,int r);
using namespace std;
int main()
{
	int n;
	cout<<"Size of array : ";
	cin>>n;
	int a[n];
	for(int i=0;i<n;i++)
		cin>>a[i];
	srand(time(NULL));
	quick_sort(a,0,n-1);
	for(int i=0;i<n;i++)
		cout<<a[i]<<" ";
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
void quick_sort(int a[],int p,int r)
{
	if(p<r)
	{
		int q=random_partition(a,p,r);
		quick_sort(a,p,q-1);
		quick_sort(a,q+1,r);
	}
}
