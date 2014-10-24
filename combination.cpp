#include<iostream>
int comb(int n, int r);
using namespace std;
int main()
{
	int n,r;
	cout<<"n = ";
	cin>>n;
	cout<<"r = ";
	cin>>r;
	if(n>=r&&r>=0)
		cout<<n<<" C "<<r<<" = "<<comb(n,r);
}
int comb(int n, int r)		//  nCr = n-1Cr + n-1Cr-1
{
	if(n>r)
	{
		if(r-1)
			return (comb(n-1,r)+comb(n-1,r-1));
		else
			return n;
	}
	else if(n==r)
		return 1;
}
