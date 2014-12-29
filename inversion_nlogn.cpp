#include<iostream>
#define inf 2147483647
int merge_inversion_sort(int a[],int p,int r);
int merge_count(int a[],int p,int q,int r);
using namespace std;
int main()
{
	int n,key,x;
	cout<<"Size of the array : ";
	cin>>n;
	int a[n];
	for(int i=0;i<n;i++)
		cin>>a[i];
	cout<<"Number of inversions = "<<merge_inversion_sort(a,0,n-1);
}
int merge_inversion_sort(int a[],int p,int r)
{
	int inversion=0;
	if(p<r)
	{
		int q=p/2+r/2;
		inversion+=merge_inversion_sort(a,p,q);
		inversion+=merge_inversion_sort(a,q+1,r);
		inversion+=merge_count(a,p,q,r);
	}
	return inversion;
}
int merge_count(int a[],int p,int q,int r)
{
	int inversion=0;
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
			inversion+=n1-i;
		}
	}
	return inversion;	
}
