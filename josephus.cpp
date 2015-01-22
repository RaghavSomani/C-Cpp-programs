#include<iostream>
using namespace std;
void enqueue(int Q[],int x,int n);
int dequeue(int Q[],int n);
int head=0,tail=0;
int main()
{
	cout<<"Number of people : ";
	int n,k,temp;
	cin>>n;
	int Q[n+1];
	for(int i=0;i<n;i++)
		Q[i]=i;
	tail=n;
	cout<<"Number of people to skip : ";
	cin>>k;
	while((head+1)%(n+1)!=tail)
	{
		for(int i=0;i<k;i++)
			enqueue(Q,dequeue(Q,n+1),n+1);
		dequeue(Q,n+1);
	}
	cout<<"Last persone to stay alive is : "<<Q[head]<<endl;
	return 0;
}
void enqueue(int Q[],int x,int n)
{
	Q[tail]=x;
	if(tail==n-1)
		tail=0;
	else
		tail++;
}
int dequeue(int Q[],int n)
{
	int x=Q[head];
	if(head==n-1)
		head=0;
	else
		head++;
	return x;
}