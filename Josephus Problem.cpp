#include<iostream>
using namespace std;
void enqueue(int Q[],int x,int n);
int dequeue(int Q[],int n);
int head=0,tail=0;
int main()
{
	cout<<"Number of people : ";
	int n,k;
	cin>>n;
	int Q[n];
	for(int i=0;i<n;i++)
		Q[i]=i;
	cout<<"Number of people to be skipped : ";
	cin>>k;
	int temp;
	while((head+1)%n!=tail)
	{
		for(int i=0;i<k;i++)
			enqueue(Q,dequeue(Q,n),n);
		dequeue(Q,n);
	}
	cout<<Q[head];
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
