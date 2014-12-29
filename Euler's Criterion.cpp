#include<iostream>
long long int power_mod(long int x,long int r,long int n);
using namespace std;
int main()
{
	int t;
	cin>>t;
	long int x,r;
	while(t--)
	{
		cin>>x>>r;
		if(power_mod(x,r/2,r)&1||r==2||x==0)
			cout<<"YES\n";
		else
			cout<<"NO\n";
	}
}
long long int power_mod(long int x,long int r,long int n)
{
	long long int temp=x%n,p=1;
	while(r>0)
	{
		if(r&1)
		{
			p*=temp;
			p=p%n;
		}
		r=r>>1;
		temp=(temp*temp)%n;
	}
	return p;
}
