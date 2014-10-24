#include<stdio.h>
int main()
{
	int n,i,j;
	scanf("%d",&n);
	int a[n][n];
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			scanf("%1d",&a[i][j]);
	for(i=1;i<n-1;i++)
	{
		for(j=1;j<n-1;j++)
		{
			if(a[i][j]>a[i-1][j]&&a[i][j]>a[i+1][j]&&a[i][j]>a[i][j-1]&&a[i][j]>a[i][j+1])
				a[i][j]=10;
		}
	}
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(a[i][j]==10)
				printf("x");
			else
				printf("%d",a[i][j]);
		}
		printf("\n");
	}
}
