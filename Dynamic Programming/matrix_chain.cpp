#include <iostream>
#include <fstream>
#include <climits>
using namespace std;
void PrintChain(int** s, int i, int j);
int main()
{
	int n;
	ifstream fp("mat_input.txt");
	cout<<"Number of matrices : ";
	fp>>n;
	int p[n+1];
	cout<<"Dimensions of matrices : ";
	for(int i=0;i<=n;i++)
		fp>>p[i];
	int m[n+1][n+1];
	int* s[n];
	for(int i=1;i<=n;i++)
		s[i]=new int[n+1];
	int j,y;
	for(int i=1;i<=n;i++)
		m[i][i]=0;
	for(int l=2;l<=n;l++)
		for(int i=1;i<=n-l+1;i++)
		{
			j=i+l-1;
			m[i][j]=INT_MAX;
			for(int k=i;k<=j-1;k++)
			{
				y=m[i][k]+m[k+1][j]+p[i-1]*p[k]*p[j];
				if(y<m[i][j])
				{
					m[i][j]=y;
					s[i][j]=k;
				}
			}
		}
	cout<<endl;
	PrintChain(s,1,n);
	cout<<"\nMinimum scalar multiplication cost : "<<m[1][n];
	for(int i=1;i<=n;i++)
		delete [] s[i];
	return 0;
}
void PrintChain(int** s, int i, int j)
{
	if(i==j)
		cout<<"A"<<i;
	else
	{
		cout<<"(";
		PrintChain(s,i,s[i][j]);
		PrintChain(s,s[i][j]+1,j);
		cout<<")";
	}
}