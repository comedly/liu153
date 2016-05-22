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

	void PosOrder()//后序遍历打印二叉树
	{
		cout<<"后序遍历(递归)：";
		_PosOrder(_root);
		cout<<endl;
		_NonPosOrder(_root);
	}

	void LevelOrder()//层次遍历
	{
		cout<<"层次遍历：";
		_LevelOrder(_root);
		cout<<endl;
	}

	size_t Size()//求结点的个数
	{
		return _Size(_root);
	}

	size_t Depth()//求树的深度
	{
		return _Depth(_root);
	}

	size_t LeafSize()//叶子节点个数
	{
		return _LeafSize(_root);
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

	void _PosOrder(Node* root)//后序遍历打印二叉树
	{
		if(root == NULL)
		{
			return;
		}
		_PosOrder(root->_left);
		_PosOrder(root->_right);
		cout<<root->_data<<" ";
	}

	void _NonPosOrder(Node* root)//非递归实现后序打印二叉树
	{
		Node* cur = root;
		Node* prev = NULL;
		stack<Node*> s;
		if(root == NULL)
			return;
		cout<<"递归实现二叉树：";
		while (cur || !s.empty())
		{
			while (cur)
			{
				s.push(cur);
				cur = cur->_left;
			}
			cur = s.top();
			if(cur->_right == NULL || cur->_right == prev)
			{
				
				cout<<cur->_data<<" ";
				s.pop();
				prev = cur;
				cur = NULL;
			}
			else
			{
				cur = cur->_right;
			}
		}
		cout<<endl;
	}

	void _LevelOrder(Node* root)//层次遍历
	{
		queue<Node*> q;
		if(root == NULL)
		{
			return;
		}
		q.push(root);
		while (!q.empty())
		{
			if(q.front()->_left != NULL)
			{
				q.push(q.front()->_left);
			}
			if(q.front()->_right != NULL)
			{
				q.push(q.front()->_right);
			}
			cout<<q.front()->_data<<" ";
			q.pop();
		}
	}

	size_t _Size(Node* root)//求结点的个数
	{
		if(root == NULL)
			return 0;
		return _Size(root->_left) + _Size(root->_right) + 1;
	}

	size_t _Depth(Node* root)//求树的深度
	{

	}

protected:
	Node* _root;//根节点
};