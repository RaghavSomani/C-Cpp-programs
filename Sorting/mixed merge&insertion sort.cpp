#include<iostream>
#define inf 2147483647
void merge_sort(int a[],int p,int r);
void merge(int a[],int p,int q,int r);
void insertion_sort(int a[], int p, int q);
using namespace std;
int main()
{
	int n,key,x;
	cout<<"Size of the array : ";
	cin>>n;
	int a[n];
	for(int i=0;i<n;i++)
		cin>>a[i];
	merge_sort(a,0,n-1);
	for(int i=0;i<n;i++)
		cout<<a[i];
}
void merge_sort(int a[],int p,int r)
{
	if(r-p>30)
	{
		int q=p/2+r/2;
		merge_sort(a,p,q);
		merge_sort(a,q+1,r);
		merge(a,p,q,r);
	}
	else
		insertion_sort(a,p,r);
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
void insertion_sort(int a[], int p, int q)
{
	int i, j, temp;
	for(i=p+1;i<=q;i++)
	{
		temp=a[i];
		j=i-1;
		while(j>=p&&a[j]>temp)
		{
			a[j+1]=a[j];
			j--;
		}
		a[j+1]=temp;
	}
}
