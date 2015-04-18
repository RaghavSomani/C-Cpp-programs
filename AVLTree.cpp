#include <iostream>
#include <cmath>
using namespace std;
struct Node
{
	int key;
	Node* left;
	Node* right;
	Node* p;
};
Node* NewNode(int k)
{
	Node* z=new Node;
	z->key=k;
	z->left=NULL;
	z->right=NULL;
	z->p=NULL;
	return z;
}
Node* root=NewNode(2);
int Height(Node* root)
{
	if(root==NULL)
		return -1;
	else
		return max(Height(root->left),Height(root->right))+1;
}
int DiffHeight(Node* root)
{
	return abs(Height(root->left)-Height(root->right));
}
void LeftRotate(Node* x)
{
	Node* y=x->right;
	x->right=y->left;
	if(y->left!=NULL)
		y->left->p=x;
	y->p=x->p;
	if(x->p==NULL)
		root=y;
	else if(x==x->p->left)
		x->p->left=y;
	else
		x->p->right=y;
	y->left=x;
	x->p=y;
}
void RightRotate(Node* x)
{
	Node* y=x->left;
	x->left=y->right;
	if(y->right!=NULL)
		y->right->p=x;
	y->p=x->p;
	if(x->p==NULL)
		root=y;
	else if(x==x->p->right)
		x->p->right=y;
	else
		x->p->left=y;
	y->right=x;
	x->p=y;
}
void Insert(Node *x, int k)
{
	Node* z=NewNode(k);
	Node* y=NULL;
	while(x!=NULL)
	{
		y=x;
		if(k<=x->key)
			x=x->left;
		else
			x=x->right;
	}
	z->p=y;
	if(y==NULL)
		x=z;
	else if(k<y->key)
		y->left=z;
	else
		y->right=z;
	
	while(z!=NULL && DiffHeight(z)<=1)
		z=z->p;
	if(z==NULL)
		return;
	//Finding Conflict
	
	if(Height(z->left) > Height(z->right))
		y=z->left;
	else if(Height(z->left) < Height(z->right))
		y=z->right;
	
	if(Height(y->left) >= Height(y->right))
		x=y->left;
	else
		x=y->right;
	
	//Cases
	
	if(y==z->right && x==y->right)
		LeftRotate(z);
	if(y==z->left && x==y->left)
		RightRotate(z);
	if(y==z->left && x==y->right)
	{
		LeftRotate(y);
		RightRotate(z);
	}
	if(y==z->right && x==y->left)
	{
		RightRotate(y);
		LeftRotate(z);
	}
}
void PreOrder(Node* root)
{
	if(root!=NULL)
	{
		cout<<root->key<<" ";
		PreOrder(root->left);
		PreOrder(root->right);
	}
}
int main()
{
	Insert(root,3);
	Insert(root,4);
	Insert(root,5);
	Insert(root,6);
	Insert(root,7);
	Insert(root,8);
	Insert(root,9);
	Insert(root,10);
	//Insert(root,11);
	PreOrder(root);
	cout<<endl;
	return 0;
}
