
/*Created by : Raghav Somani
Version      : 1.5.4
Last modified on 13/05/2014*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<string.h>
#include<ctype.h>
void print(char [30][50]);
void move();
void main()
{
	system("color F0");													//changes screen color to white and text color to black
	char a[30][50];
	int i,j,len=4,x,score=0,lives=3;
	printf("\n\n\t\t\t\tWelcome to Snakes!");
	Sleep(2000);
	printf("\n\n\n\t\t\t\tLoading...\n\t\t\t\t");
	for(i=0;i<10;i++)
	{
		Sleep(500);
		printf("%c", 177);
	}
	printf("\n\n\t\t\t\tGet Ready!!");
	Sleep(1000);
	for(i=0;i<30;i++)
		for(j=0;j<50;j++)
			a[i][j]=' ';
	struct end															//structure for head and tail coordinates
	{
		int i;
		int j;
	}head,tail,food[50];
	head.i=0;															//initializing head and tail coordinates
	head.j=3;
	tail.i=0;
	tail.j=0;
	char c=77;
	int ij[2][50],temp[2][50];
	for(i=0;i<2;i++)
		for(j=0;j<50;j++)
		{
			ij[i][j]='\0';
			temp[i][j]='\0';	
		}
	srand(time(NULL));													//helps generating different random numbers on every compilation
	for(x=0;x<50;x++)													//generates random positions for food in a structure array
	{
		food[x].i=rand()%30;
		food[x].j=rand()%50;
	}
	ij[0][0]=0;															//initializing snake position
	ij[1][0]=0;
	ij[0][1]=0;
	ij[1][1]=1;
	ij[0][2]=0;
	ij[1][2]=2;
	ij[0][3]=0;
	ij[1][3]=3;
	x=0;
	while(lives>=0)														//loop which runs only when lives >=0
	{
		if(!(head.i>=0&&head.j>=0&&head.i<30&&head.j<50))
		{
			lives--;
			Beep(1000,500);
			for(i=0;i<2;i++)
				for(j=0;j<50;j++)
				{
					ij[i][j]='\0';
					temp[i][j]='\0';	
				}
			len=4;
			ij[0][0]=0;													//initializing snake position
			ij[1][0]=0;
			ij[0][1]=0;
			ij[1][1]=1;
			ij[0][2]=0;
			ij[1][2]=2;
			ij[0][3]=0;
			ij[1][3]=3;
			head.i=ij[0][3];
			head.j=ij[1][3];
			for(i=0;i<len-1;i++)
				a[ij[0][i]][ij[1][i]]='*';
			c=77;
			if(c==75)
				a[head.i][head.j]='<';
			else if(c==80)
				a[head.i][head.j]='v';
			else if(c==77)
				a[head.i][head.j]='>';
			else if(c==72)
				a[head.i][head.j]='^';
			continue;
		}
		system("cls");													//clear screen each time
		for(i=0;i<len;i++)
			for(j=0;j<2;j++)
				temp[j][i]=ij[j][i];
		if(head.i==food[x].i&&head.j==food[x].j)						//if snake hits the food
		{
			Beep(500, 500);												//plays sound when snake eats the food
			len++;
			a[food[x].i][food[x].j]='*';								//food goes inside the snake and changes its sign from # to *
			if(c==77)													//if statements for increasing the snake size
			{
				ij[0][len-1]=ij[0][len-2];
				ij[1][len-1]=head.j;
			}
			else if(c==75)
			{
				ij[0][len-1]=ij[0][len-2];
				ij[1][len-1]=head.j;
			}
			else if(c==72)
			{
				ij[0][len-1]=head.i;
				ij[1][len-1]=ij[1][len-2];
			}
			else if(c==80)
			{
				ij[0][len-1]=head.i;
				ij[1][len-1]=ij[1][len-2];
			}
			head.i=ij[0][len-1];
			head.j=ij[1][len-1];
			x++;
		}
		for(i=0;i<len-1;i++)
			a[ij[0][i]][ij[1][i]]='*';
		if(c==75)
			a[head.i][head.j]='<';
		else if(c==80)
			a[head.i][head.j]='v';
		else if(c==77)
			a[head.i][head.j]='>';
		else if(c==72)
			a[head.i][head.j]='^';
		a[food[x].i][food[x].j]='#';									//places new food after snakes eats one after since x gets incremented
		printf("\n\n");
		score=10*x;
		printf("\n\t\tScore: %d\t\t\t\t", score);						//prints score as 10 x number of food eaten
		printf("  Lives : %d\n\n", lives);
		print(a);														//prints the arena
		c=getch();														//takes direction from player
		if(c==72)														//moving up
		{
			head.i--;
			if(a[head.i][head.j]=='*')
			{
				lives--;
				Beep(1000,500);
			}															//dies if snake eats itself
			for(i=0;i<len-1;i++)
			{
				ij[0][i]=ij[0][i+1];
				ij[1][i]=ij[1][i+1];
			}
			ij[0][len-1]=head.i;
			tail.i=ij[0][0];
			tail.j=ij[1][0];
		}
		else if(c==75)													//moving left
		{
			head.j--;
			if(a[head.i][head.j]=='*')									//dies if snake eats itself
			{
				lives--;
				Beep(1000,500);
			}
			for(i=0;i<len-1;i++)
			{
				ij[0][i]=ij[0][i+1];
				ij[1][i]=ij[1][i+1];
			}
			ij[1][len-1]=head.j;
			tail.i=ij[0][0];
			tail.j=ij[1][0];
		}
		else if(c==80)													//moving down
		{
			head.i++;
			if(a[head.i][head.j]=='*')									//dies if snake eats itself
			{
				lives--;
				Beep(1000,500);
			}
			for(i=0;i<len-1;i++)
			{
				ij[0][i]=ij[0][i+1];
				ij[1][i]=ij[1][i+1];
			}
			ij[0][len-1]=head.i;
			tail.i=ij[0][0];
			tail.j=ij[1][0];
		}
		else if(c==77)													//moving right
		{	
			head.j++;
			if(a[head.i][head.j]=='*')									//dies if snake eats itself
			{
				lives--;
				Beep(1000,500);
			}
			for(i=0;i<len-1;i++)
			{
				ij[0][i]=ij[0][i+1];
				ij[1][i]=ij[1][i+1];
			}
			ij[1][len-1]=head.j;
			tail.i=ij[0][0];
			tail.j=ij[1][0];
		}
		for(i=0;i<len;i++)
			a[temp[0][i]][temp[1][i]]=' ';
	}
	system("cls");
	printf("\n\n\t\t\tBetter Luck next time!\n\n\t\t\tYour Score: %d\n\n", score);
	printf("\n\n\t\t\tEnter your Name : ");
	char name[20],NAME[20];
	gets(name);
	for(i=0;i<strlen(name);i++)
		NAME[i]=toupper(name[i]);
	time_t mytime=time(NULL);
	FILE *fp;
	fp=fopen("record.txt","a+");
	fprintf(fp,"Player Name : %s\n",NAME);
	fprintf(fp,"Score : %d\n", score);
	fprintf(fp,"Played Date : %s\n",ctime(&mytime));
	fclose(fp);
	printf("\n\n\t\t\tWanna see your previous scores ?! (Y/N) : ");
	char ch;
	scanf("\n%c", &ch);
	if(ch=='y')
	{
		fp=fopen("record.txt","r");
		char b;
		fscanf(fp,"%c",&b);
		do
		{
			putchar(b=getc(fp));
    	}while(b!=EOF);
		fclose(fp);
	}
	printf("\n\n\t\t\t\tThank You!!\n\n\n\n\n");
}
void print(char a[30][50])												//function to print the arena
{
	int i,j;
	printf("\t\t");
	for(i=0;i<52;i++)
		printf("@");
	printf("\n");
	for(i=0;i<30;i++)
	{
		printf("\t\t@");
		for(j=0;j<50;j++)
			printf("%c", a[i][j]);
		printf("@\n");
	}
	printf("\t\t");
	for(i=0;i<52;i++)
		printf("@");
	printf("\n");
}
