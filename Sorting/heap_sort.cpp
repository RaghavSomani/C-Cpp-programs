#include<iostream>
using namespace std;
void max_heapify(int a[],int n,int i);
void build_max_heap(int a[],int n);
void heap_sort(int a[],int n);
int main()
{
	int n;
	cout<<"Size of array : ";
	cin>>n;
	int a[n];
	for(int i=0;i<n;i++)
		cin>>a[i];
	heap_sort(a,n);
	for(int i=0;i<n;i++)
		cout<<a[i]<<" ";
}
void max_heapify(int a[],int n,int i)
{
	int l,r,largest;
	while(1)
	{
		l=(2*i)+1;
		r=(2*i)+2;
		if(l<n&&a[l]>a[i])
			largest=l;
		else
			largest=i;
		if(r<n&&a[r]>a[largest])
			largest=r;
		if(largest==i)
			return;
		a[largest]=(a[i]+a[largest])-(a[i]=a[largest]);
		i=largest;
	}
}
void build_max_heap(int a[],int n)
{
	for(int i=(n-2)/2;i>=0;i--)
		max_heapify(a,n,i);
}
void heap_sort(int a[],int n)
{
	build_max_heap(a,n);
	for(int i=n-1;i>0;i--)
	{
		a[0]=(a[i]+a[0])-(a[i]=a[0]);
		n--;
		max_heapify(a,n,0);
	}
}
