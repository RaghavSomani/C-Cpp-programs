#include<iostream>
#include<sys/time.h>
#include<stdlib.h>
#define inf 2147483647
void merge_sort(int a[],int p,int r,int limit);
void merge(int a[],int p,int q,int r);
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
		a[i]=i;
	for(int i=0;i<n;i++)
	{
		j=rand()%(n-i)+i;
		a[i]=(a[j]+a[i])-(a[j]=a[i]);
	}
	struct timeval  tv1, tv2;
	double times[101]={0};
	for(int limit=0;limit<=100;limit++)
	{
		double total_ex_time=0.0,ave_ex_time=0.0;
		for(int l=0;l<20;l++)
		{
			gettimeofday(&tv1, NULL);
			merge_sort(a,0,n-1,limit);
			gettimeofday(&tv2, NULL);
			double ex_time=(double) (tv2.tv_usec - tv1.tv_usec) / 1000000 +(double) (tv2.tv_sec - tv1.tv_sec);
			total_ex_time+=ex_time;
			for(int i=0;i<n;i++)
			{
				j=rand()%(n-i)+i;
				a[i]=(a[j]+a[i])-(a[j]=a[i]);
			}
		}
		ave_ex_time=total_ex_time/20;
		times[limit]=ave_ex_time;
		printf("Avg time taken = %f seconds limit = %d\n",ave_ex_time,limit);
	}
	double min=10000,max=0.0,ave=0.0;
	int best,worst;
	for(int i=0;i<=100;i++)
	{
		if(times[i]<min)
		{
			min=times[i];
			best=i;
		}
	}
	cout<<"Best ave running time = "<<min<<" for limit = "<<best<<endl;
}
void merge_sort(int a[],int p,int r,int limit)
{
	if(r-p>limit)
	{
		int q=p/2+r/2;
		merge_sort(a,p,q,limit);
		merge_sort(a,q+1,r,limit);
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
