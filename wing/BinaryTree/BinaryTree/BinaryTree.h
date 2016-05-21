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
	BinaryTreeNode()
		:_root(NULL)
	{ }

	BinaryTreeNode(const T* a,size_t size,const T& invalid)
		:_root(NULL)
	{
		size_t index = 0;
		_root = _CreateTree(a,size,invalid,index);//创建二叉树
	}

	BinaryTreeNode(const BinaryTree<T>& t)//拷贝构造函数
		:_root(NULL)
	{
		_Copy(t._root);
	}

protected:
	Node* _CreateTree(const T* a,size_t size,const T& invalid,const size_t& index)//创建二叉树
	{
		Node* root = NULL;
		if(a[index] != invalid && index < size)
		{
			root = new Node[a[index]];
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
protected:
	Node* _root;//根节点
};