#include<iostream>
using namespace std;
typedef struct
{
	int start;
	int end;
	int sum;
}subarray;
subarray max_subarray(int a[],int n);
int main()
{
	int n;
	cout<<"Size of array : ";
	cin>>n;
	int a[n];
	for(int i=0;i<n;i++)
		cin>>a[i];
	subarray array;
	array=max_subarray(a,n);
	cout<<"Max sum is : "<<array.sum<<endl;
	for(int i=array.start;i<=array.end;i++)
		cout<<a[i]<<" ";
}
subarray max_subarray(int a[],int n)
{
	subarray max_subarray;
	max_subarray.start=0;
	max_subarray.end=0;
	max_subarray.sum=0;
	int current_sum=0,i=0;
	for(int j=0;j<n;j++)
	{
		current_sum+=a[j];
		if(current_sum>max_subarray.sum)
		{
			max_subarray.sum=current_sum;
			max_subarray.end=j;
			max_subarray.start=i;
		}
		if(current_sum<0)
		{
			current_sum=0;
			i++;
		}
	}
	return max_subarray;
}
