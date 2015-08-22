#include <iostream>
#include <cmath>
#include <climits>
using namespace std;
double fa(double x)
{
	return x-pow(2,-x);
}
double fb(double x)
{
	return (exp(x)-(x*x)+(3*x)-2);
}
double fc(double x)
{
	return (x*cos(x)-2*x*x+3*x-1);
}
double bisectionMethod(double a, double b, int N, double e, double (*func)(double))
{
	int i=1;
	double p;
	double fa = func(a), fp;
	while(i<=N)
	{
		p = a + (b-a)*0.5;
		fp = func(p);
		if(fp==0 || (b-a)<2*e)
		{
			cout<<"a = "<<a<<" b = "<<b<<endl;
			return p;
		}
		if(fa*fp > 0)
		{
			a = p;
			fa = fp;
		}
		else
			b = p;
		i++;
	}
	cout<<"The method failed after "<<N<<" iterations\n";
	return -1;
}
int main()
{
	double result_a = bisectionMethod(0,1,INT_MAX,1e-5,&fa);
	cout<<"fa("<<result_a<<") = "<<fa(result_a)<<endl<<endl;
	double result_b = bisectionMethod(0,1,INT_MAX,1e-5,&fb);
	cout<<"fb("<<result_b<<") = "<<fb(result_b)<<endl<<endl;
	double result_c = bisectionMethod(0.2,0.3,INT_MAX,1e-5,&fc);
	cout<<"fc("<<result_c<<") = "<<fc(result_c)<<endl<<endl;
	result_c = bisectionMethod(1.2,1.3,INT_MAX,1e-5,&fc);
	cout<<"fc("<<result_c<<") = "<<fc(result_c)<<endl<<endl;
	return 0;
}