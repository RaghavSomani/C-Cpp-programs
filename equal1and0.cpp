#include <iostream>
using namespace std;
int equal01(int a[], int n)
{
	int maxsize = -1, startindex;
	int sumleft[n];
	int min, max;
	sumleft[0] = ((a[0]==0)?-1:1);
	min = a[0];
	max = a[0];
	for(int i=0;i<n;i++)
	{
		sumleft[i] = sumleft[i-1] + ((a[i]==0)?-1:1);
		if(sumleft[i]<min)
			min = sumleft[i];
		if(sumleft[i]>max)
			max = sumleft[i];
	}
	int H[max-min+1];
	for(int i=0;i<max-min+1;i++)
		H[i]=-1;
	for(int i=0;i<n;i++)
	{
		if(sumleft[i]==0)
		{
			maxsize = i+1;
			startindex = 0;
		}
		if(H[sumleft[i]-min]==-1)
			H[sumleft[i]-min] = i;
		else if(i - H[sumleft[i]-min] > maxsize)
		{
			maxsize = i - H[sumleft[i]-min];
			startindex = H[sumleft[i]-min] + 1;
		}
	}
	if(maxsize == -1)
		cout<<"No such array";
	else
		cout<<startindex<<" to "<<startindex+maxsize-1;
}
int main()
{
	int a[] = {1,0,0,1,0,1,1};
	int size = sizeof(a)/sizeof(a[0]);
	int ans = equal01(a,size);
	return 0;
}