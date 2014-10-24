#include<stdio.h>
#include<stdlib.h>
int cmpfunc(const void *a, const void *b)
{
	const int *x=a;
	const int *y=b;
	return x[0]-y[0];
}
void main()
{
	int a[5][2],i;
	for(i=0;i<5;i++)
	{
		scanf("%d", &a[i][0]);
		scanf("%d", &a[i][1]);
	}
	qsort(a,5,2*sizeof(int),cmpfunc);
	for(i=0;i<5;i++)
	{
		printf("\n%d %d", a[i][0], a[i][0]);
	}
}
