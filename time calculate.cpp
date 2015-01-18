#include <iostream>
#include <windows.h>
using namespace std;
void some_operation() // Some arbitrary function that takes time.
{
	for(int i=0;i<1000;i++);
}

int main()
{
  	LARGE_INTEGER start, end, freq;
   
  	QueryPerformanceFrequency(&freq);
  	QueryPerformanceCounter(&start); 
	some_operation();
	QueryPerformanceCounter(&end);
    
	cout<<"The resolution of timer : "<<freq.QuadPart<<" Hz."<<endl;
	cout<<"Time taken : "<<(end.QuadPart - start.QuadPart)*1000000/freq.QuadPart<<" microSeconds"<<endl;
}
