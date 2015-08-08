#include <iostream>
#include <stack>
#include <queue>
#include <fstream>
using namespace std;
class Node
{
public:
	Node* p;
	Node* left;
	Node* right;
	int data;
	Node(int d): data(d), left(NULL), right(NULL), p(NULL) {};
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

class BST
{
public:
	Node* root;
	BST(): root(NULL) {};
	~BST()
	{
		root->destruct();
		root = NULL;
	}
	void insert(int k)
	{
		Node* x = root;
		Node* y = NULL;
		Node* z = new Node(k);
		while(x!=NULL)
		{
			y=x;
			if(k < x->data)
				x = x->left;
			else
				x = x->right;
		}
		z->p = y;
		if(y==NULL)
		{
			root = z;
			return;
		}
		if(y->data < k)
			y->right = z;
		else
			y->left = z;
	}
	void inorder(Node* x)
	{
		if(x==NULL)
			return;
		inorder(x->left);
		cout<<x->data<<" ";
		inorder(x->right);
	}
	void preorder(Node* x)
	{
		if(x==NULL)
			return;
		cout<<x->data<<" ";
		preorder(x->left);
		preorder(x->right);
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
	Node* max(Node* x)
	{
		Node* temp = x;
		while(temp->right!=NULL)
			temp = temp->right;
		return temp;
	}
	Node* min(Node* x)
	{
		Node* temp = x;
		while(temp->left!=NULL)
			temp = temp->left;
		return temp;
	}
	Node* successor(Node* x)
	{
		if(x->right)
			return min(x->right);
		Node* y = x->p;
		while(y!=NULL && x==y->right)
		{
			x = y;
			y = y->p;
		}
		return y;
	}
	Node* predecessor(Node* x)
	{
		if(x->left)
			return max(x->left);
		Node* y = x->p;
		while(y!=NULL && x==y->left)
		{
			x = y;
			y = y->p;
		}
		return y;
	}
	Node* lca(Node* root, int k1, int k2)
	{
		Node* x = search(k1);
		Node* y = search(k2);
		if(x==NULL || y==NULL)
			return NULL;
		if(root==NULL)
			return NULL;
		if(root->data < k1 && root->data < k2)
			return lca(root->right,k1,k2);
		else if(root->data > k1 && root->data > k2)
			return lca(root->left,k1,k2);
		return root;
	}
	void range(Node* x, int k1, int k2)
	{
		if(x==NULL)
			return;
		if(k1 < x->data)
			range(x->left,k1,k2);
		if(k1 <= x->data && x->data <= k2)
			cout<<x->data<<" ";
		if(x->data < k2)
			range(x->right,k1,k2);
	}
	Node* remove_outside_range(Node* x, int min, int max)
	{
		if(x==NULL)
			return NULL;
		x->left = remove_outside_range(x->left,min,max);
		x->right = remove_outside_range(x->right,min,max);
		if(x->data < min)
		{
			Node* r_child = x->right;
			if(r_child)
				x->right->p = x->p;
			if(x->left)
				(x->left)->destruct();
			delete x;
			return r_child;
		}
		if(x->data > max)
		{
			Node* l_child = x->left;
			if(l_child)
				x->left->p = x->p;
			if(x->right)
				(x->right)->destruct();
			delete x;
			return l_child;
		}
		return x;
	}
	void inorder_iterative(Node* x)
	{
		stack<Node*> s;
		Node* current = x;
		while(1)
		{
			while(current)
			{
				s.push(current);
				current = current->left;
			}
			if(!s.empty())
			{
				Node* temp = s.top();
				s.pop();
				cout<<temp->data<<" ";
				current = temp->right;
			}
			else
				break;
		}
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
	int ceil(Node* x, int input)
	{
		if(x==NULL)
			return -1;
		if(x->data == input)
			return x->data;
		else if(x->data < input)
			return ceil(x->right,input);
		else
		{
			int c = ceil(x->left,input);
			if(c >= input)
				return c;
			else
				return x->data;
		}
	}
	int floor(Node* x, int input)
	{
		if(x==NULL)
			return -1;
		if(x->data==input)
			return x->data;
		else if(x->data > input)
			return floor(x->left,input);
		else
		{
			int f = floor(x->right,input);
			if(f <= input)
				return f;
			else
				return x->data;
		}
	}
	void cumulate(Node* x)
	{
		static int prev = 0;
		if(x==NULL)
			return;
		cumulate(x->left);
		x->data += prev;
		prev = x->data;
		cumulate(x->right);
	}
	void levelorder(Node* x)
	{
		queue<Node*> Q;
		Q.push(x);
		while(!Q.empty())
		{
			Node* temp = Q.front();
			Q.pop();
			cout<<temp->data<<" ";
			if(temp->left)
				Q.push(temp->left);
			if(temp->right)
				Q.push(temp->right);
		}
	}
};
Node* sorted2BST(int a[], Node* par, int start, int end)
{
	if(start>end)
		return NULL;
	int mid = (start+end)/2;
	Node* root = new Node(a[mid]);
	root->left = sorted2BST(a,root,start,mid-1);
	root->right = sorted2BST(a,root,mid+1,end);
	root->p = par;
	return root;
}
bool isSameBST(int a[], int b[], int size1, int size2)
{
	if(size1!=size2)
		return false;
	if(size1==size2 && size1==0)
		return true;

	if(size1==1)
		if(a[0]==b[0])
			return true;
		else
			return false;

	int a_left[size1], a_right[size1], b_left[size1], b_right[size2];
	int a_lcount=0, a_rcount=0, b_lcount=0, b_rcount=0;

	if(a[0]==b[0])
	{
		for(int i=1;i<size1;i++)
			if(a[i]<a[0])
				a_left[a_lcount++]=a[i];
			else
				a_right[a_rcount++]=a[i];

		for(int i=1;i<size1;i++)
			if(b[i]<b[0])
				b_left[b_lcount++]=b[i];
			else
				b_right[b_rcount++]=b[i];

		bool left = isSameBST(a_left,b_left,a_lcount,b_lcount);
		bool right = isSameBST(a_right,b_right,a_rcount,b_rcount);
		return (left & right);
	}
	else
		return false;
}
bool hasOneChild(int a[], int n)
{
	int nextdiff, lastdiff;
	for(int i=0;i<n-1;i++)
	{
		nextdiff = a[i] - a[i+1];
		lastdiff = a[i] - a[n-1];
		if(nextdiff*lastdiff < 0)
			return false;
	}
	return true;
}
int main()
{
	BST Tree;
	Node* z;
	int x,y,n,choice;
	char ch;
	ifstream file("BSTclass input.txt");
	cout<<"Number of elements : ";
	file>>n;
	cout<<"Enter elements of BST :\n";
	for(int i=0;i<n;i++)
	{
		file>>x;
		Tree.insert(x);
	}
	cout<<"Tree created\n";
	do
	{
		cout<<"\n1. Inorder traversal\n";
		cout<<"2. Search\n";
		cout<<"3. Maximum element\n";
		cout<<"4. Minimum element\n";
		cout<<"5. Successor\n";
		cout<<"6. Predecessor\n";
		cout<<"7. Lowest Common Ancestor\n";
		cout<<"8. Print range\n";
		cout<<"9. Remove outside range\n";
		cout<<"10. Iterative inorder\n";
		cout<<"11. Height\n";
		cout<<"12. Maximum width\n";
		cout<<"13. Ceiling of a number\n";
		cout<<"14. Floor of a number\n";
		cout<<"15. Level order traversal\n";
		cout<<"0. Exit\n";
		cout<<"Enter a choice : ";
		cin>>choice;
		switch(choice)
		{
			case 1: cout<<"Inorder traversal : ";
					Tree.inorder(Tree.root);
					break;

			case 2: cout<<"\nEnter element to search : ";
					cin>>x;
					z = Tree.search(x);
					if(z==NULL)
						cout<<"Element not found"<<endl;
					else
						cout<<x<<" found"<<endl;
					break;

			case 3: cout<<"Maximum element : "<<Tree.max(Tree.root)->data<<endl;
					break;

			case 4: cout<<"Minimum element : "<<Tree.min(Tree.root)->data<<endl;
					break;

			case 5: cout<<"Find sucessor of : ";
					cin>>x;
					z = Tree.search(x);
					if(z)
					{
						z = Tree.successor(z);
						if(z)
							cout<<z->data<<endl;
						else
							cout<<"No successor found"<<endl;
					}
					else
						cout<<x<<" not found"<<endl;
					break;

			case 6: cout<<"Find predecessor of : ";
					cin>>x;
					z = Tree.search(x);
					if(z)
					{
						z = Tree.predecessor(z);
						if(z)
							cout<<z->data<<endl;
						else
							cout<<"No predecessor found"<<endl;
					}
					else
						cout<<x<<" not found"<<endl;
					break;

			case 7: cout<<"Enter two elements :\n";
					cin>>x>>y;
					if(!Tree.search(x) || !Tree.search(y))
						cout<<x<<" and "<<y<<" are not there in the BST\n";
					cout<<"Lowest Ancestor is "<<Tree.lca(Tree.root,x,y)->data<<endl;
					break;

			case 8: cout<<"Enter two elements :\n";
					cin>>x>>y;
					Tree.range(Tree.root,x,y);
					break;

			case 9: cout<<"Enter range :\n";
					cin>>x>>y;
					Tree.root = Tree.remove_outside_range(Tree.root,x,y);
					Tree.inorder(Tree.root);
					break;

			case 10:Tree.inorder_iterative(Tree.root);
					break;

			case 11:cout<<"Height of tree : "<<Tree.height(Tree.root)<<endl;
					break;

			case 12:cout<<"Maximum width : "<<Tree.getMaxWidth(Tree.root)<<endl;
					break;

			case 13:cout<<"Find ceiling of? : ";
					cin>>x;
					cout<<Tree.ceil(Tree.root,x)<<endl;
					break;

			case 14:cout<<"Find floor of? : ";
					cin>>x;
					cout<<Tree.floor(Tree.root,x)<<endl;
					break;

			case 15:Tree.levelorder(Tree.root);
					cout<<endl;
					break;
					
			default: cout<<"Some more  :D\n";
		}
	}while(choice!=0);

	cout<<"Create a BST from sorted array ? (y/n) : \n";
	cin>>ch;
	if(ch=='y'||ch=='Y')
	{
		cout<<"Size of array : ";
		cin>>n;
		int a[n];
		for(int i=0;i<n;i++)
			cin>>a[i];
		
		z = sorted2BST(a,NULL,0,n-1);
		BST BalancedTree;
		BalancedTree.root = z;
		BalancedTree.inorder(BalancedTree.root);
		cout<<endl;
	}
	cout<<"Check if 2 array build same BST (y/n) : ";
	cin>>ch;
	if(ch=='y'||ch=='Y')
	{
		cout<<"Size of both arrays : ";
		cin>>n;
		int a[n], b[n];
		cout<<"Elements of 1st array :\n";
		for(int i=0;i<n;i++)
			cin>>a[i];
		cout<<"Elements of 2nd array :\n";
		for(int i=0;i<n;i++)
			cin>>b[i];
		bool ans = isSameBST(a,b,n,n);
		if(ans)
			cout<<"The 2 arrays will create the same BST\n";
		else
			cout<<"The 2 arrays will not create the same BST\n";
	}
	cout<<"Check if all internal nodes of a tree have single child using preorder (y/n) : ";
	cin>>ch;
	if(ch=='y'||ch=='Y')
	{
		cout<<"Size of array : ";
		cin>>n;
		int a[n];
		cout<<"Preorder : ";
		for(int i=0;i<n;i++)
			cin>>a[n];
		if(hasOneChild(a,n))
			cout<<"The preorder represents a tree with all single child interal nodes\n";
		else
			cout<<"The preorder does not represents a tree with all single child interal nodes\n";
	}
	cout<<"Cumulate tree (y/n) : ";
	cin>>ch;
	if(ch=='y'||ch=='Y')
	{
		Tree.cumulate(Tree.root);
		Tree.inorder(Tree.root);
	}
	return 0;
}