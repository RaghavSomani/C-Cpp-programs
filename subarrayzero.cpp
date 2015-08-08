#include <iostream>
#include <unordered_map>
using namespace std;
bool zerosub(int a[],int n)
{
	int sum = 0;
	unordered_map<int,bool> H;
	for(int i=0;i<n;i++)
	{
		sum += a[i];
		if(sum==0||a[i]==0||H[sum]==true)
			return true;
		H[sum]=true;
	}
	return false;
}
int main()
{
	int n;
	cout<<"n : ";
	cin>>n;
	int a[n];
	for(int i=0;i<n;i++)
		cin>>a[i];
	cout<<zerosub(a,n);
	return 0;
}