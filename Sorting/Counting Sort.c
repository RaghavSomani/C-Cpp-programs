#include<stdio.h>
void cs(int [], int);
void main()
{
	int i,n;
	printf("Enter the size of the array: ");
	scanf("%d", &n);
	int a[n];
	printf("Enter the array:\n");
	for(i=0;i<n;i++)
		scanf("%d", &a[i]);
	cs(a,n);
}
void cs(int a[], int n)
{
	int i,j;
	int c[1000];
	for(i=0;i<1000;i++)
	{
		c[i]=0;
	}
	for(i=0;i<n;i++)
	{
		c[a[i]]++;
	}
	for(i=0;i<1000;i++)
	{
		for(j=0;j<c[i];j++)
		printf("%d ", i);
	}
}
