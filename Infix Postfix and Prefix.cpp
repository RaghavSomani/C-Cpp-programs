#include<iostream>
#include<string>
#define n 50
using namespace std;
char stack[n];
int top=-1,Top=-1;
char pop(char stack[]);
string pop(string S[]);
void push(char stack[],char x);
void push(string S[],string x);
int prior(char c);
int main()
{
	cout<<"Infix Expression    : ";
	char a[n],temp;
	cin>>a;
	int len=a.length(),k=0;
	a[len]=')';
	len++;
	char post[n];
	push(stack,'(');
	for(int i=0;i<len;i++)
	{
		if(a[i]=='(')
			push(stack,a[i]);
		else if(a[i]=='+'||a[i]=='-'||a[i]=='*'||a[i]=='/')
		{
			while(prior(stack[top]) >= prior(a[i]))
				post[k++]=pop(stack);
			push(stack,a[i]);
		}
		else if(a[i]==')')
		{
			while(stack[top]!='(')
				post[k++]=pop(stack);
			temp=pop(stack);
		}
		else
			post[k++]=a[i];
	}
	post[k]='\0';
	cout<<"Postfix Expression  : "<<post<<endl;
	int result=0,x,y;
	for(int i=0;i<k;i++)
	{
		if(post[i]=='+'||post[i]=='-'||post[i]=='*'||post[i]=='/')
		{
			y=pop(stack)-'0';
			x=pop(stack)-'0';
			if(post[i]=='+')
				result=(x+y);
			else if(post[i]=='-')
				result=(x-y);
			else if(post[i]=='*')
				result=(x*y);
			else if(post[i]=='/')
				result=(x/y);
			push(stack,result+'0');
		}
		else
			push(stack,post[i]);
	}
	cout<<"Value of expression : "<<result<<endl;
	string S[n],Temp;
	for(int i=0;i<k;i++)
	{
		if(post[i]=='+'||post[i]=='-'||post[i]=='*'||post[i]=='/')
		{
			string x=pop(S);
			string y=pop(S);
			Temp=post[i]+y+x;
			push(S,Temp);
		}
		else
		{
			Temp=post[i];
			push(S,Temp);
		}
	}
	cout<<"Post fix expression : "<<S[0];
	return 0;
}
char pop(char stack[])
{
	if(top==-1)
		return '#';
	top--;
	return stack[top+1];
}
string pop(string S[])
{
	if(Top==-1)
		return "#";
	Top--;
	return S[Top+1];
}
void push(char stack[],char x)
{
	if(top==n)
		return;
	top++;
	stack[top]=x;
}
void push(string S[],string x)
{
	if(Top==n)
		return;
	Top++;
	S[Top]=x;
}
int prior(char c)
{
	if(c=='*'||c=='/')
		return 2;
	else if(c=='+'||c=='-')
		return 1;
	else
		return 0;
}
