#pragma once

#include<iostream>
using namespace std;

enum Color
{
	BLACK,
	RED
};

template<class K,class V>
struct RBTreeNode        //红黑树的节点结构
{
	RBTreeNode<K,V>* _left;
	RBTreeNode<K,V>* _right;
	RBTreeNode<K,V>* _parent;
	Color _col;
	K _key;
	V _value;

	RBTreeNode(const K& key,const V& value,const Color col = RED)
		:_left(NULL)
		,_right(NULL)
		,_parent(NULL)
		,_col(col)
		,_key(key)
		,_value(value)
	{ }
};

template<class K,class V>
class RBTree
{
	typedef RBTreeNode<K,V> Node;
public:
	RBTree()
		:_root(NULL)
	{ }

	bool Insert(const K& key,const V& value)//插入
	{
		if(_root == NULL)
		{
			_root = new Node(key,value,BLACK);
			return true;
		}
		Node* parent = NULL;
		Node* cur = _root;

		while (cur)
		{
			if(cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if(cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				return false;//防止冗余
			}
		}

		cur = new Node(key,value,RED);//默认插入红节点
		//寻找数据要插入的位置
		if(parent->_key > key)
		{
			parent->_left = cur;
			cur->_parent = parent;
		}
		else
		{
			parent->_right = cur;
			cur->_parent = parent;
		}

		//调整节点的颜色
		while (cur != _root && parent->_col == RED)
		{
			//grandfather为祖父节点
			Node* grandfather = parent->_parent;
			if(grandfather->_left == parent)//判断parent为g的左节点
			{
				Node* uncle = grandfather->_right;
				if(uncle != NULL && uncle->_col == RED)
				{
					//情况1：cur红，parent红，uncle存在且为红，g黑 ----> p和u置黑，g置红，
					uncle->_col = parent->_col = BLACK;
					grandfather->_col = RED;
					cur = grandfather;   //继续向上调整
					parent = cur->_parent;
				}
				else
				{
					//情况3：cur红，p为红，g为黑，u不存在/u为黑，p为g的左，cur为p的右 -----》 针对p进行左单旋转 则转化为情况2
					if(cur == parent->_right)
					{
						RotateL(parent);//左旋
						swap(cur,parent);
					}
					//情况2;cur红，p为红，g为黑，u不存在/u为黑，p为g的左，cur为p的左 ----> 右旋，p为黑，g为红
					RotateR(grandfather);//
					parent->_col = BLACK;
					grandfather->_col = RED;
				}
			}
			else//parent为grandfater的右节点,与左节点类似
			{
				Node* uncle = grandfather->_left;
				if(uncle != NULL && uncle->_col == RED)
				{
					uncle->_col = parent->_col = BLACK;
					grandfather->_col = RED;
					cur = grandfather;
					parent = cur->_parent;
				}
				else
				{
					if(cur == parent->_left)
					{
						RotateR(parent);
						swap(cur ,parent);
					}
					RotateL(grandfather);
					parent->_col = BLACK;
					grandfather->_col = RED;
					
				}
			}
		}
		_root->_col = BLACK;//根节点为黑
		return true;
	}

	bool CheckRBTree()//检查是否为红黑树
	{
		int countBlack = 0;//用于记录一条路径下的黑色节点数量
		Node* cur = _root;
		while (cur != NULL)//统计一条路径下黑色节点的数量
		{
			if(cur->_col == BLACK)
			{
				countBlack++;
			}
			cur = cur->_left;
		}
		int count = 0;//用于记录另一条路径下黑色节点的数量
		return _CheckRBTree(_root,countBlack,count);//判断各个路劲下黑色节点的数量是否相等，等于则是红黑树反之不是
	}

	void InOrder()
	{
		_InOrder(_root);
		cout<<endl;
	}

protected:
	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		parent->_right = subRL;
		if(subRL != NULL)
			subRL->_parent = parent;

		subR->_left = parent;
		Node* ppNode = parent->_parent;
		parent->_parent = subR;

		if(ppNode == NULL)
		{
			_root = subR;
			subR->_parent = NULL;
		}
		else
		{
			if(ppNode->_right == parent)
				ppNode->_right = subR;
			else
				ppNode->_left = subR;
			subR->_parent = ppNode;
		}
	}

	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		parent->_left = subLR;
		if(subLR != NULL)
			subLR->_parent = parent;

		subL->_right = parent;

		Node* ppNode = parent->_parent;
		parent->_parent = subL;

		if(ppNode == NULL)
		{
			_root = subL;
			subL->_parent = NULL;
		}
		else
		{
			if(ppNode->_left == parent)
				ppNode->_left = subL;
			else
				ppNode->_right = subL;
			subL->_parent = ppNode;
		}
	}

	bool _CheckRBTree(Node* root,int countBlack,int curcount)
	{
		if(root == NULL)
			return false;

		if(root->_parent != NULL && root->_col == BLACK)
		{
			if(root->_parent->_col == RED)
				return true;
		}
		if(root->_left == NULL && root->_right == NULL)
		{
			if(countBlack == curcount)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		return _CheckRBTree(root->_left,countBlack,curcount++)
			&& _CheckRBTree(root->_right,countBlack,curcount++);
	}

	void _InOrder(Node* root)
	{
		if(root == NULL)
			return;

		_InOrder(root->_left);
		cout<<root->_key<<"->"<<root->_col<<" ";
		_InOrder(root->_right);
	}

protected:
	Node* _root;
};

void RBTreeTest()
{
	RBTree<int,int> tree;
	int a[] = {16,3,7,11,9,26,18,14,15};
	for(int i = 0;i < sizeof(a)/sizeof(a[0]);i++)
	{
		tree.Insert(a[i],i);
		tree.InOrder();
	}	
	cout<<tree.CheckRBTree()<<endl;
}
