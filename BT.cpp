#include <iostream>
#include <stack>
#include <climits>
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
	Node* search(int k)
	{
		Node* temp = root;
		while(temp!=NULL && temp->data!=k)
		{
			if(temp->data < k)
				temp = temp->right;
			else
				temp = temp->left;
		}
		return temp;
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
			while(temp->right != NULL)
				temp = temp->right;
		else if(dir==1)
			while(temp->left != NULL)
				temp = temp->left;
		return temp;
	}
	Node* min(Node* x)
	{
		Node* current = x;
		while(current->left != NULL)
			current = current->left;
		return current;
	}
	Node* max(Node* x)
	{
		Node* current = x;
		while(current->right != NULL)
			current = current->right;
		return current;
	}
	Node* predecessor(Node* x)
	{
		if(x->left)
			return max(x->left);
		Node* prev = NULL;
		Node* current = root;
		while(current != x)
		{
			if(x->data < current->data)
			{
				current = current->left;
			}
			else
			{
				prev = current;
				current = current->right;
			}
		}
		return prev;
	}
	Node* successor(Node* x)
	{
		if(x->right)
			return min(x->right);
		Node* prev = NULL;
		Node* current = root;
		while(current != x)
		{
			if(x->data < current->data)
			{
				prev = current;
				current = current->left;
			}
			else
				current = current->right;
		}
		return prev;
	}
	Node* parent(Node* x)
	{
		Node* prev = NULL;
		Node* current = root;
		while(current!=x)
		{
			prev = current;
			if(x->data < current->data)
				current = current->left;
			else
				current = current->right;
		}
		return prev;
	}
	Node* constructTree(int a[], int n, int min, int max, int* preIndex)
	{
		if(*preIndex>=n)
			return NULL;
		Node* root = NULL;
		int key = a[*preIndex];
		if(key > min && key < max)
		{
			root = newNode(key);
			(*preIndex)++;
			if(*preIndex < n)
			{
				root->left = constructTree(a,n,min,key,preIndex);
				root->right = constructTree(a,n,key,max,preIndex);
			}
		}
		return root;
	}
	int height(Node* x)
	{
		if(x==NULL)
			return 0;
		return 1+std::max(height(x->left),height(x->right));
	}
	int getWidth(Node* x, int level)
	{
		if(x==NULL)
			return 0;
		if(level==1)
			return 1;
		else if(level > 1)
			return getWidth(x->left,level-1)+getWidth(x->right,level-1);
	}
	int getMaxWidth(Node* x)
	{
		int h = height(x), max=0;
		int width;
		for(int i=1;i<=h;i++)
		{
			width = getWidth(x,i);
			if(width > max)
				max = width;
		}
		return max;
	}
	void mirror(Node* root)
	{
		if(!root)
			return;
		mirror(root->left);
		mirror(root->right);
		swap(root->left,root->right);
	}
	void leftViewUtil(Node* x, int level, int* max_level)
	{
		if(!x)
			return;
		if(*max_level<level)
		{
			cout<<x->data<<" ";
			*max_level=level;
		}
		leftViewUtil(x->left,level+1,max_level);
		leftViewUtil(x->right,level+1,max_level);
	}
	void leftView(Node* x)
	{
		int max_level = 0;
		leftViewUtil(x,1,&max_level);
		cout<<endl;
	}
	void rightViewUtil(Node* x, int level, int* max_level)
	{
		if(!x)
			return;
		if(*max_level<level)
		{
			cout<<x->data<<" ";
			*max_level=level;
		}
		rightViewUtil(x->right,level+1,max_level);
		rightViewUtil(x->left,level+1,max_level);
	}
	void rightView(Node* x)
	{
		int max_level=0;
		rightViewUtil(x,1,&max_level);
		cout<<endl;
	}
	void printBoundaryLeft(Node* x)
	{
		if(!x)
			return;
		if(x->left)
		{
			cout<<x->data<<" ";
			printBoundaryLeft(x->left);
		}
		else if(x->right)
		{
			cout<<x->data<<" ";
			printBoundaryLeft(x->right);
		}
	}
	void printBoundaryRight(Node* x)
	{
		if(!x)
			return;
		if(x->right)
		{
			printBoundaryRight(x->right);
			cout<<x->data<<" ";
		}
		else if(x->left)
		{
			printBoundaryRight(x->left);
			cout<<x->data<<" ";
		}
	}
	void printLeaves(Node* x)
	{
		if(!x)
			return;
		printLeaves(x->left);
		if(x->left==NULL && x->right==NULL)
			cout<<x->data<<" ";
		printLeaves(x->right);
	}
	void boundaryView(Node* x)
	{
		if(!x)
			return;
		cout<<x->data<<" ";
		printBoundaryLeft(x->left);
		printLeaves(x);
		printBoundaryRight(x->right);
		cout<<endl;
	}
};
int main()
{
	int n,x;
	char ch;
	BT Tree;
	Tree.root = Tree.newNode(50);
	Tree.root->left = Tree.newNode(7);
	Tree.root->right = Tree.newNode(60);
	Tree.root->right->left = Tree.newNode(55);
	Tree.root->right->right = Tree.newNode(90);
	Tree.root->left->left = Tree.newNode(2);
	Tree.root->left->left->left = Tree.newNode(1);
	Tree.root->left->right = Tree.newNode(30);
	Tree.root->left->right->left = Tree.newNode(15);
	Tree.root->left->left->right = Tree.newNode(3);
	Tree.root->left->left->right->right = Tree.newNode(5);

	Node* current = Tree.get_left_leaf(Tree.root);

	cout<<"Left View : ";
	Tree.leftView(Tree.root);
	cout<<"Right View : ";
	Tree.rightView(Tree.root);
	cout<<"Boundary view : ";
	Tree.boundaryView(Tree.root);
	cout<<"Height : "<<Tree.height(Tree.root)<<endl;
	cout<<"Maximum width : "<<Tree.getMaxWidth(Tree.root)<<endl;

	cout<<"Mirror the tree (y/n) : ";
	cin>>ch;
	if(ch=='y'||ch=='Y')
	{
		Tree.inorder(Tree.root);
		cout<<endl;
		Tree.mirror(Tree.root);
		Tree.inorder(Tree.root);
		cout<<endl;
		return 0;
	}
	cout<<"Construct BST from preorder traversal (y/n) : ";
	cin>>ch;
	if(ch=='y'||ch=='Y')
	{
		BT Bst;
		cout<<"Size of preorder array : ";
		cin>>n;
		int a[n];
		cout<<"Enter preorder array :\n";
		for(int i=0;i<n;i++)
			cin>>a[i];
		int* preIndex = new int;
		*preIndex = 0;
		Bst.root = Bst.constructTree(a,n,INT_MIN,INT_MAX,preIndex);
		Bst.inorder(Bst.root);
		return 0;
	}

	cout<<"Find parent (y/n) : ";
	cin>>ch;
	if(ch=='y'||ch=='Y')
	{
		cout<<"of? : ";
		cin>>x;
		Node* a = Tree.search(x);
		Node* b = Tree.parent(a);
		if(b)
			cout<<"Parent : "<<b->data<<endl;
		else
			cout<<"No parent\n";
		return 0;
	}
	cout<<"Find predecessor and successor (y/n) : ";
	cin>>ch;
	if(ch=='y'||ch=='Y')
	{
		cout<<"of? : ";
		cin>>x;
		Node* a = Tree.search(x);
		Node* b = Tree.successor(a);
		if(b)
			cout<<"Successor : "<<b->data<<endl;
		else
			cout<<"No successor\n";
		Node* c = Tree.predecessor(a);
		if(c)
			cout<<"Predecessor : "<<c->data<<endl;
		else
			cout<<"No predecessor\n";
		return 0;
	}

	cout<<"Connect leaves (y/n) : ";
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