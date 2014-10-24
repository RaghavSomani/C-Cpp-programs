#include<stdio.h>
void is(int [], int);
void main()
{
	int i,n;
	printf("Enter the size of the array: ");
	scanf("%d", &n);
	int a[n];
	printf("Enter the array:\n");
	for(i=0;i<n;i++)
		scanf("%d", &a[i]);
	is(a,n);
	printf("The sorted array is\n");
	for(i=0;i<n;i++)
		printf("%d  ", a[i]);
}
void is(int a[], int n)
{
	int i, j, temp;
	for(i=1;i<n;i++)
	{
		temp=a[i];
		j=i-1;
		while(j>=0&&a[j]>temp)
		{
			a[j+1]=a[j];
			j--;
		}
		a[j+1]=temp;
	}
}
