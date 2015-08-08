#include <iostream>
using namespace std;
void segregate012(int a[], int n)
{
	int Lo = 0, Mid = 0, Hi = n-1;
	while(Mid<=Hi)
	{
		if(a[Mid]==0)
		{
			swap(a[Mid],a[Lo]);
			Lo++;
			Mid++;
		}
		else if(a[Mid]==1)
			Mid++;
		else if(a[Mid]==2)
		{
			swap(a[Mid],a[Hi]);
			Hi--;
		}
	}
}
int main()
{
	cout<<"n : ";
	int n;
	cin>>n;
	int a[n];
	for(int i=0;i<n;i++)
		cin>>a[i];
	segregate012(a,n);
	for(int i=0;i<n;i++)
		cout<<a[i]<<" ";
	cout<<endl;
	return 0;
}