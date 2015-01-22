#include <iostream>
#include <limits.h>
using namespace std;
void max_heapify(int a[],int n,int i);
void build_max_heap(int a[],int n);
int maximum(int a[]);
int extract_max(int a[], int &n);
void increase_key(int a[], int i, int n, int k);
void insert(int a[], int x, int &n);
int main()
{
	int n;
	cout<<"Size of initial priority queue : ";
	cin>>n;
	int a[n];
	for(int i=0;i<n;i++)
		cin>>a[i];
	build_max_heap(a,n);
	int choice;
	cout<<"1. Maximum"<<endl;
	cout<<"2. Extract Maximum"<<endl;
	cout<<"3. Increase Key"<<endl;
	cout<<"4. Insert"<<endl;
	cout<<"5. Exit"<<endl;
	while(choice!=5)
	{
		cout<<"Enter choice : ";
		cin>>choice;
		cout<<endl;
		switch(choice)
		{
			case 1:
				cout<<"Maximum is : "<<maximum(a);
				break;
			case 2:
				cout<<extract_max(a,n)<<" was extracted"<<endl;
				break;
			case 3:
				int index;
				int new_key;
				cout<<"Index to increment : ";
				cin>>index;
				cout<<a[index]<<" to be incremented to : ";
				cin>>new_key;
				increase_key(a,index,n,new_key);
				break;
			case 4:
				int key;
				cout<<"Key to insert : ";
				cin>>key;
				insert(a,key,n);
				break;
			case 5:
				break;
			default:
				break;
		}
		cout<<endl<<"Now the priority queue is : ";
		for(int i=0;i<n;i++)
			cout<<a[i]<<" ";
		cout<<endl;
	}
	return 0;
}
int maximum(int a[])
{
	return a[0];
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
void insert(int a[], int x, int &n)
{
	n++;
	a[n-1]=INT_MIN;
	increase_key(a,n-1,n,x);
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
void build_max_heap(int a[],int n)
{
	for(int i=(n-2)/2;i>=0;i--)
		max_heapify(a,n,i);
}