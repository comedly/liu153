#pragma once
#include<iostream>
#include<queue>
#include<stack>
using namespace std;

//二叉树中结点的结构
template<class T>
struct BinaryTreeNode
{
	BinaryTreeNode(const T& x)
		:_data(x)
		,_left(NULL)
		,_right(NULL)
	{ }
	T _data;//结点的值
	BinaryTreeNode<T>* _left;//指向左子树的结点
	BinaryTreeNode<T>* _right;//指向右子树的结点
};

template<class T>
class BinaryTree
{
	typedef BinaryTreeNode<T> Node;//简化命名
public:
	BinaryTree()
		:_root(NULL)
	{ }

	BinaryTree(const T* a,size_t size,const T& invalid)
		:_root(NULL)
	{
		size_t index = 0;
		_root = _CreateTree(a,size,invalid,index);//创建二叉树
	}

	BinaryTree(const BinaryTree<T>& t)//拷贝构造函数
		:_root(NULL)
	{
		_Copy(t._root);
	}

	BinaryTree<T>& operator=(const BinaryTree<T>& t)//赋值函数
	{
		if(this != &t)
		{
			_Destory(t._root);
			_Copy(t._root);
		}
		return *this;
	}

	~BinaryTree()//析构函数
	{
		if(_root != NULL)
		{
			_Destroy(_root);
		}
	}

	void PrevOrder()//前序遍历打印二叉树
	{
		cout<<"前序遍历(递归)：";
		_PrevOrder(_root);
		cout<<endl;
		_NonPrevOrder(_root);
	}

	void InOrder()//中序遍历打印二叉树
	{
		cout<<"中序遍历(递归)：";
		_InOrder(_root);
		cout<<endl;
		_NonInOrder(_root);
	}

protected:
	Node* _CreateTree(const T* a,size_t size,const T& invalid,size_t& index)//创建二叉树
	{
		Node* root = NULL;
		if(a[index] != invalid && index < size)
		{
			root = new Node(a[index]);
			root->_left = _CreateTree(a,size,invalid,++index);
			root->_right = _CreateTree(a,size,invalid,++index);
		}
		return root;
	}

	void _Copy(Node* sroot)//拷贝函数
	{
		Node* root = NULL;
		if(sroot == NULL)//判断根节点
		{
			return;
		}
		if(sroot->_left && sroot->_right)//判断结点的左右子树
		{
			root = new Node(sroot->_data);
			return;
		}
		root->_left = _Copy(sroot->_left);//依次拷贝左子树
		root->_left = _Copy(sroot->_right);//依次拷贝右子树
	}

	void _Destory(Node* root)//销毁二叉树
	{
		if(root == NULL)//根节点为空
		{
			return;
		}
		if((root->_left == NULL) && (root->_right == NULL))只有根节点，直接释放根节点，令根节点为空
		{
			delete root;
			root = NULL;
			return;
		}
		_Destory(root->_left);//依次销毁左子树
		_Destory(root->_right);//依次销毁右子树
	}

	void _PrevOrder(Node* root)//递归实现前序遍历打印二叉树
	{
		if(root == NULL)
			return;
		cout<<root->_data<<" ";
		_PrevOrder(root->_left);
		_PrevOrder(root->_right);
	}

	void _NonPrevOrder(Node* root)//非递归实现前序遍历打印二叉树
	{
		stack<Node*> s;//利用栈的特点实现
		if(root == NULL)
			return;
		s.push(root);
		cout<<"前序遍历(非递归)：";
		while (!s.empty())
		{
			root = s.top();
			cout<<root->_data<<" ";
			s.pop();
			if(root->_right != NULL)
			{
				s.push(root->_right);
			}
			if(root->_left != NULL)
			{
				s.push(root->_left);
			}
		}
		cout<<endl;
	}

	void _InOrder(Node* root)//递归实现中序遍历打印二叉树
	{
		if(root == NULL)
			return;
		_InOrder(root->_left);
		cout<<root->_data<<" ";
		_InOrder(root->_right);
	}

	void _NonInOrder(Node* root)//非递归实现中序遍历打印二叉树
	{
		stack<Node*> s;
		Node* cur = root;
		cout<<"中序遍历（非递归）";
		while (cur || !s.empty())
		{
			while (cur)
			{
				s.push(cur);
				cur = cur->_left;
			}
			Node* top = s.top();
			cout<<top->_data<<" ";
			s.pop();
			cur = top->_right;
		}
		cout<<endl;
	}

protected:
	Node* _root;//根节点
};

void Test()
{
	int a1[10] = {1,2,3,'#','#',4,'#','#',5,6};
	int a2[15] = {1,2,'#',3,'#','#',4,5,'#',6,'#',7,'#','#',8,};
	int a3[5] = {2,3,'#','#',4};

	BinaryTree<int> t1(a1,10,'#');
	BinaryTree<int> t2(a1,15,'#');
	BinaryTree<int> t3(a1,5,'#');

	cout<<"t1遍历二叉树（前序、中序、后序）:"<<endl;
	t1.PrevOrder();
	t1.InOrder();
}