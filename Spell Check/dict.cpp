#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <cmath>
#include <algorithm>
#include <climits>
using namespace std;
int m=127;
int h(string s);
int main()
{
	string mydict="dict58k.txt";
	fstream dict(mydict);
	list<string> H[m];
	string s;
	while(!dict.eof())
	{
		dict>>s;
		transform(s.begin(), s.end(), s.begin(), ::tolower);
		H[h(s)].push_front(s);
	}
	dict.close();
	label: cout<<"Enter word to search : ";
	cin>>s;
	transform(s.begin(), s.end(), s.begin(), ::tolower);
	string S=s;
	int temp=0,found=0;
	for(auto i:H[h(s)])
		if(i==s)
		{
			temp=1;
			found=1;
			break;
		}
	if(temp==1)
		cout<<"Word found\n";
	else
	{
		char z;
		string r;
		cout<<"Word not found\n";
		cout<<"Suggested words : ";
		for(int i=0;i<s.length();i++)		//replacing letters
		{
			z=s[i];
			for(int j=97;j<=122;j++)
			{
				s[i]=(char)j;
				temp=0;
				for(auto k:H[h(s)])
					if(k==s)
					{
						temp=1;
						break;
					}
				if(temp==1)
					cout<<s<<"  ";
				s[i]=z;
			}
		}
		for(int i=0;i<=s.length();i++)		//adding letters in b/w
		{
			for(int j=97;j<=122;j++)
			{
				z=(char)j;
				r=z;
				s.insert(i,r);
				temp=0;
				for(auto k:H[h(s)])
					if(k==s)
					{
						temp=1;
						break;
					}
				if(temp==1)
					cout<<s<<"  ";
				s.erase(s.begin()+i);
			}
		}
		for(int i=0;i<s.length();i++)		//deleting letters
		{
			z=s[i];
			r=z;
			s.erase(s.begin()+i);
			temp=0;
			for(auto k:H[h(s)])
				if(k==s)
				{
					temp=1;
					break;
				}
			if(temp==1)
				cout<<s<<"  ";
			s.insert(i,r);
		}
	}
	char ch;
	if(!found)
	{
		cout<<"\nAdd "<<S<<" to Dictionary?\n";
		cin>>ch;
		if(ch=='Y'||ch=='y')
		{
			ofstream add(mydict,ios::app);
			add<<S<<endl;
			add.close();
			H[h(S)].push_front(S);
		}
	}
	cout<<endl<<"Find more? (Y/N) : ";
	cin>>ch;
	if(ch=='Y'||ch=='y')
		goto label;
	return 0;
}
int h(string s)
{
	unsigned int sum=0;
	for(int i=0;i<s.length();i++)
		sum=(sum+((int)s[i]-97) * (int)pow(26,i))%m;
	return sum;
}