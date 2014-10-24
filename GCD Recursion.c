#include<stdio.h>
void main()
{
	int gcd(int, int);
	int p,q;
	printf("Enter 1st number: ");
	scanf("%d", &p);
	printf("\nEnter 2nd number: ");
	scanf("%d", &q);
	printf("\nThe GCD is: %d", gcd(p,q));
}
int gcd(int a, int b)
{
	if(a<b)
	{
		if(b%a==0)
			return a;
		else
			return gcd(a,b%a);
	}
	if(a>b)
	{
		if(a%b==0)
			return b;
		else
			return gcd(b,a%b);
	}
	if(a==b)
	return a;
}
