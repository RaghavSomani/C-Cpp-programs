#include <iostream>
#include <cmath>
using namespace std;
int Add(int x, int y)
{
	while (y != 0)
	{
		int carry = x & y;
		x = x ^ y;
		y = carry << 1;
	}
	return x;
}
void bin(unsigned n)
{
	if (n>1)
		bin(n>>1);
	cout<<(n&1);
}
int snoob(int x)
{
	int y = x&-x;
	return (( ( (x^(x+y)) / y )>>2 )|(x+y));
}
void print_subsets(int a[], int n)
{
	for(int i = pow(2,n)-1;i>=0;i--)
	{
		int j =i, index = 0;
		while(j)
		{
			if(j&1)
				cout<<a[index]<<" ";
			j >>= 1;
			index++;
		}
		cout<<endl;
	}
}
int max(int x, int y)
{
	return x^((x^y)&-(x<y));
}
int min(int x, int y)
{
	return y^((x^y)&-(x<y));
}
int min2(int x, int y)
{
	int CHAR_BIT = 8;
	return y + ( (x - y)&((x - y)>>31) );
}
bool parity(int n)
{
	bool parity = false;
	while(n)
	{
		parity = !parity;
		n = n&(n-1);
	}
	return parity;
}
int strcmp(const char* s1, const char* s2)
{
	int i;
	for(i = 0;s1[i]&&s2[i];++i)
	{
		if(s1[i]==s2[i]||(s1[i]^32)==s2[i])
			continue;
		else
			break;
	}
	if(s1[i]==s2[i])
		return 0;
	if((s1[i]|32) < (s2[i]|32))
		return -1;
	return 1;
}
int count_bits(int n)
{
	int count = 0;
	while(n)
	{
		count ++;
		n >>= 1;
	}
	return count;
}
int count_total_bits(int n)
{
	if(n < 3)
		return n;
	int b = count_bits(n);
	int a = (1<<(b-2));
	int c = (a<<1);
	return ((b-1)*a + n-c+1 + count_total_bits(n-c));
}
int karatsuba(int x, int y)
{
	int b = max(count_bits(x),count_bits(y));
	if(b==0)
		return 0;
	if(b==1)
		return x&y;
	int l = b>>1, r = b-l;
	int p = (1<<r)-1;
	int xr = p&x, yr = p&y;
	int xl = x>>r, yl = y>>r;
	int c = karatsuba(xl,yl);
	int d = karatsuba(xr,yr);
	int e = karatsuba(xl+xr,yl+yr);
	return ( c*(1<<(r<<1)) + ((e-c-d)<<r) + d);
}
int next2power(int n)
{
	n--;
	n |= n>>1;
	n |= n>>2;
	n |= n>>4;
	n |= n>>8;
	n |= n>>16;
	return n+1;
}
int abs(int n)
{
	int mask = n>>31;
	return (mask+n)^mask;
}
int main()
{
	cout<<"15 + 32 = "<<Add(15,32)<<endl;
	int x = 156;
	cout<<x<<" = ";
	bin(156);
	int y = snoob(156);
	cout<<endl<<y<<" = ";
	bin(y);
	cout<<endl;
	int a[5] = {1,2,3};
	cout<<"subsets of 1, 2, 3"<<endl;
	print_subsets(a,3);
	cout<<"max of 24 and 22 : "<<max(24,22)<<endl;
	cout<<"max of 24 and 22 : "<<min(24,22)<<" "<<min2(24,22)<<endl;
	cout<<"parity of 7 = "<<parity(7)<<endl;
	cout<<"cat dog = "<<strcmp("cat","dog")<<endl;
	cout<<"CaT dOg = "<<strcmp("CaT","dOg")<<endl;
	cout<<"DOg caT = "<<strcmp("DOg","caT")<<endl;
	cout<<"ABCD z = "<<strcmp("ABCD","z")<<endl;
	cout<<"Z abCD = "<<strcmp("Z","abCD")<<endl;
	cout<<count_bits(42)<<endl;
	cout<<count_total_bits(7)<<endl;
	int d = karatsuba(7,10);
	cout<<d<<endl;
	cout<<next2power(8)<<endl;
	cout<<abs(-35)<<" "<<abs(35)<<endl;
	return 0;
}