#pragma once

#include<iostream>
using namespace std;

enum Color
{
	BLACK,
	RED
};

template<class K,class V>
struct RBTreeNode        //������Ľڵ�ṹ
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

	bool Insert(const K& key,const V& value)//����
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
				return false;//��ֹ����
			}
		}

		cur = new Node(key,value,RED);//Ĭ�ϲ����ڵ�
		//Ѱ������Ҫ�����λ��
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

		//�����ڵ����ɫ
		while (cur != _root && parent->_col == RED)
		{
			//grandfatherΪ�游�ڵ�
			Node* grandfather = parent->_parent;
			if(grandfather->_left == parent)//�ж�parentΪg����ڵ�
			{
				Node* uncle = grandfather->_right;
				if(uncle != NULL && uncle->_col == RED)
				{
					//���1��cur�죬parent�죬uncle������Ϊ�죬g�� ----> p��u�úڣ�g�ú죬
					uncle->_col = parent->_col = BLACK;
					grandfather->_col = RED;
					cur = grandfather;   //�������ϵ���
					parent = cur->_parent;
				}
				else
				{
					//���3��cur�죬pΪ�죬gΪ�ڣ�u������/uΪ�ڣ�pΪg����curΪp���� -----�� ���p��������ת ��ת��Ϊ���2
					if(cur == parent->_right)
					{
						RotateL(parent);//����
						swap(cur,parent);
					}
					//���2;cur�죬pΪ�죬gΪ�ڣ�u������/uΪ�ڣ�pΪg����curΪp���� ----> ������pΪ�ڣ�gΪ��
					RotateR(grandfather);//
					parent->_col = BLACK;
					grandfather->_col = RED;
				}
			}
			else//parentΪgrandfater���ҽڵ�,����ڵ�����
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
		_root->_col = BLACK;//���ڵ�Ϊ��
		return true;
	}

	bool CheckRBTree()//����Ƿ�Ϊ�����
	{
		int countBlack = 0;//���ڼ�¼һ��·���µĺ�ɫ�ڵ�����
		Node* cur = _root;
		while (cur != NULL)//ͳ��һ��·���º�ɫ�ڵ������
		{
			if(cur->_col == BLACK)
			{
				countBlack++;
			}
			cur = cur->_left;
		}
		int count = 0;//���ڼ�¼��һ��·���º�ɫ�ڵ������
		return _CheckRBTree(_root,countBlack,count);//�жϸ���·���º�ɫ�ڵ�������Ƿ���ȣ��������Ǻ������֮����
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
