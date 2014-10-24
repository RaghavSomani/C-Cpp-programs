#include<stdio.h>
void ss(int [], int);
void main()
{
	int i,n;
	printf("Enter the size of the array: ");
	scanf("%d", &n);
	int a[n];
	printf("Enter the array:\n");
	for(i=0;i<n;i++)
		scanf("%d", &a[i]);
	ss(a,n);
	printf("The sorted array is\n");
	for(i=0;i<n;i++)
		printf("%d  ", a[i]);
}
void ss(int a[], int n)
{
	int i,j,temp;
	for(i=0;i<n;i++)
	{
		for(j=i;j<n;j++)
		{
			if(a[j]<=a[i])
			{
				temp=a[j];
				a[j]=a[i];
				a[i]=temp;
			}
		}
	}
}
