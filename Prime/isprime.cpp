#include<iostream>
#include<math.h>
using namespace std;
int isprime(int n);
int main()
{
	int n;
	cin>>n;
	for(int i=1;i<n;i++)
		if(isprime(i))
			cout<<i<<" ";
}
int isprime(int n)
{
	if(n==2)
		return 1;
	else if(n==1)
		return 0;
	int flag=(n%2==0)?0:1;
	int sqn=(int)sqrt(n);
	for(int i=3;i<=sqn;i+=2)
		if(n%i==0)
			flag=0;
	return flag;
}
