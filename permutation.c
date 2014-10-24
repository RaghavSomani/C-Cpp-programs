#include<stdio.h>
#include<string.h>
void permute(char [],int ,int);
void main()
{
	int length;
	char word[20];
	printf("Enter the word: ");
	scanf("%s",word);
	length=strlen(word);
	permute(word,0,length);	
}
void permute(char word[],int start,int length)
{
	char temp,c[length];
	int i;
	for(i=0;i<length;i++)
		c[i]=word[i];
	if(start<length-1)
		for(i=start;i<length;i++)
		{	
			if(i==start||c[i]!=c[start])
			{
				temp=c[start];
				c[start]=c[i];
				c[i]=temp;
				permute(c,start+1,length);
			}
		}
	else
		printf("%s\n",c);
}
