/*	http://codeforces.com/blog/entry/15643  */
/*  use c++11 to compile 
	for terminal use
	g++ -std=c++11 file.cpp
	to compile
	for IDEs like Dev C++ make sure to make 
	Compiler Option -> Settings -> Code Generation -> Language Standard to ISO C++11  */

#include <iostream>
#include <vector>
#include <deque>
#include <set>
#include <list>
#include <array>
#include <tuple>
#include <algorithm>
#include <string>
//#include <bits/stdc++.h>		//use this to replace all the above header files! You might observe a small inc in compile time
#define what_is(x) cerr<<#x<<" is "<<x<<endl;
using namespace std;
int main()
{
	//http://www.cplusplus.com/reference/utility/pair/
	pair<int,int> p;													//declare a pair of type (int,int)
	p=make_pair(3,4);													//make a pair using make_pair
	cout<<"Pair <int,int> : "<<p.first<<","<<p.second<<endl<<endl;		//print a pair using first and second
	
	p={5,6};															//make a pair without using make_pair which is easier
	cout<<"Pair <int,int> : "<<p.first<<","<<p.second<<endl<<endl;		//print the new pair
	
	pair<char,pair<int,int>> p1;														//declare a pair of (char,(int,int))
	p1={'a',{2,3}};																		//make a pair of the above type
	cout<<"Pair <char,pair<int,int>> : ";
	cout<<p1.first<<","<<p1.second.first<<" "<<p1.second.second<<endl<<endl;			//print the (char,(int,int)) type pair
	
	//http://www.cplusplus.com/reference/vector/vector/
	vector<int> v;							//declare a vector(dynamic array)
	v={4,5};								//initialize a vector
	cout<<"Vector <int> : ";
	for (vector<int>::iterator i=v.begin();i!=end(v);++i)	//iterator method for vectors begin/end(x) and v.begin/end() are same
		cout<<*i<<" ";										//iterator is dereferenced for accessing value
	cout<<endl;
	
	v.push_back(2);							//add elements in the vector
	v.push_back(3);							//using push_back
	for(auto &i:v)							//change values using auto
		i*=i;
	cout<<"Vector after push_back 2 and 3 and squaring and sorting : ";
	sort(begin(v),end(v),[](int a,int b){return a>b;});		//lambda function o sort in decreasing order
	for(auto i:v)											//auto method to iterate a vector
		cout<<i<<" ";										//no need to dereference i
	cout<<endl<<"First element > 10 : "<<*find_if(begin(v),end(v),[](int x){return x>10;});	//returns itr to first element with condition
	cout<<endl<<"After stable partition wrt 10 : ";
	stable_partition(begin(v),end(v),[](int x){return x<10;});		//stable partition wrt 10
	for(auto i:v)
		cout<<i<<" ";
	v.push_back(7);
	v.push_back(26);
	v.push_back(17);
	cout<<endl<<"After adding a few elements : ";
	for(auto i:v)
		cout<<i<<" ";

	make_heap(begin(v),end(v));
	cout<<endl<<endl<<"After making heap of vector : ";
	for(auto i:v)
		cout<<i<<" ";
	pop_heap(begin(v),end(v));			//swap v[0],v[size-1] and heapify from begin(v) to end(v)-1
	v.pop_back();						//popping v[size-1]
	cout<<endl<<"After popping head of heap : ";
	for(auto i:v)
		cout<<i<<" ";
	v.push_back(18);					//element added at the last
	push_heap(begin(v),end(v));			//heapify last element of v
	cout<<endl<<"Heap after pushing 18 in heap : ";
	for(auto i:v)
		cout<<i<<" ";
	sort_heap(begin(v),end(v));			//uses heap sort and works only on heaps
	cout<<endl<<"After heap sort : ";
	for(auto i:v)
		cout<<i<<" ";
	cout<<endl<<endl;
	
	//http://www.cplusplus.com/reference/deque/deque/
	deque<vector<pair<int,int>>> d;					//deque of vectors of pair<int,int> type
	d={ {{1,2},{3,4}} , {{5,6},{7,8}} };			//iniatailize deque
	cout<<"Deque <vector<pair<int,int>>>\n";
	for(auto i:d)									//auto method to iterate, i is a vector
	{
		for(auto j:i)								//j is a pair<int,int>
			cout<<j.first<<","<<j.second<<endl;
		cout<<"---\n";
	}
	cout<<"Deque[1][0].second : "<<d[1][0].second<<endl<<endl;						//accessing second of first pair of second vector of deque

	//http://www.cplusplus.com/reference/set/set/
	set<int> s;					//declate a set of type int
	s={4,6,2,7,4};				//initialize set
	cout<<"Set <int> : ";
	for(auto i:s)				//auto method to iterate
		cout<<i<<" ";
	cout<<endl;
	s.insert(3);
	cout<<"Set after adding 3 : ";
	for(auto i:s)				//auto method to iterate
		cout<<i<<" ";	
	cout<<endl<<endl;

	//http://www.cplusplus.com/reference/list/list/
	list<int> l;					//declare a list of type int
	l={31,35,79,46,1};				//initialize list
	cout<<"List <int> : ";
	for(auto i:l)					//print list
		cout<<i<<" ";
	cout<<endl<<"Maximum LSDigit Number is ";
	cout<<*max_element(l.begin(),l.end(),[](int x,int y){return (x%10)<(y%10);})<<endl;	//returns iterator to max
	replace_if(begin(l),end(l),[](int x){return x<40;},0);								//replaces elements <40 with 0
	cout<<"List after replacing all x<40 with 0 : ";
	for(auto i:l)					//print list
		cout<<i<<" ";
	cout<<endl<<endl;

	//http://www.cplusplus.com/reference/array/array/
	array<int,4> a;				//declare array
	a={2,6,4,3};				//initialize array
	cout<<"Array <int,4> : ";
	for(auto i:a)				//print array
		cout<<i<<" ";
	cout<<endl;
	cout<<"Array is "<<(a.empty()?"empty":"not empty");		//inline if statements in cout
	cout<<endl<<"Elements less than 5 : "<<count_if(begin(a),end(a),[](int x){return x<5;})<<endl;	//counts elements on condition

	//http://www.cplusplus.com/reference/tuple/tuple/
	tuple<char,int,int> t('c',3,4);		//declare a tuple
	//t={'c',3,4};						//*check if this works
	cout<<"Third element of tuple (c,3,4) : "<<get<2>(t)<<endl;				//access third element of tuple t
	int x,y;
	tie(ignore,y,x)=t;			//Allows a set of objects to act like tuple, useful to unpack tuple objects
	cout<<"x = "<<x<<" y = "<<y<<endl<<endl;


	what_is(get<2>(t));						//look at the define statement of what_is

	cout<<"GCD of 18 and 27 : "<<__gcd(18,27)<<endl;				//Euclidean algorithm implemented in #include<algorithm>
	cout<<"Least significant 1-bit of 10 is at position "<<__builtin_ffs(10)<<" from right (1010)"<<endl;
	cout<<"Number of 1-bits in 14 is "<<__builtin_popcount(14)<<" (1110)"<<endl<<endl;

	cout<<"Matrix"<<endl;
	int A[2][2]={1,2,3,4};
	for(int i=0;i<=1;i++)
		for(int j=0;j<=1;j++)
			cout<<A[i][j]<<" \n"[j==1];		//[0] if j!=1 and [1] if j==1, saves a line of code ;)
	cout<<endl;
	for(int i=0;i<=1;i++,cout<<endl)		//endl after every change in row
		for(int j=0;j<=1;j++)
			cout<<A[i][j]<<" ";

	//for(int i=0;i<n;cin>>a[i++])							//one line way of input
	//for(int i=0;i<n;cout<<a[i++]<<" \n"[i==n-1])			//one line way of output

	string raw_str=R"(Hello\tWorld\n)";		//stores raw string Hello\tWorld\n
	cout<<endl<<raw_str<<endl;
	string str="abcd";
	next_permutation(begin(str),end(str));
	cout<<"Next permutation of abcd : "<<str<<endl;
	shuffle(begin(str),end(str),default_random_engine());
	cout<<"Random shuffle of ^abdc : "<<str<<endl<<endl;
	return 0;
}