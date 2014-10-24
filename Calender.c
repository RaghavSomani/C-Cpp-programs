/*************************
Owner : Raghav Somani
Version : 1.0.0
**************************/
#include<stdio.h>
void main()
{
	int a[12]={0,3,3,6,1,4,6,2,5,0,3,5};
	char month[12][9]={"January","February","March","April","May","June","July","August","September","October","November","December"};
	int month_days[12]={31,28,31,30,31,30,31,31,30,31,30,31};
	char day[7][10]={"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};
	int d,m,y,i,j;
	printf("\n\n\t\t~~~~~~ Calender ~~~~~~\n\n");
	
	//Taking input
	
	printf("\tEnter date -\n");
	labelD : printf("\n\tDate             : ");
	scanf("%d",&d);
	if(d<1||d>31)
	{
		printf("\n\tEnter a valid date! Please correct.\n");
		goto labelD;
	}
	labelM : printf("\n\tMonth (1-12)     : ");
	scanf("%d",&m);
	if(m<1)
	{
		printf("\n\tMonth cannot be negative! Please correct.\n");
		goto labelM;
	}
	if(m>12)
	{
		printf("\n\tThere are just 12 months in a year! Please correct.\n");
		goto labelM;
	}
	labelY : printf("\n\tYear (1900-2100) : ");
	scanf("%d",&y);
	if(y<1900||y>2100)
	{
		printf("\n\tPlease enter a year in the given range!\n");
		goto labelY;
	}
	
	// Validating date
	
	if(d==29&&m==2&&y==1900)
	{
		printf("\n\t%d did not have 29th February! Please correct.\n",y);
		goto labelD;
	}
	
	if(m==1||m==3||m==5||m==7||m==8||m==10||m==12)
		label1 : if(d>31||d<1)
		{
			printf("\n\t%s has 31 days! Please correct.\n", month[m-1]);
			printf("\n\tDate : ");
			scanf("%d",&d);
			goto label1;
		}			
	if(m==2)
	{
		label2 : if(y%4!=0&&(d>28||d<1))
		{
			printf("\n\t%s has 28 days in this year! Please correct.\n", month[m-1]);
			printf("\n\tDate : ");
			scanf("%d",&d);
			goto label2;
		}
		label3 : if((y%4==0)&&(d>29||d<1))
		{
			printf("\n\t%s has 29 days in this year! Please correct.\n", month[m-1]);
			printf("\n\tDate : ");
			scanf("%d",&d);
			goto label3;
		}
		if(y%4==0&&y!=1900)
			month_days[1]=29;
	}
	if(m==4||m==6||m==9||m==11)
		label4 : if(d>30||d<1)
		{
			printf("\n\t%s has 30 days! Please correct.\n", month[m-1]);
			printf("\n\tDate : ");
			scanf("%d",&d);
			goto label4;
		}
	
	//The real magic here ;)
	
	int index;
	int first_day=0;
	int leap=0,leap1=0,leap2=0;
	leap1=(y-1900-1)/4;
	for(i=(1900+leap1*4+1);i<y;i++)
		if(i%4==0)
			leap2++;
	if(y%4==0&&m>2)
		if(y%100!=0||y%400==0)
			leap2++;
	leap=leap1+leap2;
	int y_diff=y-1900;
	index = (y_diff+a[m-1]+first_day+leap+d)%7;
	printf("\n\t  The day is %s\n",day[index]);
	int index_month = (y_diff+a[m-1]+first_day+leap+1)%7;
	int month_cal[5][7];
	for(i=0;i<5;i++)
		for(j=0;j<7;j++)
			month_cal[i][j]=0;
	j=1;
	for(i=0;i<35;i++)
	{
		if(i>=index_month&&i<=index_month+month_days[m-1]-1)
		{
			month_cal[i/7][i%7]=j;
			j++;
		}
	}
	printf("\n\n");
	printf("\t\t%s  %d\n\n",month[m-1],y);
	printf("\t|  S  M  T  W  T  F  S |\n");
	for(i=0;i<5;i++)
	{
		printf("\t| ");
		for(j=0;j<7;j++)
		{
			if(month_cal[i][j]>0)
			{
				if(month_cal[i][j]<10)
					printf(" %d ",month_cal[i][j]);
				else
					printf("%d ",month_cal[i][j]);
			}
			else
				printf("   ");
		}
		printf("|\n");
	}
}
