#include <iostream>
#include <map>
using namespace std;
class Node
{
public:
	Node* left;
	Node* right;
	Node* random;
	int data;
	Node(int k=0): data(k), left(NULL), right(NULL), random(NULL) {};
	void destruct(void)
	{
		if(this!=NULL)
		{
			left->destruct();
			left = NULL;
			right->destruct();
			right = NULL;
			random = NULL;
			delete this;
		}
	}
};
class BT
{
public:
	Node* root;
	BT(): root(NULL) {};
	~BT()
	{
		root->destruct();
		root = NULL;
	}
	Node* newNode(int k)
	{
		return (new Node(k));
	}
	void inorder(Node* x)
	{
		if(x==NULL)
			return;
		inorder(x->left);
		cout<<x->data<<" ";
		inorder(x->right);
	}
	Node* clone(Node* x)
	{
		if(x==NULL)
			return NULL;
		Node* l = clone(x->left);
		Node* r = clone(x->right);
		root = newNode(x->data);
		root->left = l;
		root->right = r;
	}
	void inorder_random(Node* x)
	{
		if(x==NULL)
			return;
		inorder_random(x->left);
		if(x->random)
			cout<<x->random->data<<" ";
		else
			cout<<"NULL ";
		inorder_random(x->right);
	}
};
void iterate(map<Node*, Node*>* M, Node* x, Node* y)
{
	if(x==NULL)
		return;
	iterate(M,x->left,y->left);
	(*M)[x] = y;
	iterate(M,x->right,y->right);
}
map<Node*, Node*>* pointerMap(BT* bt1, BT* bt2)
{
	map<Node*,Node*>* M = new map<Node*,Node*>;
	iterate(M,bt1->root,bt2->root);
	return M;
}
void clone_random(map<Node*,Node*>* M, map<Node*,Node*>* M_reverse, Node* x)
{
	if(x==NULL)
		return;
	clone_random(M,M_reverse,x->left);
	x->random = (*M)[(*M_reverse)[x]->random];
	clone_random(M,M_reverse,x->right);
}
int main()
{
	int n,x;
	BT Tree;
	Tree.root = Tree.newNode(1);
	Tree.root->left = Tree.newNode(2);
	Tree.root->right = Tree.newNode(3);
	Tree.root->left->left = Tree.newNode(4);
	Tree.root->left->right = Tree.newNode(5);
	Tree.root->random = Tree.root->left->right;
	Tree.root->left->left->random = Tree.root;
	Tree.root->left->right->random = Tree.root->right;
	Tree.inorder(Tree.root);
	cout<<endl;

	BT ClonedBT;
	ClonedBT.root = ClonedBT.clone(Tree.root);
	ClonedBT.inorder(ClonedBT.root);
	cout<<endl;

	map<Node*,Node*>* M = pointerMap(&Tree, &ClonedBT);
	map<Node*,Node*>::iterator it;
	// cout<<"Pointer to pointer map :\n";
	// for(it=M->begin(); it!=M->end();it++)
	// 	cout<<it->first<<" -> "<<it->second<<endl;
	
	map<Node*,Node*>* M_reverse = new map<Node*,Node*>;
	for(it=M->begin();it!=M->end();it++)
		(*M_reverse)[it->second]=it->first;

	// cout<<"Reverse map :\n";
	// for(it=M_reverse->begin(); it!=M_reverse->end();it++)
	// 	cout<<it->first<<" -> "<<it->second<<endl;
	clone_random(M,M_reverse,ClonedBT.root);
	
	Tree.inorder_random(Tree.root);
	cout<<endl;
	ClonedBT.inorder_random(ClonedBT.root);
	cout<<endl;
	return 0;
}