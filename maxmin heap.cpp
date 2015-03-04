#include <iostream>
#include <cmath>
using namespace std;
void TickleDown(int a[], int i, int n);
void TickleDownMin(int a[], int i, int n);
void TickleDownMax(int a[], int i, int n);
void BubbleUp(int a[], int i, int n);
void BubbleUpMin(int a[], int i, int n);
void BubbleUpMax(int a[], int i, int n);
void Insert(int a[], int x, int &n);
void DeleteMax(int a[], int& n);
void DeleteMin(int a[], int& n);
int level(int i);
int main()
{
	int n,x;
	cout<<"Number of elements : ";
	cin>>n;
	int size=n;
	int a[2*n+10];
	n=0;
	for(int i=0;i<size;i++)
	{
		cin>>x;
		Insert(a,x,n);
	}
	cout<<"MinMax Heap : ";
	for(int i=0;i<n;cout<<a[i++]<<" \n"[i==n-1]);
	int choice;
	do
	{
		cout<<"1. Insert\n";
		cout<<"2. Minimum\n";
		cout<<"3. Maximum\n";
		cout<<"4. Delete Min\n";
		cout<<"5. Delete Max\n";
		cout<<"6. Exit\n";
		cout<<"Enter choice : ";
		cin>>choice;
		switch(choice)
		{
			case 1:
				cout<<"Element to insert : ";
				cin>>x;
				Insert(a,x,n);
				break;
			case 2:
				cout<<"Minimum : "<<((a[1]<a[2])?a[1]:a[2])<<endl;
				break;
			case 3:
				cout<<"Maximum : "<<a[0]<<endl;
				break;
			case 4:
				DeleteMin(a,n);
				break;
			case 5:
				DeleteMax(a,n);
				break;
			case 6:
				break;
			default : break;
		}
		cout<<endl<<"Heap after operation : ";
		for(int i=0;i<n;cout<<a[i++]<<" \n"[i==n-1]);
	}while(choice!=6);
	return 0;
}
int level(int i)		//odd = max level, even = min level
{
	return (int)log2(i+1)+1;
}
void Insert(int a[],int x, int &n)
{
	n++;
	a[n-1]=x;
	BubbleUp(a,n-1,n);
}
void BubbleUp(int a[], int i, int n)
{
	int p=(i-1)/2;
	if(level(i)%2==0)
	{
		if(i>0&&a[i]>a[p])
		{
			a[i]=(a[p]+a[i])-(a[p]=a[i]);
			BubbleUpMax(a,p,n);
		}
		else
			BubbleUpMin(a,i,n);
	}
	else
	{
		if(i>0&&a[i]<a[p])
		{
			a[i]=(a[p]+a[i])-(a[p]=a[i]);
			BubbleUpMin(a,p,n);
		}
		else
			BubbleUpMax(a,i,n);
	}
}
void BubbleUpMin(int a[], int i, int n)
{
	int p=(i-1)/2,g;
	if(p>0)
		g=(i-3)/4;
	else
		return;
	if(a[i]<a[g])
	{
		a[i]=(a[g]+a[i])-(a[g]=a[i]);
		BubbleUpMin(a,g,n);
	}
}
void BubbleUpMax(int a[], int i, int n)
{
	int p=(i-1)/2,g;
	if(p>0)
		g=(i-3)/4;
	else
		return;
	if(a[i]>a[g])
	{
		a[i]=(a[g]+a[i])-(a[g]=a[i]);
		BubbleUpMax(a,g,n);
	}
}
void DeleteMax(int a[], int& n)
{
	a[0]=a[n-1];
	n--;
	TickleDownMax(a,0,n);
}
void DeleteMin(int a[], int& n)
{
	int min=0;
	if(n==2)
		min=1;
	else
		min=(a[1]<a[2])?1:2;
	a[min]=a[n-1];
	n--;
	TickleDownMin(a,min,n);
}
void TickleDown(int a[], int i, int n)
{
	if(level(i)%2==1)			//1 for maxmin heap, 0 for minmax
		TickleDownMax(a,i,n);
	else
		TickleDownMin(a,i,n);
}
void TickleDownMin(int a[], int i, int n)
{
	int m=i,p;				//index of smallest amongst children and grandchildren(if any)
	if(i<=(n-2)/2)
	{
		for(int j=(4*i+3);j<=(4*i+6)&&j<n;j++)
			m=(a[j]<a[m])?j:m;
		if(m>=(4*i+3)&&m<=(4*i+6))
		{
			if(a[m]<a[i])
			{
				a[m]=(a[i]+a[m])-(a[i]=a[m]);
				p=(m-1)/2;
				if(a[m]>a[p])
					a[m]=(a[p]+a[m])-(a[p]=a[m]);
				TickleDownMin(a,m,n);
			}
		}
		else if(m==(2*i+1)||m==(2*i+2))
		{
			if(a[m]<a[i])
				a[m]=(a[i]+a[m])-(a[i]=a[m]);
		}
	}
}
void TickleDownMax(int a[], int i, int n)
{
	int m=i,p;				//index of largest amongst children and grandchildren(if any)
	if(i<=(n-2)/2)
	{
		for(int j=(4*i+3);j<=(4*i+6)&&j<n;j++)
			m=(a[j]>a[m])?j:m;
		if(m>=(4*i+3)&&m<=(4*i+6))
		{
			if(a[m]>a[i])
			{
				a[m]=(a[i]+a[m])-(a[i]=a[m]);
				p=(m-1)/2;
				if(a[m]<a[p])
					a[m]=(a[p]+a[m])-(a[p]=a[m]);
				TickleDownMax(a,m,n);
			}
		}
		else if(m==(2*i+1)||m==(2*i+2))
		{
			if(a[m]>a[i])
				a[m]=(a[i]+a[m])-(a[i]=a[m]);
		}
	}
}