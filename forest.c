#include<stdio.h>
void burn(int forest[50][50],int rows,int cols,int srow,int scol);
void main()
{
	int forest[50][50],rows,cols,i,j,srow,scol;
	char c;
	printf("Number of rows : ");
	scanf("%d", &rows);
	printf("Number of columns : ");
	scanf("%d", &cols);
	printf("Forest (1 for dense regions else 0) :\n");
	for(i=0;i<rows;i++)
		for(j=0;j<cols;j++)
			scanf("%d",&forest[i][j]);
	printf("Region to burn : ");
	scanf("%d %d", &srow,&scol);
	burn(forest,rows,cols,srow,scol);
	printf("\n");
	for(i=0;i<rows;i++)
	{
		for(j=0;j<cols;j++)
			printf("%d ", forest[i][j]);
		printf("\n");
	}
}
void burn(int forest[50][50],int rows,int cols,int srow,int scol)
{
	static count=0;
	count++;
	printf("%d",count);
	if(forest[srow][scol] == 1 && scol < cols && srow < rows)
	{
		forest[srow][scol] = 0;
		if(srow != rows-1)
			if(forest[srow+1][scol] == 1)
				burn(forest,rows,cols,srow+1,scol);
		if(srow != 0)
			if(forest[srow-1][scol] == 1)
				burn(forest,rows,cols,srow-1,scol);
		if(scol != cols-1)
			if(forest[srow][scol+1] == 1)
				burn(forest,rows,cols,srow,scol+1);
		if(scol != 0)
			if(forest[srow][scol-1] == 1)
			burn(forest,rows,cols,srow,scol-1);
	}
}
