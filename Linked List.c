#include<stdio.h>
#include<stdlib.h>
struct node
{
	int data;
	struct node* next;
};
struct node* head;
struct node* new_ptr(int x)
{
	struct node* newnode=(struct node*)malloc(sizeof(struct node));
	newnode->data=x;
	newnode->next=NULL;
	return newnode;
}
void insert_beg(int x)
{
	struct node* temp=new_ptr(x);
	temp->next=head;
	head=temp;
}
void insert(int x, int pos)
{
	struct node* newnode=new_ptr(x);
	struct node* temp=head;
	int i;
	for(i=0;i<(pos-2);i++)
		temp=temp->next;
	newnode->next=temp->next;
	temp->next=newnode;
}
void print()
{
	struct node* temp;
	temp=head;
	while(temp!=NULL)
	{
		printf("%d ", temp->data);
		temp=temp->next;
	}
}
void delete_last()
{
	struct node* temp=head;
	while(temp->next->next!=NULL)
	{
		temp=temp->next;
	}
	temp->next=NULL;	
}
void main()
{
	int x,y,pos,z;
	char c;
	printf("Enter number: ");
	scanf("%d", &y);
	head=new_ptr(y);
	do
	{
		printf("Enter number: ");
		scanf("%d", &x);
		insert_beg(x);
		printf("Do you want to enter more elements??");
		scanf("\n%c", &c);
	}while(c=='y'||c=='Y');
	print();
	printf("\nPosition: ");
	scanf("%d", &pos);
	printf("Data: ");
	scanf("%d", &z);
	insert(z,pos);
	print();
	printf("\nAfter deleting last element\n");
	delete_last();
	print();
}
