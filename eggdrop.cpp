#include <iostream>
#include <climits>
using namespace std;

// n eggs k floors
int eggDrop(int n, int k)
{
	int eggFloor[n+1][k+1], res;
	for(int i=0;i<=n;i++)
	{
		eggFloor[i][0] = 0;
		eggFloor[i][1] = 1;
	}
	for(int i=0;i<=k;i++)
		eggFloor[1][i] = i;
	for(int i=2;i<=n;i++)
		for(int j=2;j<=k;j++)
		{
			eggFloor[i][j] = INT_MAX;
			for(int x=1;x<=j;x++)
			{
				res = 1 + max(eggFloor[i-1][x-1],eggFloor[i][j-x]);
				if(res<eggFloor[i][j])
					eggFloor[i][j] = res;
			}

		}
	return eggFloor[n][k];
}
int main()
{
	int n = 2, k = 36;
	cout<<"n = "<<n<<" k = "<<k<<" min number of trials in worst case = "<<eggDrop(n,k);
	return 0;
}