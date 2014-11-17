#include<iostream>
using namespace std;
void multiply(int a[2][2], int b[2][2], int c[2][2])
{
	for(int i=0;i<2;++i)
		for(int j=0;j<2;++j)
			for(int k=0;k<2;++k)
				c[i][j]+=a[i][k]*b[k][j];
}
void pow(int a[2][2], int b[2][2], int n)
{
	int c[2][2]={{}};
	while(n)
	{
		if(n%2==1)
		{
			c[0][0]=0;
			c[0][1]=0;
			c[1][0]=0;
			c[1][1]=0;
			multiply(b,a,c);
			for(int i=0;i<2;i++)
				for(int j=0;j<2;j++)
					b[i][j]=c[i][j];
		}
		c[0][0]=0;
		c[0][1]=0;
		c[1][0]=0;
		c[1][1]=0;
		multiply(a,a,c);
		for(int i=0;i<2;i++)
				for(int j=0;j<2;j++)
					a[i][j]=c[i][j];
		n/=2;
	}
}
int main()
{
	int a[2][2]={{1,1},{1,0}};
	int b[2][2]={{1,0},{0,1}};
	int n;
	cout<<"n : ";
	cin>>n;
	cout<<"Fib "<<n<<" = ";
	if(n==0)
		cout<<0;
	else
	{
		pow(a,b,n-1);
		cout<<b[0][0];
	}
	return 0;
}
