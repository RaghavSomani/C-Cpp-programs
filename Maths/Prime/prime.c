#include<stdio.h>
#include<stdlib.h>
#include<time.h>
long int power_mod(long int x,long int y, long int n)
{
	if((y&1)==0&&y!=0)
	{
		long int temp=power_mod(x,y/2,n)%n;
		return (temp*temp)%n;
	}
	else if((y&1)==1&&y!=1)
	{
		long int temp=power_mod(x,y-1,n)%n;
		return (temp*(x%n))%n;		
	}
	else if(y==0)
		return 1;
	else if(y==1)
		return x%n;
}
int prime(long int n)
{
	int k=20,temp=1,i;
	long int a=0;
	for(i=0;i<k;i++)
	{
		a=rand()%(n-1)+1;
		//a=i+1;
		if(power_mod(a,n-1,n)!=1)
			temp=0;
	}
	if(temp==0)
		return 0;
	else if(temp==1)
		return 1;
}
int main()
{
	long int m,n,i,count;
	srand(time(NULL));
	int t;
	scanf("%d",&t);
	while(t--)
	{
		count=0;
		scanf("%ld %ld",&m,&n);
		if(m==1||(m%2==0&&m!=2))
			m++;
		if(m==2&&n>=2)
		{
			m++;
			printf("2\n");
			count++;
		}
		if(m<=3&&n>=3)
		{
			printf("3\n");
			m=m+2;
			count++;
		}
		if(m<=5&&n>=5)
		{
			printf("5\n");
			m=m+2;
			count++;
		}
		if(m<=7&&n>=7)
		{
			printf("7\n");
			m=m+4;
			count++;
		}
		if(m<=11&&n>=11)
		{
			printf("11\n");
			m=m+2;
			count++;
		}
		for(i=m;i<=n;i=i+2)
		{	
			if(i%3!=0||i%5!=0||i%7!=0||i%11!=0)
				if(prime(i)==1)
				{
					count++;
					//printf("%ld\n",i);
				}
		}
		printf("\n%ld\n",count);
	}
}




