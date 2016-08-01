#pragma once

#include<iostream>
#include<iterator>
using namespace std;

//-------------------- 模拟实现简化版List迭代器 ---------------------------

template<class T>
struct _ListNode//链表的节点结构
{
	/*_ListNode()
		:_prev(NULL)
		,_next(NULL)
	{ }*/

	_ListNode(const T& x = T())
		:_data(x)
		,_prev(NULL)
		,_next(NULL)
	{ }

	T _data;//链表的数据
	_ListNode<T>* _prev;//指向当前节点的前一个节点
	_ListNode<T>* _next;//指向当前节点的下一个节点
};

template<class T, class Ref, class Ptr>
struct __ListIterator {
  typedef __ListIterator<T, Ref, Ptr> Self;

  typedef T ValueType;
  typedef Ptr Pointer;
  typedef Ref Reference;
  //typedef ptrdiff_t DifferenceType;
  _ListNode<T>* _Node;

  __ListIterator(_ListNode<T>* x)
	  :_Node(x)
  { }

  __ListIterator()
  { }

  /*__ListIterator(const iterator& x)
	  :_Node(x._Node)
  { }*/

  bool operator==(const Self& x) const
  {
	  return _Node == x._Node;
  }

  bool operator!=(const Self& x) const
  {
	  return _Node != x._Node;
  }
  
  Reference operator*()
  {
	  return (*_Node)._data;
  }

  Pointer operator->()const
  {
	  return &(operator*());
  }

  Pointer operator->()
  {
	  return &(_Node->_data);
  }

  Self& operator++()
  {
	  _Node = _Node->_next;
	  return *this;
  }

  Self operator++(int)
  {
	  Self temp(*this);
	  _Node = _Node->_next;
	  return temp;
  }

  Self& operator--()
  {
	  _Node = _Node->_prev;
	  return *this;
  }

  Self operator--(int)
  {
	  Self temp(*this);
	  _Node = _Node->_prev;
	  return temp;
  }
};

template<class T>
class List
{
public:
	typedef _ListNode<T> ListNode;
	typedef __ListIterator<T,T&,T*> Iterator;
	typedef __ListIterator<T,const T&,const T*> constIterator;


public:
	List()
	{
		_head = new ListNode;
		_head->_next = _head;
		_head->_prev = _head;
	}

	void PushBack(const T& x)
	{
		ListNode* tail = _head->_prev;
		ListNode* newNode = new ListNode(x);
		tail->_next = newNode;
		newNode->_prev = tail;
		_head->_prev = newNode;
		newNode->_next = _head;
	}

	Iterator Begin()
	{
		return Iterator(_head->_next);
	}

	Iterator End()
	{
		return Iterator(_head);
	}
protected:
	ListNode* _head;
};

void Print(const List<int>& list)
{
	/*List<int>::Iterator it = list.Begin();
	while (it != list.End())
	{
		cout<<*it<<" ";
		it++;
	}*/

	List<int>::constIterator it = list.Begin();
	while (it != list.End())
	{
		cout<<*it<<" ";
		it++;
	}
	cout<<endl;
}


void test()
{
	List<int> list;
	list.PushBack(1);
	list.PushBack(2);
	list.PushBack(3);
	list.PushBack(4);
	list.PushBack(5);
	Print(list);
}