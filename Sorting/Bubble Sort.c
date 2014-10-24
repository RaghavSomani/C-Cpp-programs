#include<stdio.h>
void bs(int [], int);
void main()
{
	int i,n;
	printf("Enter the size of the array: ");
	scanf("%d", &n);
	int a[n];
	printf("Enter the array:\n");
	for(i=0;i<n;i++)
		scanf("%d", &a[i]);
	bs(a,n);
	printf("The sorted array is\n");
	for(i=0;i<n;i++)
		printf("%d  ", a[i]);
}
void bs(int a[], int n)
{
	int i, j, temp;
	for(i=n-2;i>=0;i--)
	{
		for(j=0;j<=i;j++)
		{
			if(a[j]>a[j+1])
			{
				temp=a[j];
				a[j]=a[j+1];
				a[j+1]=temp;
			}
		}
	}
}
