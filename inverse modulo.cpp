#include<iostream>
using namespace std;
void inv(int a, int n)
{
	if(n==0||a==0)
	{
		cout<<"Inverse does not exist";
		return;
	}
	int x[3],y[3];
	x[0]=a;
	x[1]=n;
	y[0]=1;
	y[1]=0;
	while(x[1])
	{
		y[2]=y[0]-(y[1]*(x[0]/x[1]));			//http://www.cs.hunter.cuny.edu/~saad/courses/dm/notes/note7.pdf
		y[0]=y[1];								//http://web.stanford.edu/class/cs97si/02-mathematics.pdf
		y[1]=y[2];
		x[2]=x[0]%x[1];
		x[0]=x[1];
		x[1]=x[2];
	}
	if(x[0]==1)
		cout<<((y[0]>=0)?y[0]:(n+y[0]));
	else
		cout<<"Inverse does not exist";
}
int main()
{
	int a,n;
	cout<<"Inverse of : ";
	cin>>a;
	cout<<"mod : ";
	cin>>n;
	inv(a,n);
	return 0;
}
