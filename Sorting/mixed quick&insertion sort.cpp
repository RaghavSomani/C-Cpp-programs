#include<iostream>
#include<sys/time.h>
#include<stdlib.h>
void mixed_quick_sort(int a[],int p,int r);
int random_partition(int a[],int p,int r);
void insertion_sort(int a[], int p, int q);
using namespace std;
int main()
{
	int n,temp,j;
	srand(time(NULL));
	cout<<"Size of array : ";
	cin>>n;
	int a[n];
	for(int i=0;i<n;i++)
		cin>>a[i];
	mixed_quick_sort(a,0,n-1);
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
void mixed_quick_sort(int a[],int p,int r)
{
	if((r-p)>20)
	{
		int q=random_partition(a,p,r);
		mixed_quick_sort(a,p,q-1);
		mixed_quick_sort(a,q+1,r);
	}
	else
		insertion_sort(a,p,r);
		
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
