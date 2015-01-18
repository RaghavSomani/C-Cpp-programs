#include<iostream>
#include<sys/time.h>
#include<limits.h>
#include <windows.h>
#include "sorting.h"
using namespace std;
int main()
{
	LARGE_INTEGER start, end, freq;
	srand(time(NULL));
	int n=10;
	
	//opening .dat files for storing data to plot
	FILE* fpis;
	FILE* fpms;
	FILE* fpqs;
	FILE* fprqs;
	FILE* fphs;
	FILE* fpbs;
	FILE* fpmms;
	FILE* fpmrqs;
	
	fpis=fopen("insertion.dat","w");
	fpms=fopen("merge.dat","w");
	fpqs=fopen("quick.dat","w");
	fprqs=fopen("randomquick.dat","w");
	fphs=fopen("heap.dat","w");
	fpmms=fopen("mixedmerge.dat","w");
	fpmrqs=fopen("mixedrandomquick.dat","w");
	
	while(n<=300)
	{
		//cout<<"Size of array : ";
		//cin>>n;
		int is[n],ms[n],qs[n],rqs[n],hs[n],mms[n],mqs[n];
		float bs[n];
		for(int i=0;i<n;i++)
		{
			is[i]=rand();			// rand() for random, i for sorted, n-i for reverse sorted, rand()%100+i for nearly sorted
			ms[i]=is[i];
			qs[i]=is[i];
			rqs[i]=is[i];
			hs[i]=is[i];
			mms[i]=is[i];
			mqs[i]=is[i];
		}
		
		//calculating and storing insertion sort analysis in insertion.dat
		QueryPerformanceFrequency(&freq);
		QueryPerformanceCounter(&start);
		insertion_sort(is,0,n-1);
		QueryPerformanceCounter(&end);
		if(n>0)
			fprintf(fpis,"%d %lld\n",n,((end.QuadPart - start.QuadPart)*1000000/freq.QuadPart));
		
		//calculating and storing merge sort analysis in merge.dat	
		QueryPerformanceFrequency(&freq);
		QueryPerformanceCounter(&start);
		merge_sort(ms,0,n-1);
		QueryPerformanceCounter(&end);
		if(n>0)
			fprintf(fpms,"%d %lld\n",n,((end.QuadPart - start.QuadPart)*1000000/freq.QuadPart));
		
		//calculating and storing quick sort analysis in quick.dat
		QueryPerformanceFrequency(&freq);
		QueryPerformanceCounter(&start);
		quick_sort(qs,0,n-1);
		QueryPerformanceCounter(&end);
		if(n>0)
			fprintf(fpqs,"%d %lld\n",n,((end.QuadPart - start.QuadPart)*1000000/freq.QuadPart));
		
		//calculating and storing randlomized sort analysis in randomquick.dat	
		QueryPerformanceFrequency(&freq);
		QueryPerformanceCounter(&start);
		randomized_quick_sort(rqs,0,n-1);
		QueryPerformanceCounter(&end);
		if(n>0)
			fprintf(fprqs,"%d %lld\n",n,((end.QuadPart - start.QuadPart)*1000000/freq.QuadPart));
		
		//calculating and storing heap sort analysis in heap.dat
		QueryPerformanceFrequency(&freq);
		QueryPerformanceCounter(&start);
		heap_sort(hs,n);
		QueryPerformanceCounter(&end);
		if(n>0)
			fprintf(fphs,"%d %lld\n",n,((end.QuadPart - start.QuadPart)*1000000/freq.QuadPart));
		
		//calculating and storing mixed merge sort analysis in mixedmerge.dat
		QueryPerformanceFrequency(&freq);
		QueryPerformanceCounter(&start);
		mixed_merge_sort(mms,0,n-1);
		QueryPerformanceCounter(&end);
		if(n>0)
			fprintf(fpmms,"%d %lld\n",n,((end.QuadPart - start.QuadPart)*1000000/freq.QuadPart));
		
		//calculating and storing mixed quick sort analysis in mixedrandomquick.dat
		QueryPerformanceFrequency(&freq);
		QueryPerformanceCounter(&start);
		mixed_quick_sort(mqs,0,n-1);
		QueryPerformanceCounter(&end);
		if(n>0)
			fprintf(fpmrqs,"%d %lld\n",n,((end.QuadPart - start.QuadPart)*1000000/freq.QuadPart));
		
		n=n+10;		//increasing n for next sorting round
	}
	
	//closing .dat files
	fclose(fpis);
	fclose(fpms);
	fclose(fpqs);
	fclose(fprqs);
	fclose(fphs);
	fclose(fpmms);
	fclose(fpmrqs);
}
