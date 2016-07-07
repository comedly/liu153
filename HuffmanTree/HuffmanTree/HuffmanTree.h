#pragma once

#include<iostream>
#include"Heap.h"
#include<assert.h>

//HuffmanTree结点结构
template<class T>
struct HuffmanNode
{
	HuffmanNode<T>* _left;
	HuffmanNode<T>* _right;
	T _weight;  //权值

	HuffmanNode(T weight = 0)//
		:_left(NULL)
		,_right(NULL)
		,_weight(weight)
	{ }
};

template<class T>
class HuffmanTree
{
	typedef HuffmanNode<T> Node;
public:
	HuffmanTree()//默认构造函数
		:_root(NULL)
	{	}

	HuffmanTree(const T* a,size_t size,const T& invalid)
	{
		assert(a);
		_root = _CreateTree(a,size,invalid);
	}

	Node* GetRootNode()
	{
		return this->_root;
	}

	~HuffmanTree()
	{
		_Delete(_root);
	}

protected:
	Node* _CreateTree(const T* a,size_t size,const T& invalid)
	{
		assert(a);

		struct NodeComper
		{
			bool operator()(const Node* l,const Node* r)
			{
				return l->_weight < r->_weight;
			}
		};

		//建一个小堆
		Heap<Node*,NodeComper> minHeap;
		Node* parent = NULL;
		for(size_t i = 0;i < size;i++)
		{
			if(a[i] != invalid)
			{
				minHeap.Push(new Node(a[i]));
			}
		}
		while (minHeap.Size() > 1)
		{
			Node* first = minHeap.GetTop();
			minHeap.Pop();
			Node* second = minHeap.GetTop();
			minHeap.Pop();

			parent = new Node(first->_weight + second->_weight);
			parent->_left = first;
			parent->_right = second;
			minHeap.Push(parent);
		}
		return parent;
	}

	void _Delete(Node* root)
	{
		if(root == NULL)
		{
			return;
		}
		else
		{
			_Delete(root->_left);
			_Delete(root->_right);

			delete root;
		}
	}

private:
	Node* _root;
};

void TestHuffmanTree()
{
	int a[] = {1,2,3,4,5,6,7,8,9,0};
	HuffmanTree<int> t1(a,10,'#');
	HuffmanNode<int>* root = t1.GetRootNode();
}
