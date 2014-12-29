#include <sys/time.h>
#include<iostream>
int main()
{
	struct timeval  tv1, tv2;
	gettimeofday(&tv1, NULL);
	for(int i=0;i<10000;i++)
		for(int j=0;j<10000;j++)
			for(int k=0;k<3;k++);
	gettimeofday(&tv2, NULL);
	printf("Time taken in execution = %f seconds\n",(double) (tv2.tv_usec - tv1.tv_usec) / 1000000 +(double) (tv2.tv_sec - tv1.tv_sec));
}
