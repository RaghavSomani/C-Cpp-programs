#include <iostream>
using namespace std;
int getmax(int a[], int n)
{
	int max = a[0];
	for(int i=0;i<n;i++)
		if(a[i]>max)	max = a[i];
	return max;
}
void countsort(int a[], int n, int exp, int b)
{
	int output[n], count[b];
	for(int i=0;i<b;i++)
		count[i]=0;
	for(int i=0;i<n;i++)
		count[(a[i]/exp)%b]++;
	for(int i=1;i<b;i++)
		count[i] += count[i-1];
	for(int i=n-1;i>=0;i--)
		output[ --count[(a[i]/exp)%b] ] = a[i];
	for(int i=0;i<n;i++)
		a[i]=output[i];
}
void radixsort(int a[], int n, int b)
{
	int m = getmax(a,n);
	for(int exp=1;m/exp>0;exp*=b)
		countsort(a,n,exp,b);
}
int main()
{
	int a[] = {8,48,11,65,46,21,71,93,25,3};
	int n = sizeof(a)/sizeof(a[0]);
	int b = 2;
	radixsort(a,n,b);
	for(int i=0;i<n;i++)
		cout<<a[i]<<" ";
	cout<<endl;
	return 0;
}