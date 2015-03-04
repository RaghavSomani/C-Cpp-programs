#include <iostream>
#include <limits.h>
using namespace std;
void max_heapify(int a[],int n,int i);
void min_heapify(int a[],int n,int i);
void build_max_heap(int a[],int n);
void build_min_heap(int a[],int n);
void increase_key(int a[], int i, int n, int k);
void decrease_key(int a[], int i, int n, int k);
void insert_max_heap(int a[], int x, int &n);
void insert_min_heap(int a[], int x, int &n);
int extract_max(int a[], int &n);
int extract_min(int a[], int &n);
int root(int a[]);
int main()
{
	int n,n1=0,n2=0;
	cout<<"Total size of array : ";
	cin>>n;
	int a[n],b[n],k;
	while(n1+n2!=n)
	{
		cout<<"Enter element : ";
		cin>>k;
		if(n1==0)
		{
			insert_max_heap(a,k,n1);
			cout<<"Median : "<<root(a)<<endl;
			cout<<"Elements : "<<root(a)<<endl;
			continue;
		}
		if(k<=root(a))
			insert_max_heap(a,k,n1);
		else
			insert_min_heap(b,k,n2);
		if(n1-n2>1)
			insert_min_heap(b,extract_max(a,n1),n2);
		else if(n2-n1>=1)
			insert_max_heap(a,extract_min(b,n2),n1);
		cout<<"Median : "<<root(a)<<endl;
		cout<<"Elements : ";
		for(int i=0;i<n1;i++)
			cout<<a[i]<<" ";
		for(int i=0;i<n2;i++)
			cout<<b[i]<<" ";
		cout<<endl;
	}
	return 0;
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
			break;
		a[largest]=(a[i]+a[largest])-(a[i]=a[largest]);
		i=largest;
	}
}
void min_heapify(int a[],int n,int i)
{
	int l,r,smallest;
	while(1)
	{
		l=(2*i)+1;
		r=(2*i)+2;
		if(l<n&&a[l]<a[i])
			smallest=l;
		else
			smallest=i;
		if(r<n&&a[r]<a[smallest])
			smallest=r;
		if(smallest==i)
			break;
		a[smallest]=(a[i]+a[smallest])-(a[i]=a[smallest]);
		i=smallest;
	}
}
void build_max_heap(int a[],int n)
{
	for(int i=(n-2)/2;i>=0;i--)
		max_heapify(a,n,i);
}
void build_min_heap(int a[],int n)
{
	for(int i=(n-2)/2;i>=0;i--)
		min_heapify(a,n,i);
}
int extract_max(int a[], int &n)
{
	if(n<1)
	{
		cout<<"Heap Empty!"<<endl;
		return 0;
	}
	int max=a[0];
	a[0]=a[n-1];
	n--;
	max_heapify(a,n,0);
	return max;
}
int extract_min(int a[], int &n)
{
	if(n<1)
	{
		cout<<"Heap Empty!"<<endl;
		return 0;
	}
	int min=a[0];
	a[0]=a[n-1];
	n--;
	min_heapify(a,n,0);
	return min;
}
void increase_key(int a[], int i, int n, int k)
{
	if(k<a[i])
	{
		cout<<"New key is smaller, try a bigger key!"<<endl;
		return;
	}
	a[i]=k;
	while(i>0 && a[(i-1)/2]<a[i])
	{
	    a[(i-1)/2]=(a[i]+a[(i-1)/2])-(a[i]=a[(i-1)/2]);
	    i=(i-1)/2;
	}
}
void decrease_key(int a[], int i, int n, int k)
{
	if(k>a[i])
	{
		cout<<"New key is bigger, try a smaller key!"<<endl;
		return;
	}
	a[i]=k;
	while(i>0 && a[(i-1)/2]>a[i])
	{
	    a[(i-1)/2]=(a[i]+a[(i-1)/2])-(a[i]=a[(i-1)/2]);
	    i=(i-1)/2;
	}
}
void insert_max_heap(int a[], int x, int &n)
{
	n++;
	a[n-1]=INT_MIN;
	increase_key(a,n-1,n,x);
}
void insert_min_heap(int a[], int x, int &n)
{
	n++;
	a[n-1]=INT_MAX;
	decrease_key(a,n-1,n,x);
}
int root(int a[])
{
	return a[0];
}