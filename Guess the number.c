#include<stdio.h>
int bs(int, int);
void main()
{
	char c;
	int i=1, min,max;
	do
	{
		label: printf("\nIs the number greater than or equal to %d ?? (Y/N) :", i*i);
		scanf("\n%c", &c);
		i++;
	}while(c=='y'||c=='Y');
	if(c!='n'&&c!='N')
	{
		printf("Wrong Entry !!\n");
		i--;
		goto label;
	}
	min=(i-2)*(i-2);
	max=(i-1)*(i-1)-1;
	printf("The number is %d !!",bs(min,max));
}
int bs(int min, int max)
{
	char c;
	if((max-min)>1)
	{
		label1: printf("\nIs the number greater than or equal to %d ?? (Y/N) :", (max+min)/2);
		scanf("\n%c", &c);
		if(c=='y'||c=='Y')
			bs((max+min)/2, max);
		else if(c=='n'||c=='N')
			bs(min, (max+min)/2-1);
		else
		{
			printf("Wrong Entry !!\n");
			goto label1;
		}
	}
	else if((max-min)==1)
	{
		label2: printf("\nIs the number greater or than equal to %d ?? (Y/N) :", max);
		scanf("\n%c", &c);
		if(c=='y'||c=='Y')
			return max;
		else if(c=='n'||c=='N')
			return min;
		else
		{
			printf("Wrong Entry !!\n");
			goto label2;
		}
	}
	else if(max==min)
		return max;
}
