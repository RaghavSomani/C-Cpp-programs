#include<stdio.h>
#include<math.h>
int main()
{
	int i,j;
	int n=6;
	int a[n][n];
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			scanf("%d",&a[i][j]);
	printf("The Determinant of the matrix is : %d",det(6,a));
}
int det(int n,int a[n][n])
{
	int i,j,k,d=0,x,y;
	if(n==1)
		return a[0][0];
	else
	{
		for(i=0;i<n;i++)
		{
			int temp[n-1][n-1];
			for(j=1,x=0;j<n,x<n-1;j++,x++)
				for(k=0,y=0;k<n,y<n-1;k++,y++)
				{
					if(k!=i)
						temp[x][y]=a[j][k];
					else
						y--;
				}
			d+=pow(-1,i)*det(n-1,temp)*a[0][i];
		}
	}
	return d;
}
