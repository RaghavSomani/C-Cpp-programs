#include<stdio.h>
#include<string.h>
void main()
{
	printf("Enter an expression: ");
	char c[50], stack[50];
	gets(c);
	int i,j=0;
	for(i=0;i<50;i++)
		stack[i]='\0';
	int n=strlen(c);
	for(i=0;i<n;i++)
	{
		if(c[i]=='('||c[i]==')'||c[i]=='{'||c[i]=='}'||c[i]=='['||c[i]==']')
		{
			stack[j]=c[i];
			j++;
			if((stack[j-2]=='('&&stack[j-1]==')')||(stack[j-2]=='{'&&stack[j-1]=='}')||(stack[j-2]=='['&&stack[j-1]==']'))
			{
				stack[j]='\0';
				stack[j-1]='\0';
				j=j-2;
			}
		}
	}
	if(j==0)
		printf("Expression is correct!");
	else
		printf("Incorrect Expression");
}
