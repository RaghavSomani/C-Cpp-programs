#include <iostream>
using namespace std;
struct Node
{
	Node* p;
	Node* left;
	Node* right;
	int key;
};
Node* NewNode(int k);
Node* Insert(Node* root, int k);
void InOrder(Node* root);
Node* Search(Node* root, int k);
Node* Maximum(Node* root);
Node* Minimum(Node* root);
Node* Successor(Node* x);
Node* Predecessor(Node* x);
int main()
{
	int n,k;
	cout<<"Number of elements : ";
	cin>>n;
	Node* root=NULL;
	for(int i=0;i<n;i++)
	{
		cin>>k;
		root=Insert(root,k);
	}
	InOrder(root);
	cout<<endl;
	cout<<"Maximum : "<<(Maximum(root)->key)<<endl;
	cout<<"Minimum : "<<(Minimum(root)->key)<<endl;
	cout<<"Key to search : ";
	cin>>k;
	Node* z=Search(root,k);
	if(z==NULL)
		cout<<k<<" not Found\n";
	else
		cout<<k<<" found\n";
	cout<<"Successor of : ";
	cin>>k;
	cout<<Successor(Search(root,k))->key<<endl;
	cout<<"Predecessor of : ";
	cin>>k;
	cout<<Predecessor(Search(root,k))->key<<endl;
	return 0;
}
Node* NewNode(int k)
{
	Node* z=new Node;
	z->p=NULL;
	z->left=NULL;
	z->right=NULL;
	z->key=k;
	return z;
}
Node* Insert(Node* root, int k)
{
	Node* y=NULL;
	Node* x=root;
	Node* z=NewNode(k);
	while(x!=NULL)
	{
		y=x;
		if(z->key < x->key)
			x=x->left;
		else
			x=x->right;
	}
	z->p=y;
	if(y==NULL)
		root=z;
	else if(z->key <= y->key)
		y->left=z;
	else
		y->right=z;
	return root;
}
void InOrder(Node* root)
{
	if(root==NULL)
		return;
	InOrder(root->left);
	cout<<root->key<<" ";
	InOrder(root->right);
}
Node* Search(Node* root, int k)
{
	while(root!=NULL && root->key!=k)
	{
		if(k <= root->key)
			root=root->left;
		else
			root=root->right;
	}
	return root;
}
Node* Maximum(Node* root)
{
	// Node* x=root;
	while(root->right!=NULL)
		root=root->right;
	return root;
}
Node* Minimum(Node* root)
{
	// Node* x=root;
	while(root->left!=NULL)
		root=root->left;
	return root;
}
Node* Successor(Node* x)
{
	if(x->right)
		return Minimum(x->right);
	Node* y=x->p;
	while(y!=NULL && x== y->right)
	{
		x=y;
		y=y->p;
	}
	return y;
}
Node* Predecessor(Node* x)
{
	if(x->left)
		return Maximum(x->left);
	Node* y=x->p;
	while(y!=NULL && x== y->left)
	{
		x=y;
		y=y->p;
	}
	return y;
}