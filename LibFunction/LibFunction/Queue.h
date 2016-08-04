/**************************************************************************
	>file name:Queue.h
	>author:Comedly
	>create time:2016-8-4
***************************************************************************/

#pragma once
using namespace std;

template<class T>
struct Node
{
	Node()
		:_next(NULL)
	{ }

	Node(const T& x)
		:_data(x)
		 ,_next(NULL)
	{ }

	T _data;
	Node<T>* _next; 
};

template<class K>
class Queue
{
public:
	Queue()
		:_head(NULL)
		 ,_tail(NULL)
	{ }

	Queue(const Queue<K>& q)
		:_head(NULL)
		,_tail(NULL)
	{
		Node<K>* cur = q._head;
		while(cur)
		{
			Push(cur->_data);
			cur = cur->_next;
		}
	}

	~Queue()
	{
		Destroy();
	}

public:
	void Destroy()
	{
		if(_head == NULL)
			return;
		Node<K>* cur = _head;
		while(cur->_next != NULL)
		{
			Node<K>* del = cur;
			cur = cur->_next;
			delete del;
		}
		delete cur;
		_head = NULL;
		_tail = NULL;
	}
	
	void Push(const K& x)//插入
	{
		Node<K>* newNode = new Node<K>(x);
		if(_head == NULL)
		{
			_head = newNode;
			_tail = newNode;
		}
		else
		{
			_tail->_next = newNode;
			_tail = newNode;
		}
	}

	void Pop()//删除
	{
		if(_head == NULL)
		{
			return;
		}
		Node<K>* del = _head;
		_head = _head->_next;
		delete del;
	}

	K& Front()//获取头节点的值
	{
		return _head->_data;
	}

	K& Back()//获取尾节点的值
	{
		return _tail->_data;
	}

	void IsEmpty()//判空
	{
		if(_head == NULL)
			return true;
		return false;
	}

	size_t Size()//求取队列的节点数量
	{
		if(_head == NULL)
		{
			return 0;
		}
		Node<K>* cur = _head;
		size_t count = 0;
		while(cur)
		{
			count++;
			cur = cur->_next;
		}
		return count;
	}

 	void Print()
	{
		if(_head == NULL)
			return;
		Node<K>* cur = _head;
		while(cur)
		{
			cout<<cur->_data<<" ";
			cur = cur->_next;
		}
		cout<<endl;
	}

protected:
	Node<K>* _head;
	Node<K>* _tail;
};
