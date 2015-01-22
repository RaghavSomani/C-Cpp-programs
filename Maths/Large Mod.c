#include<stdio.h>
long int mod(long int r,long int x,long int n);
int main()
{
	long int x,m,n,ans,r;
	register long int i;
	register int j;
	int t;
	scanf("%d",&t);
	while(t--)
	{
		ans=1;
		scanf("%ld %ld %ld",&x,&m,&n);
		r=x%n;
		for(i=0;i<m;i++)
		{
			ans=(ans+r)%n;
			r=mod(r,x,n);
		}
		printf("%ld\n",ans);
	}
	return 0;
}
long int mod(long int r,long int x,long int n)
{
	long int temp=x%n,i;
	for(i=0;i<r;i++)
		temp=(x%n+temp)%n;
	return temp;
}
