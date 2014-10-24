#include<iostream>
using namespace std;
void qs(int *a,int start,int end);
int partition(int *a,int start,int end);
int main()
{
	int n,i;
	cout<<"Number of elements : ";
	cin>>n;
	int a[n];
	for(i=0;i<n;i++)
		cin>>a[i];
	qs(a,0,n-1);
	for(i=0;i<n;i++)
		cout<<a[i]<<" ";
}
void qs(int *a,int start,int end)
{
	if(start<end)
	{
		int pIndex=partition(a,start,end);
		qs(a,start,pIndex-1);
		qs(a,pIndex+1,end);
	}
}
int partition(int *a,int start,int end)
{
	int pivot=a[end];
	int pIndex=start;
	for(int i=start;i<end;i++)
	{
		if(a[i]<=pivot)
		{
			std::swap(a[i],a[pIndex]);
			pIndex++;
		}
	}
	std::swap(a[end],a[pIndex]);
	return pIndex;
}
