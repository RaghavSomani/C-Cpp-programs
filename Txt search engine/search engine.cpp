/***************************************************************
 * The aim of this program is to make a text file search engine
 * which sorts the names of the text files in descending order
 * according to their occurences.
 * 
 * The main idea of this project is to hunt for the best
 * algorithm and data structure to serve the purpose.
 * 
 * An analysis of 6 different data structure and techniques
 * have been done to make out a satisfactory relation
 * between asymptotic theoretical analysis and experimental
 * data of space and time complexities.
 * 
 * The program takes the help of efficient inbuilt basic
 * data structures and algorithms provided by C++ in their
 * Standard Template Library which is inbuilt in the recent
 * versions of C++.
****************************************************************/

/* Standard Template Library header files for fstream, strings,
 * maps, vectors, linked lists and algorithm are included
 * along with basic header files like iostream, cstdlib,
 * sys/time.
*/

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <sys/time.h>
#include <cmath>
using namespace std;

/*
 * The Operating System is determined and stored in a char os
 * using a preprosessor if else statement which checks
 * is _WIN32 is defined or not
*/

#if defined(_WIN32)
	char os='W';
#else
	char os='L';
#endif

// The number of slots is globally initialized and stored in m

int m=127;

/* Prototype of the hash function which takes a string and
 * returns the slot number of the hash table
*/

unsigned int h(string);

/* Prototype of a compare function used while sorting the
 * names of text files in decreasing order of the occurence
 * of a word
*/

bool compare(pair<string,int> s1, pair<string,int> s2);

int main()
{
	
	/* The os character variable is checked and terminal is colored
	 * according to operating system based system commands.
	 * System commands are used to send the names of all the
	 * text files in the current directory to files.dat file so that
	 * we can extract the text file names from it. 
	*/

	if(os=='W')
	{
		system("cls");
		system("color 47");
		system("dir /b *.txt > files.dat");
	}
	else
	{
		system("tput setaf 7");
		system("tput setab 4");
		system("setterm -cursor off");
		system("clear");
		system("ls *.txt > files.dat");
	}

	/* Two objects start and end of the predefined structure contained in
	 * sys/time.h are created along with two int variables to store the
	 * start and end time of any running process
	*/

	struct timeval start, end;
	int buildtym, searchtym;
	
	/* A vector (resizable array) of string type is declared and
	 * all the names of the text files contained in files.dat are
	 * read and strored in it. The files.dat file is then deleted
	 * using OS dependent system command
	*/

	vector<string> FileList;
	string file;
	ifstream fp("files.dat");
	getline(fp,file);
	while(!fp.eof())
	{
		FileList.push_back(file);
		getline(fp,file);
	}
	fp.close();
	int NofFile=FileList.size();
	
	// files.dat file is deleted after use
	
	if(os=='W')
		system("del files.dat");
	else
		system("rm files.dat");
		
	/* The maximum length of the name of a text file is stored in maxlength
	 * This will be further used to indent file names
	*/
	
	int maxlength=0;
	for(int f=0;f<NofFile;f++)
		if(maxlength<FileList[f].length())
			maxlength=FileList[f].length();
	
	/* An array of pair of, string and int type is declared to keep the
	 * frequency of the word searched in decreasing order
	*/

	pair<string,int> SortedFiles[NofFile];

	/* Iterators to maps and vectors are declared for future use.
	 * Integer variables choice, gap, slot, i,j;
	 * character variable c; boolean variable found;
	 * ifstream variable FP; string variable s and str
	 * are declared for future use as they cannot be declared
	 * inside switch statements
	*/

	map<string,int>::iterator itm;
	vector<pair<string,int> >::iterator it;
	unordered_map<string,int>::iterator itu;
	int choice, slot, i, j, gap, setting, max;
	bool found=false;
	ifstream FP;
	string s, str, temp;
	char c, case_sense='n';
	
	// Welcome message with Settings options are shown on the terminal
	
	cout<<"\n\n\n\t\t\t\t\t***** WELCOME *****";
	cout<<"\n\n\t\t\tThe program sorts the occurrences of a word in all";
	cout<<"\n\t\t\tthe text files in the present directory in decreasing order\n";
	cout<<"\n\t\t\t1. Continue\n";
	cout<<"\t\t\t2. Change Settings\n";
	
	// Default choice is set to 5 which is for Hash Tables with Maps
	
	choice=6;
	cin>>setting;
	
	/* If the user enters setting, he/she is given the option to
	 * change the data structure
	*/
	
	if(setting==2)
	{
		cout<<"\t\t\t1. Change Data Structure\n";
		cout<<"\t\t\t2. Continue\n";
		cin>>setting;
		
		// The user is shown, the different Data structures available
		
		if(setting==1)
		{
			cout<<"\n\t\t\tChoose a method : \n\n";
			cout<<"\t\t\t1. Hash tables using Linked Lists\n";
			cout<<"\t\t\t2. Hash tables using Vectors storing frequencies\n";
			cout<<"\t\t\t3. Linear Search Algorithm using Linked Lists\n";
			cout<<"\t\t\t4. Balanced Trees using maps storing frequencies (with suggestions)\n";
			cout<<"\t\t\t5. Hash table using Balanced Trees storing frequencies\n";
			cout<<"\t\t\t6. Unordered maps storing frequencies (default)\n";
			cout<<"\n\t\t\tEnter choice : ";
			cin>>choice;
			
			/* If the data structure selected, contains hash tables, an option
			 * to change the number of slots is provided
			*/
			
			if(choice==1||choice==2||choice==5)
			{
				cout<<"\n\t\t\t1. Change the number of slots (default = 127)";
				cout<<"\n\t\t\t2. Continue\n";
				cin>>setting;
				if(setting==1)
				{
					cout<<"\t\t\tEnter the number of slots to keep (<"<<(int)(180000/FileList.size())<<"): ";
					cin>>m;
				}
			}
		}
	}
	
	/* The do-while loop runs, as many times we want to
	 * repeat the program, using different data structures.
	*/

	do
	{

		/* 6 different data structures are initialized for different cases.
		 * 
		 * Case 1 : Hash table of linked lists for each file, with m slots
		 * Case 2 : Hash table of vectors for each file, Each vector cell
		 *			contains a pair, to store both string and its corresponding
		 * 			frequency.
		 * Case 3 : Linked list for each file.
		 * Case 4 : Map (balanced tree) for each file, where each node of a map
		 			contains the string and its corresponding frequency.
		 * Case 5 : Hash table of maps (balanced trees), where each map
		 * 			contains the string and its corresponding frequency.
		 * Case 6 : Unordered Maps for each file, where each unordered map is
		 			internally a hash table.
		*/
		
		list<string> H[m][NofFile];
		vector<pair<string,int> > HF[m][NofFile];
		list<string> B[NofFile];
		map<string,int> M[NofFile];
		map<string,int> MF[m][NofFile];
		unordered_map<string,int> UM[NofFile];

		/* The menu of the program is displayed, and the user is prompted
		 * to enter a choice out of 6.
		*/
		
		cout<<"\t\t\tAdd case sensitivity? (Y/N) : ";
		cin>>case_sense;
		
		switch(choice)
		{
			case 1:

				/* The starting time of data structre creation is stored in start object
				 * of the timeval structure using the gettimeofday inbuilt function.
				*/
			
				cout<<"\n\t\t\tPlease wait while the data structure is being created\n";
				gettimeofday(&start,NULL);

				// For each file a data structure is created

				for(int f=0;f<NofFile;f++)
				{
					
					/* The fth file is opened and strings are read untill,
					 * the FP pointer reaches the end of file.
					*/

					char* CurrFile=&FileList[f][0];
					FP.open(CurrFile);
					FP>>str;
					while(!FP.eof())
					{
						
						/* Each string is preprocessed by removing the punctuations
						 * and special characters on both of its sides, using the
						 * isalnum function. The string is converted to lower case
						 * using the transform::tolower function in algorithm
						 * header file
						*/

						i=0;
						j=str.length();
						if(!str.empty())
						{
							while(!isalnum(str[i])) i++;
							while(!isalnum(str[j])) j--;
						}
						if(j>=i)
						{
							s=str.substr(i,j-i+1);
							if(case_sense=='n')
								transform(s.begin(), s.end(), s.begin(), ::tolower);

							// The slot of processed string is calculated by the h function

							slot=h(s);

							/* This string is then pushed in the linked list corresponding to
							 * the slot and file
							*/

							H[slot][f].push_back(s);
						}
						FP>>str;
					}
					FP.close();
				}

				/* The end time of data structure creation is stored in the end object, using
				 * the gettimeofday function. The difference of the start and end time in 
				 * microseconds is stored in buildtym variable and printed on the terminal.
				*/

				gettimeofday(&end,NULL);
				buildtym = (end.tv_sec-start.tv_sec)*1000000 + (end.tv_usec-start.tv_usec);
				cout << "\n\t\t\tTime taken to build the Hash table is : " << buildtym << " microseconds\n";

				/* A do-while loop runs untill, the user wants to use the built data structure
				 * to search words.
				*/

				do
				{
					/* A word is taken from the user and is converted to lowercase using the
					 * transform::tolower function to avoid case-sensitivity.
					*/

					cout<<"\n\t\t\tEnter a word to search : ";
					cin>>s;
					cout<<"\n\t\t\tFiles with decreasing order of their occurrences\n\n";
					if(case_sense=='n')
						transform(s.begin(), s.end(), s.begin(), ::tolower);
							
					/* The begin time of word searching is stored in the start object using
					 * the gettimeofday function. The slot number is calculated using the same
					 * hash function to know its position and if that word is present.
					*/

					gettimeofday(&start,NULL);
					slot=h(s);

					/* The array of sortedfiles is updated with its first variable as the
					 * name of the file and second variable as the number of times the word
					 * appears in that particular file. The counting is done using the
					 * count function inbuilt in algorithm header file.
					*/

					for(int f=0;f<NofFile;f++)
					{
						SortedFiles[f].first=FileList[f];
						SortedFiles[f].second=count(H[slot][f].begin(),H[slot][f].end(),s);
					}

					/* The end time of searching and creation of table is stored in end object
					 * using the gettimeofday function. The difference of start and build time is
					 * stored in searchtym and printed. The SortedFiles array of pairs is sorted
					 * using a sort and compare function to list the files in decreasing order.
					*/

					gettimeofday(&end,NULL);
					searchtym = (end.tv_sec-start.tv_sec)*1000000 + (end.tv_usec-start.tv_usec);
					sort(SortedFiles,SortedFiles+NofFile,compare);

					/* The SortedFiles array is printed in an indented manner
					 * by calculating extra space gaps using the maxlength of a
					 * text file name, calculated previously.
					*/

					for(int f=0;f<NofFile;f++)
					{
						cout<<"\t\t\t\t"<<SortedFiles[f].first;
						gap=maxlength-SortedFiles[f].first.length();
						for(int i=0;i<gap;i++)
							cout<<" ";
						cout<<"  |  ";
						cout<<SortedFiles[f].second<<endl;
					}

					/* The searchtym is printed, and the user is prompted if, he/she
					 * wants to search another word in the same data structure.
					*/

					cout << "\n\t\t\tTime taken to search the word and sort the files : " << searchtym<< " microseconds\n";
					cout << "\n\t\t\tSearch another word? (Y/N) : ";
					cin>>c;
				}while(c=='y'||c=='Y');
				break;
			case 2:

				/* The starting time of data structre creation is stored in start object
				 * of the timeval structure using the gettimeofday inbuilt function.
				*/

				cout<<"\n\t\t\tPlease wait while the data structure is been created\n";
				gettimeofday(&start,NULL);

				// For each file a data structure is created

				for(int f=0;f<NofFile;f++)
				{
					
					/* The fth file is opened and strings are read until
					 * the FP pointer reaches the end of file.
					*/

					char* CurrFile=&FileList[f][0];
					FP.open(CurrFile);
					FP>>str;
					while(!FP.eof())
					{
						
						/* Each string is preprocessed by removing the punctuations
						 * and special characters on both of its sides using the
						 * isalnum function. The string is made to lower case
						 * using the transform::tolower function in algorithm
						 * header file
						*/

						i=0;
						j=str.length();
						if(!str.empty())
						{
							while(!isalnum(str[i])) i++;
							while(!isalnum(str[j])) j--;
						}
						if(j>=i)
						{
							s=str.substr(i,j-i+1);
							if(case_sense=='n')
								transform(s.begin(), s.end(), s.begin(), ::tolower);

							// The slot of processed string is calculated by the h function

							slot=h(s);

							/* A pair is made with its first variable as the processed string and
							 * second variable as the initial starting frequency 1. The found
							 * boolean variable is set to false
							*/

							pair<string,int> P;
							P.first=s;
							P.second=1;
							found=false;

							/* The string is searched in the present linked list
							 * corresponding to the file and the calculated slot.
							 * If the string is found, the integer part storing the
							 * frequency is incremented by 1.
							*/

							for(it=HF[slot][f].begin();it!=HF[slot][f].end();it++)
							{
								if(it->first==s)
								{
									it->second++;
									found=true;
									break;
								}
							}

							/* This string if not found is then pushed in the linked list corresponding to
							 * the slot and file
							*/

							if(!found)
								HF[slot][f].push_back(P);
						}
						FP>>str;
					}
					FP.close();
				}

				/* The end time of data structure creation is stored in the end object using
				 * the gettimeofday function. The difference of the start and end time in 
				 * microseconds is stored in buildtym variable and printed on the terminal.
				*/

				gettimeofday(&end,NULL);
				buildtym = (end.tv_sec-start.tv_sec)*1000000 + (end.tv_usec-start.tv_usec);
				cout << "\n\t\t\tTime taken to build the Hash table storing words\n\t\t\talong with";
				cout <<" their frequency is : " << buildtym << " microseconds\n";
				
				/* A do-while loop runs untill the user wants to use the built data structure
				 * to search words.
				*/

				do
				{

					/* A word is taken from the user and converted to lowercase using the
					 * transform::tolower function to avoid case-sensitivity.
					*/

					cout<<"\n\t\t\tEnter a word to search : ";
					cin>>s;
					cout<<"\n\t\t\tFiles with decreasing order of their occurrences\n\n";
					if(case_sense=='n')
						transform(s.begin(), s.end(), s.begin(), ::tolower);

					/* The begin time of word searching is stored in the start object using
					 * the gettimeofday function. The slot number is calculated using the same
					 * hash function to know its position if the word is present.
					*/

					gettimeofday(&start,NULL);
					slot=h(s);

					/* The first variable of each element in SortedFile array is made to
					 * store the file name. The word to be searched is scanned throughout
					 * the list. If the string is found then the second variable of
					 * pair is made equal to second variable of SortedFiles[f] pair,
					 * else it is set to 0.
					*/

					for(int f=0;f<NofFile;f++)
					{
						SortedFiles[f].first=FileList[f];
						SortedFiles[f].second=0;
						for(it=HF[slot][f].begin();it!=HF[slot][f].end();it++)
						{
							if(it->first==s)
							{
								SortedFiles[f].second=it->second;
								break;
							}
						}
					}

					/* The end time of searching and creation of table is stored in end object
					 * using the gettimeofday function. The difference of start and build time
					 * stored in searchtym and printed. The SortedFiles array of pairs is sorted
					 * using a sort and compare function to list the files in decreasing order.
					*/

					gettimeofday(&end,NULL);
					searchtym = (end.tv_sec-start.tv_sec)*1000000 + (end.tv_usec-start.tv_usec);
					sort(SortedFiles,SortedFiles+NofFile,compare);

					/* The SortedFiles array is printed in an indented manner
					 * by calculating extra space gaps using the maxlength of a
					 * text file name previously calculated.
					*/

					for(int f=0;f<NofFile;f++)
					{
						cout<<"\t\t\t\t"<<SortedFiles[f].first;
						gap=maxlength-SortedFiles[f].first.length();
						for(int i=0;i<gap;i++)
							cout<<" ";
						cout<<"  |  ";
						cout<<SortedFiles[f].second<<endl;
					}

					/* The searchtym is printed and the user is prompted if he/she
					 * wants to search another word in the same data structure.
					*/

					cout << "\n\t\t\tTime taken to search the word and sort the files : " << searchtym<< " microseconds\n";
					cout << "\n\t\t\tSearch another word? (Y/N) : ";
					cin>>c;
				}while(c=='y'||c=='Y');
				break;
			case 3:

				/* The starting time of data structre creation is stored in start object
				 * of the timeval structure using the gettimeofdat inbuild function.
				*/

				cout<<"\n\t\t\tPlease wait while the data structure is been created\n";
				gettimeofday(&start,NULL);

				// For each file a data structure is created

				for(int f=0;f<NofFile;f++)
				{

					/* The fth file is opened and strings are read until
					 * the FP pointer reaches the end of file.
					*/

					char* CurrFile=&FileList[f][0];
					FP.open(CurrFile);
					FP>>str;
					while(!FP.eof())
					{

						/* Each string is preprocessed by removing the punctuations
						 * and special characters on both of its sides using the
						 * isalnum function. The string is made to lower case
						 * using the transform::tolower function in algorithm
						 * header file
						*/

						i=0;
						j=str.length();
						if(!str.empty())
						{
							while(!isalnum(str[i])) i++;
							while(!isalnum(str[j])) j--;
						}
						if(j>=i)
						{
							s=str.substr(i,j-i+1);
							if(case_sense=='n')
								transform(s.begin(), s.end(), s.begin(), ::tolower);

							/* This string is then pushed in the linked list corresponding to
							 * the file
							*/

							B[f].push_back(s);
						}
						FP>>str;
					}
					FP.close();
				}

				/* The end time of data structure creation is stored in the end object using
				 * the gettimeofday function. The difference of the start and end time in 
				 * microseconds is stored in buildtym variable and printed on the terminal.
				*/

				gettimeofday(&end,NULL);
				buildtym = (end.tv_sec-start.tv_sec)*1000000 + (end.tv_usec-start.tv_usec);
				cout << "\n\t\t\tTime taken to push the words in the Linked List : " << buildtym<< " microseconds\n";
				
				/* A do-while loop runs untill the user wants to use the built data structure
				 * to search words.
				*/

				do
				{

					/* A word is taken from the user and converted to lowercase using the
					 * transform::tolower function to avoid case-sensitivity.
					*/

					cout<<"\n\t\t\tEnter a word to search : ";
					cin>>s;
					cout<<"\n\t\t\tFiles with decreasing order of their occurrences\n\n";
					if(case_sense=='n')
						transform(s.begin(), s.end(), s.begin(), ::tolower);
					
					/* The begin time of word searching is stored in the start object using
					 * the gettimeofday function.
					*/
					
					gettimeofday(&start,NULL);

					/* The array of sortedfiles is updated with its first variable as the
					 * name of the file and second variable as the number of times the word
					 * appeared in that particular file. The counting is done using the
					 * count function inbuilt in algorithm header file.
					*/

					for(int f=0;f<NofFile;f++)
					{
						SortedFiles[f].first=FileList[f];
						SortedFiles[f].second=count(B[f].begin(),B[f].end(),s);
					}

					/* The end time of searching and creation of table is stored in end object
					 * using the gettimeofday function. The difference of start and build time
					 * stored in searchtym and printed. The SortedFiles array of pairs is sorted
					 * using a sort and compare function to list the files in decreasing order.
					*/

					gettimeofday(&end,NULL);
					searchtym = (end.tv_sec-start.tv_sec)*1000000 + (end.tv_usec-start.tv_usec);
					sort(SortedFiles,SortedFiles+NofFile,compare);

					/* The SortedFiles array is printed in an indented manner
					 * by calculating extra space gaps using the maxlength of a
					 * text file name previously calculated.
					*/

					for(int f=0;f<NofFile;f++)
					{
						cout<<"\t\t\t\t"<<SortedFiles[f].first;
						gap=maxlength-SortedFiles[f].first.length();
						for(int i=0;i<gap;i++)
							cout<<" ";
						cout<<"  |  ";
						cout<<SortedFiles[f].second<<endl;
					}

					/* The searchtym is printed and the user is prompted if he/she
					 * wants to search another word in the same data structure.
					*/

					cout << "\n\t\t\tTime taken to search the word and sort the files : " << searchtym<< " microseconds\n";
					cout << "\n\t\t\tSearch another word? (Y/N) : ";
					cin>>c;
				}while(c=='y'||c=='Y');
				break;
			case 4:

				/* The starting time of data structre creation is stored in start object
				 * of the timeval structure using the gettimeofdat inbuild function.
				*/

				cout<<"\n\t\t\tPlease wait while the data structure is been created\n";
				gettimeofday(&start,NULL);

				// For each file a data structure is created

				for(int f=0;f<NofFile;f++)
				{
					
					/* The fth file is opened and strings are read until
					 * the FP pointer reaches the end of file.
					*/

					char* CurrFile=&FileList[f][0];
					FP.open(CurrFile);
					FP>>str;
					while(!FP.eof())
					{
						
						/* Each string is preprocessed by removing the punctuations
						 * and special characters on both of its sides using the
						 * isalnum function. The string is made to lower case
						 * using the transform::tolower function in algorithm
						 * header file
						*/

						i=0;
						j=str.length();
						if(!str.empty())
						{
							while(!isalnum(str[i])) i++;
							while(!isalnum(str[j])) j--;
						}
						if(j>=i)
						{
							s=str.substr(i,j-i+1);
							if(case_sense=='n')
								transform(s.begin(), s.end(), s.begin(), ::tolower);
							itm=M[f].find(s);

							/* This string if not found is then inserted in the map corresponding to
							 * the file. If found, the integer part of the node is incremented by 1.
							*/

							if(itm==M[f].end())
								M[f].insert(pair<string,int>(s,1));
							else
								itm->second++;
						}
						FP>>str;
					}
					FP.close();
				}

				/* The end time of data structure creation is stored in the end object using
				 * the gettimeofday function. The difference of the start and end time in 
				 * microseconds is stored in buildtym variable and printed on the terminal.
				*/

				gettimeofday(&end,NULL);
				buildtym = (end.tv_sec-start.tv_sec)*1000000 + (end.tv_usec-start.tv_usec);
				cout << "\n\t\t\tTime taken to Build The balanced Tree storing words\n\t\t\talong with";
				cout <<" their frequencies : " << buildtym<< " microseconds\n";
				
				/* A do-while loop runs untill the user wants to use the built data structure
				 * to search words.
				*/

				do
				{
					
					/* A word is taken from the user and converted to lowercase using the
					 * transform::tolower function to avoid case-sensitivity.
					*/

					cout<<"\n\t\t\tEnter a word to search : ";
					cin>>s;
					if(case_sense=='n')
						transform(s.begin(), s.end(), s.begin(), ::tolower);
					
					/* The begin time of word searching is stored in the start object using
					 * the gettimeofday function.
					*/

					gettimeofday(&start,NULL);

					/* The first variable of each element in SortedFile array is made to
					 * store the file name. The word to be searched is scanned throughout
					 * the map. If the string is found then the second variable of
					 * node is made equal to second variable of SortedFiles[f] pair,
					 * else it is set to 0. The maximum frequency is kept track.
					*/

					max=0;
					for(int f=0;f<NofFile;f++)
					{
						SortedFiles[f].first=FileList[f];
						itm=M[f].find(s);
						if(itm==M[f].end())
							SortedFiles[f].second=0;
						else
						{
							SortedFiles[f].second=itm->second;
							if(itm->second > max)
								max=itm->second;
						}
					}

					/* If the maximum frequency comes out to be 0 then the words
					 * which come just after and before s in lexicographic order word length difference 
					 * maximum is printed for all files.
					*/
					
					if(max==0)
					{
						cout<<"\n\t\t\tWord not found";
						cout<<"\n\t\t\tNearest words might be";
						cout<<"\n\t\t\t";
						for(int f=0;f<NofFile;f++)
						{
							if(!M[f].empty())
							{
								itm=M[f].lower_bound(s);
								if(itm!=M[f].end())
								{
									if(abs(itm->first.length() - s.length())<2)
										cout<<itm->first<<" ";
								}
								itm--;
								if(itm!=M[f].begin())
								{
									if(abs(itm->first.length() - s.length())<2)
										cout<<itm->first<<" ";
								}
							}
							
						}
					}
					cout<<"\n\t\t\t";

					/* The end time of searching and creation of table is stored in end object
					 * using the gettimeofday function. The difference of start and build time
					 * stored in searchtym and printed. The SortedFiles array of pairs is sorted
					 * using a sort and compare function to list the files in decreasing order.
					*/

					gettimeofday(&end,NULL);
					searchtym = (end.tv_sec-start.tv_sec)*1000000 + (end.tv_usec-start.tv_usec);
					sort(SortedFiles,SortedFiles+NofFile,compare);

					/* if the maximum frequency is not 0, the SortedFiles array is printed
					 * in an indented manner by calculating extra space gaps using the maxlength of a
					 * text file name previously calculated.
					*/

					if(max!=0)
					{
						cout<<"\n\t\t\tFiles with decreasing order of their occurrences\n\n";
						for(int f=0;f<NofFile;f++)
						{
							cout<<"\t\t\t\t"<<SortedFiles[f].first;
							gap=maxlength-SortedFiles[f].first.length();
							for(int i=0;i<gap;i++)
								cout<<" ";
							cout<<"  |  ";
							cout<<SortedFiles[f].second<<endl;
						}
					}

					/* The searchtym is printed and the user is prompted if he/she
					 * wants to search another word in the same data structure.
					*/

					cout << "\n\t\t\tTime taken to search the word and sort the files : " << searchtym<< " microseconds\n";
					cout << "\n\t\t\tSearch another word? (Y/N) : ";
					cin>>c;
				}while(c=='y'||c=='Y');
				break;
			case 5:

				/* The starting time of data structre creation is stored in start object
				 * of the timeval structure using the gettimeofdat inbuild function.
				*/

				cout<<"\n\t\t\tPlease wait while the data structure is been created\n";
				gettimeofday(&start,NULL);

				// For each file a data structure is created

				for(int f=0;f<NofFile;f++)
				{
					
					/* The fth file is opened and strings are read until
					 * the FP pointer reaches the end of file.
					*/

					char* CurrFile=&FileList[f][0];
					FP.open(CurrFile);
					FP>>str;
					while(!FP.eof())
					{

						/* Each string is preprocessed by removing the punctuations
						 * and special characters on both of its sides using the
						 * isalnum function. The string is made to lower case
						 * using the transform::tolower function in algorithm
						 * header file
						*/

						i=0;
						j=str.length();
						if(!str.empty())
						{
							while(!isalnum(str[i])) i++;
							while(!isalnum(str[j])) j--;
						}
						if(j>=i)
						{
							s=str.substr(i,j-i+1);
							if(case_sense=='n')
								transform(s.begin(), s.end(), s.begin(), ::tolower);
								
							// The slot of processed string is calculated by the h function

							slot=h(s);
							itm=MF[slot][f].find(s);

							/* This string if not found is then pushed in the map corresponding to
							 * the slot and file with frequency as 1. If the string is found then
							 * the second variable of the node is incremented by 1.
							*/

							if(itm==MF[slot][f].end())
								MF[slot][f].insert(pair<string,int>(s,1));
							else
								itm->second++;
						}
						FP>>str;
					}
					FP.close();
				}

				/* The end time of data structure creation is stored in the end object using
				 * the gettimeofday function. The difference of the start and end time in 
				 * microseconds is stored in buildtym variable and printed on the terminal.
				*/

				gettimeofday(&end,NULL);
				buildtym = (end.tv_sec-start.tv_sec)*1000000 + (end.tv_usec-start.tv_usec);
				cout << "\n\t\t\tTime taken to Build The Balanced Tree Hash Table : " << buildtym<< " microseconds\n";
				
				/* A do-while loop runs untill the user wants to use the built data structure
				 * to search words.
				*/

				do
				{

					/* A word is taken from the user and converted to lowercase using the
					 * transform::tolower function to avoid case-sensitivity.
					*/

					cout<<"\n\t\t\tEnter a word to search : ";
					cin>>s;
					cout<<"\n\t\t\tFiles with decreasing order of their occurrences\n\n";
					if(case_sense=='n')
						transform(s.begin(), s.end(), s.begin(), ::tolower);

					/* The begin time of word searching is stored in the start object using
					 * the gettimeofday function. The slot number is calculated using the same
					 * hash function to know its position if the word is present.
					*/

					gettimeofday(&start,NULL);
					slot=h(s);

					/* The first variable of each element in SortedFile array is made to
					 * store the file name. The word to be searched is scanned throughout
					 * the map. If the string is found then the second variable of
					 * node is made equal to second variable of SortedFiles[f] pair,
					 * else it is set to 0.
					*/

					for(int f=0;f<NofFile;f++)
					{
						SortedFiles[f].first=FileList[f];
						itm=MF[slot][f].find(s);
						if(itm==MF[slot][f].end())
							SortedFiles[f].second=0;
						else
							SortedFiles[f].second=itm->second;
					}

					/* The end time of searching and creation of table is stored in end object
					 * using the gettimeofday function. The difference of start and build time
					 * stored in searchtym and printed. The SortedFiles array of pairs is sorted
					 * using a sort and compare function to list the files in decreasing order.
					*/

					gettimeofday(&end,NULL);
					searchtym = (end.tv_sec-start.tv_sec)*1000000 + (end.tv_usec-start.tv_usec);
					sort(SortedFiles,SortedFiles+NofFile,compare);

					/* The SortedFiles array is printed in an indented manner
					 * by calculating extra space gaps using the maxlength of a
					 * text file name previously calculated.
					*/

					for(int f=0;f<NofFile;f++)
					{
						cout<<"\t\t\t\t"<<SortedFiles[f].first;
						gap=maxlength-SortedFiles[f].first.length();
						for(int i=0;i<gap;i++)
							cout<<" ";
						cout<<"  |  ";
						cout<<SortedFiles[f].second<<endl;
					}

					/* The searchtym is printed and the user is prompted if he/she
					 * wants to search another word in the same data structure.
					*/

					cout << "\n\t\t\tTime taken to search the word and sort the files : " << searchtym<< " microseconds\n";
					cout << "\n\t\t\tSearch another word? (Y/N) : ";
					cin>>c;
				}while(c=='y'||c=='Y');
				break;
			case 6:

				/* The starting time of data structre creation is stored in start object
				 * of the timeval structure using the gettimeofdat inbuild function.
				*/

				cout<<"\n\t\t\tPlease wait while the data structure is been created\n";
				gettimeofday(&start,NULL);

				// For each file a data structure is created

				for(int f=0;f<NofFile;f++)
				{
					
					/* The fth file is opened and strings are read until
					 * the FP pointer reaches the end of file.
					*/

					char* CurrFile=&FileList[f][0];
					FP.open(CurrFile);
					FP>>str;
					while(!FP.eof())
					{
						
						/* Each string is preprocessed by removing the punctuations
						 * and special characters on both of its sides using the
						 * isalnum function. The string is made to lower case
						 * using the transform::tolower function in algorithm
						 * header file
						*/

						i=0;
						j=str.length();
						if(!str.empty())
						{
							while(!isalnum(str[i])) i++;
							while(!isalnum(str[j])) j--;
						}
						if(j>=i)
						{
							s=str.substr(i,j-i+1);
							if(case_sense=='n')
								transform(s.begin(), s.end(), s.begin(), ::tolower);
							itu=UM[f].find(s);

							/* This string if not found is then inserted in the unordered map corresponding to
							 * the file. If found, the integer part of the node is incremented by 1.
							*/

							if(itu==UM[f].end())
								UM[f].insert(pair<string,int>(s,1));
							else
								itu->second++;
						}
						FP>>str;
					}
					FP.close();
				}

				/* The end time of data structure creation is stored in the end object using
				 * the gettimeofday function. The difference of the start and end time in 
				 * microseconds is stored in buildtym variable and printed on the terminal.
				*/

				gettimeofday(&end,NULL);
				buildtym = (end.tv_sec-start.tv_sec)*1000000 + (end.tv_usec-start.tv_usec);
				cout << "\n\t\t\tTime taken to Build the unordered map storing words\n\t\t\talong with";
				cout <<" their frequencies : " << buildtym<< " microseconds\n";
				
				/* A do-while loop runs untill the user wants to use the built data structure
				 * to search words.
				*/

				do
				{
					
					/* A word is taken from the user and converted to lowercase using the
					 * transform::tolower function to avoid case-sensitivity.
					*/

					cout<<"\n\t\t\tEnter a word to search : ";
					cin>>s;
					cout<<"\n\t\t\tFiles with decreasing order of their occurrences\n\n";
					if(case_sense=='n')
						transform(s.begin(), s.end(), s.begin(), ::tolower);
					
					/* The begin time of word searching is stored in the start object using
					 * the gettimeofday function.
					*/

					gettimeofday(&start,NULL);

					/* The first variable of each element in SortedFile array is made to
					 * store the file name. The word to be searched is scanned throughout
					 * the unordered map. If the string is found then the second variable of
					 * node is made equal to second variable of SortedFiles[f] pair,
					 * else it is set to 0.
					*/

					for(int f=0;f<NofFile;f++)
					{
						SortedFiles[f].first=FileList[f];
						itu=UM[f].find(s);
						if(itu==UM[f].end())
							SortedFiles[f].second=0;
						else
							SortedFiles[f].second=itu->second;
					}

					/* The end time of searching and creation of table is stored in end object
					 * using the gettimeofday function. The difference of start and build time
					 * stored in searchtym and printed. The SortedFiles array of pairs is sorted
					 * using a sort and compare function to list the files in decreasing order.
					*/

					gettimeofday(&end,NULL);
					searchtym = (end.tv_sec-start.tv_sec)*1000000 + (end.tv_usec-start.tv_usec);
					sort(SortedFiles,SortedFiles+NofFile,compare);

					/* The SortedFiles array is printed in an indented manner
					 * by calculating extra space gaps using the maxlength of a
					 * text file name previously calculated.
					*/

					for(int f=0;f<NofFile;f++)
					{
						cout<<"\t\t\t\t"<<SortedFiles[f].first;
						gap=maxlength-SortedFiles[f].first.length();
						for(int i=0;i<gap;i++)
							cout<<" ";
						cout<<"  |  ";
						cout<<SortedFiles[f].second<<endl;
					}

					/* The searchtym is printed and the user is prompted if he/she
					 * wants to search another word in the same data structure.
					*/

					cout << "\n\t\t\tTime taken to search the word and sort the files : " << searchtym<< " microseconds\n";
					cout << "\n\t\t\tSearch another word? (Y/N) : ";
					cin>>c;
				}while(c=='y'||c=='Y');
				break;
			default:

				/* If the user enters a choice out of range, i.e., greater than 5 or less
				 * than 1 then the user is asked to try a valid option.
				*/

				cout<<"\n\t\t\tTry a valid option\n";
				break;
		}

		/* If the user enters an invalid choice, the user variable c is forced set to 'Y'.
		 * Else the user is prompted to ask for a choice to repeat or not. The character c
		 * is set to 'y' or 'n' accordingly.
		*/

		if(choice<0||choice>6)
			c='Y';
		else
		{
			cout<<"\n\t\t\tRepeat? (Y/N) : ";
			cin>>c;
		}

		// The user is provided with an option to change Data Structure and run again
		
		if(c=='y'||c=='Y')
		{
			cout<<"\n\t\t\t1. Change Data Structure\n";
			cout<<"\t\t\t2. Continue\n";
			cin>>setting;
			if(setting==1)
			{
				cout<<"\n\t\t\tChoose a method : \n\n";
				cout<<"\t\t\t1. Hash tables using Linked Lists ";
				if(choice==1)
					cout<<"(current)";
				cout<<"\n";
				cout<<"\t\t\t2. Hash tables using Vectors storing frequencies ";
				if(choice==2)
					cout<<"(current)";
				cout<<"\n";
				cout<<"\t\t\t3. Linear Search Algorithm using Linked Lists ";
				if(choice==3)
					cout<<"(current)";
				cout<<"\n";
				cout<<"\t\t\t4. Balanced Trees using maps storing frequencies (with suggestions) ";
				if(choice==4)
					cout<<"(current)";
				cout<<"\n";
				cout<<"\t\t\t5. Hash table using Balanced Trees storing frequencies ";
				if(choice==5)
					cout<<"(current)";
				cout<<"\n";
				cout<<"\t\t\t6. Unordered maps storing frequencies ";
				if(choice==6)
					cout<<"(current)";
				cout<<"\n";
				cout<<"\n\t\t\tEnter choice : ";
				cin>>choice;
				if(choice==1||choice==2||choice==5)
				{
				
					// The user also has the option to change the number of slots for another run
					
					cout<<"\n\t\t\t1. Change the number of slots (Currently "<<m<<")";
					cout<<"\n\t\t\t2. Continue\n";
					cin>>setting;
					if(setting==1)
					{
						cout<<"\t\t\tEnter the number of slots to keep (<"<<(int)(180000/FileList.size())<<") : ";
						cin>>m;
					}
				}
			}
		}
		
		/* The time when the do-while loop runs again or the program ends,
		 * the memory alloted to the data structures is freed.
		*/
		
		cout<<"\n\t\t\tFreeing memory... \n";
	}while(c=='y'||c=='Y');
	
	// User is asked to enter a key to exit so that he/she gets the time to see the output.

	cout<<"\n\n\t\t\t\t***** Thank You *****\n";
	cout<<"\n\t\t\tPress a key to exit...";
	c=getchar();
	c=getchar();

	/* Based on the operating syetem, terminal screen is cleated and the background
	 * is set to linux in case of linux based OS
	*/

	if(os=='W')
		system("cls");
	else
	{
		system("tput reset");
		system("clear");
	}
	return 0;
}

/* The compare function takes two pairs containing two variables, string and int.
 * The function returns true only when the second variable of the first pair is
 * greater than that of second pair.
*/

bool compare(pair<string,int> s1, pair<string,int> s2) { return s1.second>s2.second; }

/* The hash function h uses a rolling function to calculate slot number.
 * It takes a string and returns an unsigned integer representing slot number.
 * This rolling hash function treats each string as a 27 bit integer modulo m
*/

unsigned int h(string s)
{
	unsigned int sum=0,len=s.length();
	unsigned int po=1;
	for(int i=0;i<len;i++)
	{

		/* If the character is an alphabet, its value is taken as
		 * its ascii value - 97 so that a -> 0, b -> 1, ...,
		 * z -> 25 and any other non alphabet character is taken as 26.
		*/

		if(isalpha(s[i]))
			sum=( sum + (((unsigned int)(s[i]-97))%m)*po )%m;
		else
			sum=( sum + 26*po )%m;
		po = (po*27)%m;
	}
	return sum;
}
