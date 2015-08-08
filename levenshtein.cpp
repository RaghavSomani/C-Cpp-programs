#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
unsigned short levenshtein(string s, string t);
int main(int argc, char** argv)
{
	if(argc==3)
		cout<<"\nLevenshtein distance ("<<argv[1]<<","<<argv[2]<<") "<<": "<<levenshtein(argv[1],argv[2])<<"\n";
	else
		cout<<"\nNo inputs given\nTry :a word1 word2\n";
	return 0;
}
unsigned short levenshtein(string s, string t)
{
	transform(s.begin(), s.end(), s.begin(), ::tolower);
	transform(t.begin(), t.end(), t.begin(), ::tolower);
	unsigned short m = s.length();
	unsigned short n = t.length();
	unsigned short d[m+1][n+1], min;
	d[0][0]=0;
	for(short i=1;i<=n;i++)
		d[0][i]=i;
	for(short i=1;i<=m;i++)
		d[i][0]=i;
	for(short i=1;i<=m;i++)
	{
		for(short j=1;j<=n;j++)
		{
			if(s[i-1]==t[j-1])
				d[i][j]=d[i-1][j-1];
			else
			{
				min = (d[i-1][j]<d[i][j-1])?d[i-1][j]:d[i][j-1];
				d[i][j] = (min<d[i-1][j-1])?(min+1):(d[i-1][j-1]+1);
			}
		}
	}
	return d[m][n];
}