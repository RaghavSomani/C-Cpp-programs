#include <iostream>
using namespace std;
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n,m;
		cin>>n>>m;
		int a[n][m];
		for(int i=0;i<n;++i)
			for (int j=0;j<m;++j)
				cin>>a[i][j];
		int g[n][m];
		for(int i=0;i<n;++i)
			g[i][m-1]=a[i][m-1];
		for(int i=0;i<n;i++)
			for(int j=m-2;j>=0;j--)
			{
				if(a[i][j]<=g[i][j+1])
					g[i][j]=a[i][j]-1;
				else
					g[i][j]=a[i][j];
			}
		int ans=0;
		for(int i=0;i<n;i++)
			ans=ans^g[i][0];
		if(ans!=0)
			cout<<"FIRST"<<endl;
		else
			cout<<"SECOND"<<endl;
	}
	return 0;
}