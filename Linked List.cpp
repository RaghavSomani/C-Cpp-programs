#include <iostream>
using namespace std;
class Node
{
public:
	Node* next;
	int data;
	Node(int d): data(d), next(NULL) {};
};
class List
{
public:
	Node* head;
	List(): head(NULL) {};
	~List()
	{
		Node* current = head;
		Node* prev = NULL;
		while(current!=NULL)
		{
			if(prev)
				delete prev;
			prev = current;
			current = current->next;
		}
		if(prev)
			delete prev;
		head = NULL;
	}
	void push(int data)
	{
		Node* new_node = new Node(data);
		new_node->next = head;
		head = new_node;
	}
	void pop(void)
	{
		if(head)
		{	
			Node* temp = head;
			head = head->next;
			delete temp;
		}
	}
	void print(void)
	{
		Node* temp = head;
		while(temp != NULL)
		{
			cout<<temp->data<<" ";
			temp = temp->next;
		}
		cout<<endl;
	}
	void insert_after(Node* prev, int d)
	{
		Node* z = new Node(d);
		Node* dest = prev->next;
		prev->next = z;
		z->next = dest;
	}
	Node* search(int x)
	{
		Node* temp = head;
		while(temp!=NULL)
		{
			if(temp->data==x)
				return temp;
			temp = temp->next;
		}
		return temp;
	}
	void append(int x)
	{
		Node* z = new Node(x);
		Node* temp = head;
		if(!head)
		{
			head = z;
			return;
		}
		while(temp->next != NULL)
			temp = temp->next;
		temp->next = z;
	}
	void del(int x)
	{
		Node* temp = head;
		Node* prev = NULL;
		if(head && head->data == x)
		{
			pop();
			return;
		}
		while(temp != NULL && temp->data != x)
		{
			prev = temp;
			temp = temp->next;
		}
		if(temp==NULL)
		{
			cout<<x<<" not found\n";
			return;
		}
		if(temp->data == x)
		{
			prev->next = temp->next;
			delete temp;
		}
	}
};
int main()
{
	List L;
	int n,x,choice;
	cout<<"Number of elements in Linked list : ";
	cin>>n;
	Node* t;
	for(int i=0;i<n;i++)
	{
		cin>>x;
		L.push(x);
	}
	L.print();
	do
	{
		cout<<"1. Search\n";
		cout<<"2. Insert after\n";
		cout<<"3. Append\n";
		cout<<"4. Delete\n";
		cout<<"0. Exit\n";
		cout<<"Enter a choice : ";
		cin>>choice;
		switch(choice)
		{
			case 1: cout<<"Search for : ";
					cin>>x;
					if(L.search(x))
						cout<<x<<" found\n";
					else
						cout<<x<<" not found\n";
					break;	

			case 2: cout<<"Insert after : ";
					cin>>x;
					t = L.search(x);
					if(t)
					{
						cout<<x<<" found\n";
						cout<<"Insert : ";
						cin>>x;
						L.insert_after(t,x);
						L.print();
					}
					else
						cout<<x<<" not found\n";
			
			case 3: cout<<"Append : ";
					cin>>x;
					L.append(x);
					L.print();
					break;
			case 4: cout<<"Delete : ";
					cin>>x;
					L.del(x);
					L.print();
			default:cout<<"Bye :)\n";
		}
	}while(choice!=0);
	return 0;
}