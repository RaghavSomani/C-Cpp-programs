#include<stdio.h>
#include<time.h>
//#include<stdlib.h>
#include<string.h>
void print(int [4][4]);
int digit(int);
void main()
{
	system("color F0");
	int a[4][4],i,j,flag,pole,score=0,rod1=0,rod2=0;
	char c;
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
			a[i][j]=0;
	srand(time(NULL));
	int number[10]={2,2,2,2,2,2,2,2,2,4};
	int tempi1=rand()%4;
	int tempj1=rand()%4;
	int tempi2=rand()%4;
	int tempj2=rand()%4;
	a[tempi1][tempj1]=number[rand()%10];
	a[tempi2][tempj2]=number[rand()%10];
	printf("\n\t\tScore : %d\n", score);
	print(a);
	printf("\n");
	i=rand()%4;
	j=rand()%4;
	do
	{
		c=getch();
		c=getch();
		int k=0;
		rod1=0;
		rod2=0;
		if(c==72)
		{
			for(i=0;i<4;i++)
				for(j=0;j<4;j++)
				{
					if(a[i][j]!=0)
					{
						k=i;
						while(k>0&&a[k-1][j]==0)
						{
							a[k-1][j]=a[k][j];
							a[k][j]=0;
							k--;
							rod1=1;
						}
					}
					if(k!=0)
						if(a[k][j]==a[k-1][j])
						{
							a[k-1][j]=a[k-1][j]*2;
							score=score+a[k-1][j];
							a[k][j]=0;
							rod2=1;
						}
				}				
		}
		else if(c==75)
		{
			for(i=0;i<4;i++)
				for(j=0;j<4;j++)
				{
					if(a[i][j]!=0)
					{
						k=j;
						while(k>0&&a[i][k-1]==0)
						{
							a[i][k-1]=a[i][k];
							a[i][k]=0;
							k--;
							rod1=1;
						}
					}
					if(k!=0)
						if(a[i][k]==a[i][k-1])
						{
							a[i][k-1]=a[i][k-1]*2;
							score=score+a[i][k-1];
							a[i][k]=0;
							rod2=1;
						}
				}
		}
		else if(c==77)
		{
			for(i=0;i<4;i++)
				for(j=3;j>=0;j--)
				{
					if(a[i][j]!=0)
					{
						k=j;
						while(k<3&&a[i][k+1]==0)
						{
							a[i][k+1]=a[i][k];
							a[i][k]=0;
							k++;
							rod1=1;
						}
					}
					if(k!=3)
						if(a[i][k]==a[i][k+1])
						{
							a[i][k+1]=a[i][k+1]*2;
							score=score+a[i][k+1];
							a[i][k]=0;
							rod2=1;
						}
				}
		}
		else if(c==80)
		{
			for(i=3;i>=0;i--)
				for(j=0;j<4;j++)
				{
					if(a[i][j]!=0)
					{
						k=i;
						while(k<3&&a[k+1][j]==0)
						{
							a[k+1][j]=a[k][j];
							a[k][j]=0;
							k++;
							rod1=1;
						}
					}
					if(k!=3)
						if(a[k][j]==a[k+1][j])
						{
							a[k+1][j]=a[k+1][j]*2;
							score=score+a[k+1][j];
							a[k][j]=0;
							rod2=1;
						}
				}
		}
		flag=0;
		for(i=0;i<4;i++)
			for(j=0;j<4;j++)
				if(a[i][j]==0)
					flag=1;
		pole=1;
		if(flag==0)
		{
			pole=0;
			for(i=0;i<3;i++)
				for(j=0;j<4;j++)
					if(a[i][j]==a[i+1][j])
						pole=1;
			for(i=0;i<4;i++)
				for(j=0;j<3;j++)
					if(a[i][j]==a[i][j+1])
						pole=1;
		}
		if(flag==1&&(rod1==1||rod2==1))
		{
			while(a[i][j]!=0)
			{
				i=rand()%4;
				j=rand()%4;
			}
			if(a[i][j]==0)
				a[i][j]=number[rand()%5];
		}
		system("cls");
		printf("\n\t\tScore : %d\n", score);
		print(a);
		printf("\n");
	}while(flag!=0||pole!=0);
	printf("\nGame Over!!");
}
void print(int a[4][4])
{
	int i,j,k,max=a[0][0];
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
			if(a[i][j]>max)
				max=a[i][j];
	int big=digit(max);
	printf("\n\n");
	for(i=0;i<4;i++)
	{
		printf("\t|");
		for(j=0;j<4;j++)
		{
			if(a[i][j]!=0)
			{
				printf(" ");
				for(k=0;k<big-digit(a[i][j]);k++)
					printf(" ");
				printf("%d  |", a[i][j]);
			}
			else
			{
				printf(" ");
				for(k=0;k<big-digit(a[i][j]);k++)
					printf(" ");
				printf("  |");
			}
		}
		printf("\n\n");
	}
}
int digit(int number)
{
	int count=0;
	while(number>0)
	{
		count++;
		number=number/10;
	}
	return count;
}