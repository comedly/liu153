#pragma once
#include<iostream>
#include<queue>
#include<stack>
using namespace std;

//�������н��Ľṹ
template<class T>
struct BinaryTreeNode
{
	BinaryTreeNode(const T& x)
		:_data(x)
		,_left(NULL)
		,_right(NULL)
	{ }
	T _data;//����ֵ
	BinaryTreeNode<T>* _left;//ָ���������Ľ��
	BinaryTreeNode<T>* _right;//ָ���������Ľ��
};

template<class T>
class BinaryTree
{
	typedef BinaryTreeNode<T> Node;//������
public:
	BinaryTreeNode()
		:_root(NULL)
	{ }

	BinaryTreeNode(const T* a,size_t size,const T& invalid)
		:_root(NULL)
	{
		size_t index = 0;
		_root = _CreateTree(a,size,invalid,index);//����������
	}

	BinaryTreeNode(const BinaryTree<T>& t)//�������캯��
		:_root(NULL)
	{
		_Copy(t._root);
	}

protected:
	Node* _CreateTree(const T* a,size_t size,const T& invalid,const size_t& index)//����������
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

	void _Copy(Node* sroot)//��������
	{
		Node* root = NULL;
		if(sroot == NULL)//�жϸ��ڵ�
		{
			return;
		}
		if(sroot->_left && sroot->_right)//�жϽ�����������
		{
			root = new Node(sroot->_data);
			return;
		}
		root->_left = _Copy(sroot->_left);//���ο���������
		root->_left = _Copy(sroot->_right);//���ο���������
	}
protected:
	Node* _root;//���ڵ�
};