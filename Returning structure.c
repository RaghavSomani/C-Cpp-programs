#include<stdio.h>
#include<string.h>
struct student function(void);
struct student
{
	int roll;
	int year;
	char* name;
};	
void main()
{
	struct student raghav;
	raghav=function();
	printf("%d %d %s\n",raghav.roll,raghav.year,raghav.name);
}
struct student function(void)
{
	struct student dummy;
	dummy.roll=3029;
	dummy.year=2;
	dummy.name = "Raghav";
	return dummy;
}
