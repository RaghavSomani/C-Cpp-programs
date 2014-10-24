#include<iostream>
#include<cstring>
void lcs(char* s1, char* s2);
using namespace std;
int main()
{
	char s1[100],s2[100];
	gets(s1);
	gets(s2);
	lcs(s1,s2);
}
void lcs(char* s1, char* s2)
{
	int len1=strlen(s1);
	int len2=strlen(s2);
	int a[len1+1][len2+1],i,j;
	for(i=0;i<len1+1;i++)
		a[i][0]=0;
	for(j=0;j<len2+1;j++)
		a[0][j]=0;
	for(i=1;i<len1+1;i++)
	{
		for(j=1;j<len2+1;j++)
		{
			if(s1[i-1]!=s2[j-1])
				a[i][j]=(a[i-1][j]>=a[i][j-1])?a[i-1][j]:a[i][j-1];
			else
				a[i][j]=(1+a[i-1][j-1]);
			//cout<<a[i][j]<<" ";
		}
		//cout<<endl;
	}
	int len=a[len1][len2];
	cout<<endl<<len<<endl;
	char lcs[len+1];
	int k=len;
	lcs[k]='\0';
	i=len1;
	j=len2;
	while(i>0&&j>0)		// it prints just one of the all possible LCS of the 2 stings
	{
		if(s1[i-1]==s2[j-1])
		{
			lcs[k-1]=s1[i-1];
			k--;
			i--;
			j--;
		}
		else if(a[i-1][j]>=a[i][j-1])
			i--;
		else
			j--;
	}
	puts(lcs);
}
