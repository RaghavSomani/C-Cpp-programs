#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int* convert(char* c);
void main()
{
	int i=0;
	char c[100];
	gets(c);
	int len=strlen(c);
	int *a=convert(c);
	for(i=0;i<len;i++)
		printf("%d",a[i]);
	free(a);
}
int* convert(char* c)
{
	int len=strlen(c),i;
	int *a=(int*)malloc(len*sizeof(int));
	for(i=0;i<len;i++)
		a[i]=c[i]-48;
	return a;
}
