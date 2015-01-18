#include<limits.h>
#include<sys/time.h>
#include<stdlib.h>
#include<list>
using namespace std;
int random_partition(int a[],int p,int r)
{
	srand(time(NULL));
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
void randomized_quick_sort(int a[],int p,int r)
{
	if(p<r)
	{
		int q=random_partition(a,p,r);
		randomized_quick_sort(a,p,q-1);
		randomized_quick_sort(a,q+1,r);
	}
}
int partition(int a[],int p,int r)
{
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
	if(r>p)
	{
		int q=partition(a,p,r);
		quick_sort(a,p,q-1);
		quick_sort(a,q+1,r);
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
	left[n1]=INT_MAX;
	right[n2]=INT_MAX;
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
void merge_sort(int a[],int p,int r)
{
	if(r>p)
	{
		int q=p/2+r/2;
		merge_sort(a,p,q);
		merge_sort(a,q+1,r);
		merge(a,p,q,r);
	}
}
void mixed_merge_sort(int a[],int p,int r)
{
	if(r-p>30)
	{
		int q=p/2+r/2;
		mixed_merge_sort(a,p,q);
		mixed_merge_sort(a,q+1,r);
		merge(a,p,q,r);
	}
	else
		insertion_sort(a,p,r);
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
void bucket_sort(float a[],int p,int q)
{
	int n=q-p+1;
	list<float> b[n+1];
	for(int i=p;i<=q;i++)
		b[(int)(n*a[i])].push_back(a[i]);
	for(int i=0;i<n;i++)
		b[i].sort();
	int j=p;
	for(int i=0;i<=n;i++)
	{
		while (!b[i].empty())
		{
    		a[j]=b[i].front();
    		j++;
			b[i].pop_front();
		}
	}
}
