#include<stdio.h>
void ms(int [], int, int);
void merge(int [], int, int, int);
int main()
{
	int i,n;
	printf("Enter the size of the array: ");
	scanf("%d", &n);
	if(n<1)
		return 0;
	int a[n];
	printf("Enter the array:\n");
	for(i=0;i<n;i++)
		scanf("%d", &a[i]);
	ms(a,0,n-1);
	printf("The sorted array is\n");
	for(i=0;i<n;i++)
		printf("%d  ", a[i]);
	return 0;
}
void ms(int a[], int p, int r)
{
	if(p<r)										//this is very important
	{
		int q=(p+r)/2;
		ms(a,p,q);
		ms(a,q+1,r);
		merge(a,p,q,r);
	}
}
void merge(int a[], int p, int q, int r)
{
	int temp, i=p, j=q+1, k=0;
	int b[r-p+1];
	while(i<=q&&j<=r)
	{
		if(a[i]>=a[j])
		{
			b[k]=a[j];
			k++;
			j++;
		}
		else
		{
			b[k]=a[i];
			k++;
			i++;
		}
	}
	while(i<=q)
	{
		b[k]=a[i];
		i++;
		k++;
	}
	while(j<=r)
	{
		b[k]=a[j];
		j++;
		k++;
	}
	k=0;
	int c;
	for(c=p;c<=r;c++,k++)
	{
		a[c]=b[k];
	}
}
