#include <iostream>
using namespace std;
class Node
{
public:
	Node* left;
	Node* right;
	int data;
	Node(int k=0): data(k), left(NULL), right(NULL) {};
	void destruct(void)
	{
		if(this!=NULL)
		{
			left->destruct();
			left = NULL;
			right->destruct();
			right = NULL;
			delete this;
		}
	}
};
class BT
{
public:
	Node* root;
	BT(): root(NULL) {};
	// ~BT()
	// {
	// 	root->destruct();
	// 	root = NULL;
	// }
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
	Node* get_left_leaf(Node* x)
	{
		if(x->left==NULL && x->right==NULL)
			return x;
		else
		{
			if(x->left)
				return get_left_leaf(x->left);
			else
				return get_left_leaf(x->right);
		}
	}
	Node* get_right_leaf(Node* x)
	{
		if(x->left==NULL && x->right==NULL)
			return x;
		else
		{
			if(x->right)
				return get_right_leaf(x->right);
			else
				return get_right_leaf(x->left);
		}
	}
	void join_leaves(Node* x)
	{
		if(x==NULL)
			return;
		else
		{
			join_leaves(x->left);
			if(x->left && x->right)
				get_right_leaf(x->left)->right = get_left_leaf(x->right);
			join_leaves(x->right);
		}
	}
	Node* DLL(Node* x, int dir)
	{
		if(x==NULL)
			return NULL;
		if(x->left)
		{
			Node* l = DLL(x->left,0);
			l->right = x;
			x->left = l;
		}
		if(x->right)
		{
			Node* r = DLL(x->right,1);
			r->left = x;
			x->right = r;
		}

		Node* temp = x;
		if(dir==0)
		{
			while(temp->right != NULL)
				temp = temp->right;
		}
		else if(dir==1)
		{
			while(temp->left != NULL)
				temp = temp->left;
		}
		return temp;
	}
};
int main()
{
	int n,x;
	BT Tree;
	Tree.root = Tree.newNode(50);
	Tree.root->left = Tree.newNode(7);
	Tree.root->right = Tree.newNode(60);
	Tree.root->right->left = Tree.newNode(70);
	Tree.root->right->right = Tree.newNode(90);
	Tree.root->left->left = Tree.newNode(2);
	Tree.root->left->left->left = Tree.newNode(1);
	Tree.root->left->right = Tree.newNode(30);
	Tree.root->left->right->left = Tree.newNode(15);
	Tree.root->left->left->right = Tree.newNode(3);
	Tree.root->left->left->right->right = Tree.newNode(5);

	Node* current = Tree.get_left_leaf(Tree.root);
	
	cout<<"Connect leaves (y/n) : ";
	char ch;
	cin>>ch;
	if(ch=='y'||ch=='Y')
	{
		Tree.join_leaves(Tree.root);
		while(current)
		{
			cout<<current->data<<" ";
			current = current->right;
		}
		return 0;
	}
	cout<<"Convert BT to DLL (y/n) : ";
	cin>>ch;
	if(ch=='y'||ch=='Y')
	{
		current = Tree.DLL(Tree.root,1);
		while(current)
		{
			cout<<current->data<<" ";
			current = current->right;
		}
	}
	return 0;
}