#include<stdio.h>
bs(int a[], int key, int min, int max)
{
	int mid;
	mid=max/2+min/2;
	if(max>min)
	{
		if(a[mid]<key)
		{
			bs(a, key, mid+1, max);
		}
		else if(a[mid]>key)
		{
			bs(a, key, min, mid-1);
		}
		else
		{
			printf("%d is at position %d", key, mid+1);
		}
	}
	else
	{
		printf("Element not found!!");
	}
}
void main()
{
	int i, n, a[n], key;
	printf("Enter the number of elements to be added: ");
	scanf("%d", &n);
	printf("Enter the elements(in ascending order) :\n");
	for(i=0;i<n;i++)
	{
		printf("#%d ", i+1);
		scanf("%d", &a[i]);
	}
	printf("Enter the element to search: ");
	scanf("%d", &key);
	bs(a, key, 0, n-1);
}
