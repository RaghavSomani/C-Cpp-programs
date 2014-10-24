#define phi 0.61803398874989484
#include <stdio.h>
int main()
{
	double n;
	scanf("%lf",&n);
	if(n<=3)
	{
		printf("Fib\n");
		return 0;
	}
	double a=(phi*n)+(1/n);
	double b=(phi*n)-(1/n);
	long int a1=(int)a;
	long int b1=(int)b;
	if(a1-b1==1)
		printf("Fib\n");
	else
		printf("Not Fib\n");
	return 0;
}
