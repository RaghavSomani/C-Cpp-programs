#include <iostream>
#include <fstream>
struct BstNode
{
	int key;
	BstNode* p;
	BstNode* left;
	BstNode* right;
};
void InOrder(BstNode* x);
BstNode* Search(BstNode* x,int k);
BstNode* Minimum(BstNode* x);
BstNode* Maximum(BstNode* x);
BstNode* Successor(BstNode* x);
BstNode* Predecessor(BstNode* x);
BstNode* Insert(BstNode* x,int k);
BstNode* Delete(BstNode* x,int k);
using namespace std;
int main()
{
	int temp;
	BstNode* root=NULL;
	ifstream fp("input.txt");
	while(!fp.eof())
	{
		fp>>temp;
		root=Insert(root,temp);
	}	
	InOrder(root);
	cout<<endl;
	cout<<endl;
	fp.clear();
	fp.seekg(0,ios::beg);
	while(!fp.eof())
	{
		fp>>temp;
		root=Delete(root,temp);
	}
	InOrder(root);
}
void InOrder(BstNode* x)
{
	if(x==NULL)
		return
	InOrder(x->left);
	cout<<x->key<<endl;
	InOrder(x->right);
}
BstNode* Search(BstNode* x,int k)
{
	while(x!=NULL && k!=x->key)
	{
		if(k<x->key)
			x=x->left;
		else
			x=x->right;
	}
	return x;
}
BstNode* Minimum(BstNode* x)
{
	while(x->left!=NULL)
		x=x->left;
	return x;
}
BstNode* Maximum(BstNode* x)
{
	while(x->right!=NULL)
		x=x->right;
	return x;
}
BstNode* Successor(BstNode* x)
{
	if(x->right!=NULL)
		return Minimum(x->right);
	BstNode* y=x->p;
	while(y!=NULL && x==y->right)
	{
		x=y;
		y=y->p;
	}
	return y;
}
BstNode* Predecessor(BstNode* x)
{
	if(x->left!=NULL)
		return Maximum(x->left);
	BstNode* y=x->p;
	while(y!=NULL && x==y->left)
	{
		x=y;
		y=y->p;
	}
	return y;
}
BstNode* Insert(BstNode* root,int k)
{
	BstNode* z=new BstNode;
	z->key=k;
	z->left=NULL;
	z->right=NULL;
	z->p=NULL;
	BstNode* y=NULL;
	BstNode* x=root;
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
		root=z;
	else if(k<=y->key)
		y->left=z;
	else
		y->right=z;	
	return root;
}
BstNode* Delete(BstNode* x,int k)
{
	if(x==NULL)
		return x;
	else if(k<x->key)
		x->left=Delete(x->left,k);
	else if(k>x->key)
		x->right=Delete(x->right,k);
	else
	{
		if(x->left==NULL && x->right==NULL)
		{
			delete x;
			x=NULL;
		}
		else if(x->left==NULL)
		{
			BstNode* temp=x;
			x=x->right;
			delete temp;
		}
		else if(x->right==NULL)
		{
			BstNode* temp=x;
			x=x->left;
			delete temp;
		}
		else
		{
			BstNode* temp=Minimum(x->right);
			x->key=temp->key;
			x->right=Delete(x->right,temp->key);
		}
	}
	return x;
}
