#include<stdio.h>
#include<math.h>
void rs(int [], int);
void main()
{
	int i,n;
	printf("Enter the size of the array: ");
	scanf("%d", &n);
	int a[n];
	printf("Enter the array:\n");
	for(i=0;i<n;i++)
		scanf("%d", &a[i]);
	rs(a,n);
	printf("The sorted array is\n");
	for(i=0;i<n;i++)
		printf("%d  ", a[i]);
}
void rs(int a[], int n)
{
	int array[n][10];
	int i,j,k=0;
	int max=a[0];
	for(i=0;i<n;i++)
		if(a[i]>max)
			max=a[i];
	int digits=log(max)/log(10)+1,l;
	for(l=1;l<=digits;l++)
	{
		for(i=0;i<n;i++)
			for(j=0;j<10;j++)
				array[i][j]='\0';
		for(i=0;i<n;i++)
		{
			j=0;
			int m=(a[i]%(int)pow(10,l))/pow(10,l-1);
			while(array[j][m]!='\0')
				j++;
			array[j][m]=a[i];
		}
		for(i=0;i<10;i++)
		{
			j=0;
			while(array[j][i]!='\0')
			{
				a[k]=array[j][i];
				k++;
				j++;
			}
		}
	}
}
