#include<iostream>
#include<list>
void bucket_sort(float a[],int p,int q);
using namespace std;
int main()
{
	int n;
	cout<<"Size of array : ";
	cin>>n;
	float a[n],max=0;
	for(int i=0;i<n;i++)
	{
		cin>>a[i];
		if(a[i]>=max)
			max=a[i];
	}
	float b[n];
	for(int i=0;i<n;i++)
		b[i]=a[i]/max;
	bucket_sort(b,0,n-1);
	for(int i=0;i<n;i++)
		cout<<(b[i]*max)<<" ";
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
