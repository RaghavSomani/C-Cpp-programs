#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;

class Node
{
public:
	int key;
	char data;
	Node* p;
	int d;
	int pos;
	Node(int k=0)		{	key=k;	pos=k;	d=k;	};
	Node(int k, char d)	{	key=k;	data=d;	pos=k;	};
	Node(const Node& v)	{	key=v.key;	data=v.data;	};
};

class Priority_Queue
{
public:
	vector<Node*> V;
	int n;
	vector<Node*> build_min_heap(void)
	{
		n = V.size();
		for(int i=(n-2)/2;i>=0;i--)
			min_heapify(i);
		for(int i=0;i<n;i++)
			V[i]->pos=i;
	};
	void min_heapify(int i)
	{
		n = V.size();
		int l, r, smallest;
		while(1)
		{
			l=(2*i)+1;
			r=(2*i)+2;
			if(l<n && (V[l]->d < V[i]->d))
				smallest=l;
			else
				smallest=i;
			if(r<n && (V[r]->d < V[smallest]->d))
				smallest=r;
			if(smallest==i)
				break;
			swap(V[smallest],V[i]);
			V[smallest]->pos=smallest;
			V[i]->pos=i;
			i=smallest;
		}
	};
	void decrease_key(int i, int k)
	{
		V[i]->d=k;
		while(i>0 && (V[(i-1)/2]->d > V[i]->d))
		{
			swap(V[i],V[(i-1)/2]);
			V[i]->pos=i;
			V[(i-1)/2]->pos=(i-1)/2;
			i=(i-1)/2;
		}
	}
	Node* extract_min(void)
	{
		Node* min=V[0];
		V[0]=V[n-1];
		V[0]->pos=0;
		V.pop_back();
		min_heapify(0);
		n=V.size();
		return min;
	}
};

int main()
{
	srand(time(NULL));
	vector<Node*> A(10);
	for(int i=0;i<10;i++)
		A[i] = new Node(rand()%10);
	Priority_Queue Q;
	int n=10;
	Q.V.resize(10);
	for(int i=0;i<n;i++)
		Q.V[i] = A[i];
	Q.build_min_heap();
	cout<<endl;
	cout<<"pos\n";
	for(auto i:Q.V)
		cout<<i->pos<<" ";
	cout<<endl;
	for(auto i:Q.V)
		cout<<i->d<<" ";
	cout<<endl;
	Node* u = Q.extract_min();
	cout<<u->d<<endl;
	for(auto i:Q.V)
		cout<<i->d<<" ";
	cout<<endl;
	cout<<"pos\n";
	for(auto i:Q.V)
		cout<<i->pos<<" ";
	Q.decrease_key(2,0);
	cout<<endl;
	for(auto i:Q.V)
		cout<<i->d<<" ";
	cout<<"\npos\n";
	for(auto i:Q.V)
		cout<<i->pos<<" ";
	return 0;
}