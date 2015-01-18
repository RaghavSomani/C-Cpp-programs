#include <iostream>
using namespace std;
struct Node
{
	int key;
	Node* next;
	Node* prev;
};
Node* NewNode(int k);
Node* Search(Node* nil, int k);
Node* Insert(Node* head, int k);
void Delete(Node* x);
void Print(Node* nil);
Node* Merge(Node* nil11,Node* nil2);
Node* Reverse(Node* nil);
int main()
{
	struct Node* nil1 = NewNode(0);
	struct Node* nil2 = NewNode(0);
	for(int i=1;i<=3;i++)
		nil1 = Insert(nil1,i);
	for(int i=4;i<=7;i++)
		nil2 = Insert(nil2,i);
	nil1 = Merge(nil1,nil2);
	Print(nil1);
	nil1 = Reverse(nil1);
	Print(nil1);
	struct Node* temp=nil1->next->next;
	temp=Insert(temp,0);
	Print(nil1);
	Delete(temp->next);
	Print(nil1);
	return 0;
}
Node* NewNode(int k)
{
	Node* x = new Node;
	x->next = x;
	x->prev = x;
	x->key  = k;
	return x;
}
Node* Insert(Node* nil, int k)
{
	Node* x         = NewNode(k);
	x->next         = nil->next;
	nil->next->prev = x;
	nil->next       = x;
	x->prev         = nil;
	return nil;
}
Node* Search(Node* nil, int k)
{
	Node* x = nil->next;
	while(x!=nil && x->key!=k)
		x = x->next;
	return x;
}
void Delete(Node* x)
{
	Node* temp    = x;
	x->prev->next = x->next;
	x->next->prev = x->prev;
	delete temp;
}
void Print(Node* nil)
{
	Node* head = nil->next;
	Node* temp = head;
	while(temp!=nil)
	{
		cout<<temp->key<<" ";
		temp = temp->next;
	}
	cout<<endl;
}
Node* Merge(Node* nil1,Node* nil2)
{
	nil1->prev->next = nil2->next;
	nil2->next->prev = nil1->prev;
	nil2->prev->next = nil1;
	nil1->prev       = nil2->prev;
	nil2->next       = NULL;
	nil2->prev       = NULL;
	delete nil2;
	return nil1;
}
Node* Reverse(Node* nil)
{
	struct Node* temp = nil->next;
	struct Node* n;
	struct Node* p;
	while(temp!=nil)
	{
		n=temp->next;
		p=temp->prev;
		swap(temp->next,temp->prev);
		temp=n;
	}
	swap(temp->next,temp->prev);
	return nil;
}
