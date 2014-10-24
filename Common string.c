#include<stdio.h>
#include<string.h>
#include<stdlib.h>
char* common(char* a,char* b);
char* cs(char* a,char* b);
void main()
{
	int n,i,j=0,k;
	scanf("%d", &n);
	char c[n][100];
	for(i=0;i<n;i++)
		scanf("%s",c[i]);
	char* next=NULL;
	char* temp=NULL;
	next = cs(c[0],c[1]);
	for(i=1;i<n-1;i++)
	{
		temp = cs(c[i+1],next);
		free(next);
		next = temp;
	}
	printf("%d",strlen(next));
	free(next);
}
//char* common(char* a,char* b)
//{
//	int i,j,k=0,len1=strlen(a),len2=strlen(b),max=(len1>=len2)?len1:len2,flag[len2];
//	char c[max];
//	for(i=0;i<max;i++)
//		c[i]='\0';
//	for(i=0;i<len2;i++)
//		flag[i]=0;
//	for(i=0;i<len1;i++)
//	{
//		for(j=0;j<len2;j++)
//		{
//			if(b[j]==a[i])
//				flag[j]=1;
//		}
//	}
//	for(i=0;i<len2;i++)
//	{
//		if(flag[i]==1)
//		{
//			c[k]=b[i];
//			k++;
//		}
//	}
//	c[k]='\0';
//	int len=strlen(c);
//	for(i=0;i<len;i++)
//	{
//		for(j=i+1;j<len;j++)
//		{
//			if(c[i]==c[j])
//				c[j]=' ';
//		}
//	}
//	k=0;
//	char* ch = (char*)malloc(max*sizeof(char));
//	for(i=0;i<len;i++)
//	{
//		if(c[i]!=' ')
//		{
//			ch[k]=c[i];
//			k++;
//		}
//	}
//	ch[k]='\0';
//	return ch;
//}
char* cs(char* a,char* b)
{
	int x[26],y[26],len1=strlen(a),len2=strlen(b),i,j,k=0;
	for(i=0;i<26;i++)
	{
		x[i]=0;
		y[i]=0;
	}
	for(i=0;i<len1;i++)
		x[a[i]-97]=1;
	for(i=0;i<len2;i++)
		y[b[i]-97]=1;
	char *ch = (char*)malloc(26*sizeof(char));
	for(i=0;i<26;i++)
	{
		if(x[i]==1&&y[i]==1)
		{
			ch[k]=i+97;
			k++;
		}
	}
	ch[k]='\0';
	return ch;
}
