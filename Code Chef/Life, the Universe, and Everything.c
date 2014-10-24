#include<stdio.h>
int main()
{
	int a[1000],i=0;
	do
	{
		scanf("%d",&a[i]);
		i++;
	}while(a[i-1]!=42);
	int n=i;
	for(i=0;i<n-1,a[i]!=42;i++)
		printf("%d\n",a[i]);
	return 0;
}
