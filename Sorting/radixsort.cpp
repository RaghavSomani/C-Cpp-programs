#include <iostream>
using namespace std;
int getmax(int a[], int n)
{
	int max = a[0];
	for(int i=0;i<n;i++)
		if(a[i]>max)	max = a[i];
	return max;
}
void countsort(int a[], int n, int exp)
{
	int output[n], count[10] = {0};
	for(int i=0;i<n;i++)
		count[(a[i]/exp)%10]++;
	for(int i=1;i<10;i++)
		count[i] += count[i-1];
	for(int i=n-1;i>=0;i--)
	{
		output[ count[(a[i]/exp)%10] - 1 ] = a[i];		// -1 because array index starts from 0
		count[(a[i]/exp)%10]--;
	}
	for(int i=0;i<n;i++)
		a[i]=output[i];
}
void radixsort(int a[], int n)
{
	int m = getmax(a,n);
	for(int exp=1;m/exp>0;exp*=10)
		countsort(a,n,exp);
}
int main()
{
	int a[] = {8,48,11,65,46,2,71,93,25,3};
	int n = sizeof(a)/sizeof(a[0]);
	radixsort(a,n);
	for(int i=0;i<n;i++)
		cout<<a[i]<<" ";
	cout<<endl;
	return 0;
}