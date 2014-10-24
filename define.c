#include <stdio.h>
#define square(x) x*x
#define MAX(x,y) (x>y)?x:y
#define swap(x,y){			\
					x^=y;	\
					y^=x;	\
					x^=y;	\
				}
#define TEST(a,b) printf("The value of " #a " = " #b " \n", a)


short int countbit(unsigned int n)
{
	short int bits = 0;
	while(n)
	{
		if (n & 1)
			bits++;
        n>>=1;
    }
    return bits;
}
int main()
{
	printf("%d\n",square(4));
	printf("%d\n",MAX(3,4));
	unsigned short int a=187,b=725;
	swap(a,b);
	printf("a=%d\nb=%d\n",a,b);
	TEST(a,%d);
	printf("%d\n",countbit(5));
}