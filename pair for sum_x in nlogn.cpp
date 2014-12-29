#include<iostream>
#define inf 2147483647
int binary_search(int a[], int key, int min, int max);
void merge_sort(int a[],int p,int r);
void merge(int a[],int p,int q,int r);
using namespace std;
int main()
{
	int n,key,x;
	cout<<"Size of the array : ";
	cin>>n;
	int a[n];
	for(int i=0;i<n;i++)
		cin>>a[i];
	cout<<"Sum to be equal to : ";
	cin>>x;
	merge_sort(a,0,n-1);
	int flag=0;
	for(int i=0;i<n;i++)
	{
		int pos=binary_search(a,x-a[i],0,n-1);
		if(pos!=-1)
		{
			cout<<a[i]<<" and "<<a[pos]<<" sum up to "<<x<<endl;
			flag=1;
		}
	}
	if(flag==0)
		cout<<"No such pair exist";
}
int binary_search(int a[], int key, int min, int max)
{
	int mid=max/2+min/2;
	if(min<max)
	{
		if(a[mid]>key)
			binary_search(a,key,min,mid-1);
		else if(a[mid]<key)
			binary_search(a,key,mid+1,max);
		else
			return mid;
	}
	else
		return -1;
}
void merge_sort(int a[],int p,int r)
{
	if(p<r)
	{
		int q=p/2+r/2;
		merge_sort(a,p,q);
		merge_sort(a,q+1,r);
		merge(a,p,q,r);
	}
}
void merge(int a[],int p,int q,int r)
{
	int n1=q-p+1;
	int n2=r-q;
	int left[n1+1];
	int right[n2+1];
	for(int i=0;i<n1;i++)
		left[i]=a[p+i];
	for(int i=0;i<n2;i++)
		right[i]=a[q+i+1];
	left[n1]=inf;
	right[n2]=inf;
	int i=0,j=0;
	for(int k=p;k<=r;k++)
	{
		if(left[i]<=right[j])
		{
			a[k]=left[i];
			i++;
		}
		else
		{
			a[k]=right[j];
			j++;
		}
	}	
}
