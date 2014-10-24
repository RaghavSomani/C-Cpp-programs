#include<stdio.h>
long int fib(unsigned long int n)			// for n<=48
{
	if(n&1&&n>1)
	{
		long int f1=fib((n+1)*0.5);
		long int f2=fib((n-1)*0.5);
		return (f1*f1)+(f2*f2);
	}
	else if((!(n&1))&&n>1)
	{
		long int f1=fib((n-2)*0.5);
		long int f2=fib(n*0.5);
		return ((f1+f1+f2)*f2);
	}
	else if(n)
		return 1;
	else
		return 0;
}
int main(int argc, char const *argv[])
{
	unsigned long int n;
	scanf("%ld",&n);
	printf("%ld\n",fib(n));
	return 0;
}
