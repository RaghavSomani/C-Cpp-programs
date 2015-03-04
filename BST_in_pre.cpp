#include <iostream>
#define n 12
using namespace std;
struct Node
{
	Node* left;
	Node* right;
	int key;
	int x;
	int y;
};
int tree[n][n]={0};
Node* BuildTree(int in[], int pre[], int start, int end);	// start and end are of in[]
void InOrder(Node* root);
void PreOrder(Node* root);
Node* NewNode(int key);
int LinearSearch(int a[],int key,int low, int high);
void Depth(Node* head);
int main()
{
	int in[n],pre[n];
	cout<<"PreOrder : ";
	for(int i=0;i<n;cin>>pre[i++]);
	cout<<"InOrder  : ";
	for(int i=0;i<n;cin>>in[i++]);
	Node* root=BuildTree(in,pre,0,n-1);
	root->y=0;
	Depth(root);
	cout<<"InOrder : ";
	InOrder(root);
	cout<<endl;
	cout<<"PreOrder : ";
	PreOrder(root);
	cout<<endl;
	for(int j=0;j<n;j++)
	{
		int flag=0;
		for(int i=0;i<n;i++)
		{
			if(tree[i][j]==0)
				cout<<"   ";
			else
			{
				cout<<" "<<tree[i][j]<<" ";
				flag=1;
			}
		}
		if(flag==0)
			break;
		cout<<endl<<endl;
	}
	cout<<endl;
	return 0;
}
Node* BuildTree(int in[], int pre[], int start, int end)	// start and end are of in[]
{
	static int preIndex=0;
	int inIndex;
	if(start>end)
		return NULL;
	Node* temp=NewNode(pre[preIndex++]);
	if(start==end)
		return temp;
	inIndex=LinearSearch(in,temp->key,start,end);
	temp->left=BuildTree(in,pre,start,inIndex-1);
	temp->right=BuildTree(in,pre,inIndex+1,end);
	return temp;
}
void Depth(Node* head)
{
	if(head->left)
	{
		head->left->y=head->y+1;
		Depth(head->left);
	}
	if(head->right)
	{
		head->right->y=head->y+1;
		Depth(head->right);
	}
}
void InOrder(Node* head)
{
	static int x=0;
	if(head==NULL)
		return;
	InOrder(head->left);
	cout<<head->key<<" ";
	head->x=x++;
	InOrder(head->right);
}
void PreOrder(Node* head)
{
	if(head==NULL)
		return;
	cout<<head->key<<endl;
	tree[head->x][head->y]=head->key;
	PreOrder(head->left);
	PreOrder(head->right);
}
Node* NewNode(int key)
{
	Node* z=new Node;
	z->key=key;
	z->left=NULL;
	z->right=NULL;
	return z;
}
int LinearSearch(int a[],int key,int low, int high)
{
	for(int i=low;i<=high;i++)
		if(a[i]==key)
			return i;
}
