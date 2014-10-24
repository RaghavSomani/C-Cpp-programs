#include<stdio.h>
void ls(int [], int, int);
void main()
{
	printf("Enter the number of elements : ");
	int n,i,key;
	scanf("%d", &n);
	int a[n];
	for(i=0;i<n;i++)
		scanf("%d", &a[i]);
	printf("Element to be searched : ");
	scanf("%d", &key);
	ls(a,n,key);
}
void ls(int a[], int n, int key)
{
	int pos=-1,i;
	for(i=0;i<n;i++)
		if(a[i]==key)
			pos=i;
	if(pos!=-1)
		printf("\nThe element was found at position %d !!", pos+1);
	else
		printf("\nSorry! The element was not found!!");
}
