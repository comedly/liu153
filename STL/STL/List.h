#pragma once

#include<iostream>
#include<assert.h>
#include"Iterator.h"
using namespace std;

//-------------------- ģ��ʵ�ּ򻯰�List������ ---------------------------

template<class T>
struct _ListNode//����Ľڵ�ṹ
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

	T _data;//���������
	_ListNode<T>* _prev;//ָ��ǰ�ڵ��ǰһ���ڵ�
	_ListNode<T>* _next;//ָ��ǰ�ڵ����һ���ڵ�
};

template<class T, class Ref, class Ptr>
struct __ListIterator {
  typedef __ListIterator<T, Ref, Ptr> Self;

  typedef BidirectionalIteratorTag IteratorCagetory;
  typedef ptrdiff_t DifferenceType;
  typedef T ValueType;
  typedef Ptr Pointer;
  typedef Ref Reference;
 
  

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
	typedef ReverseIterator<Iterator> ReverseIterator;


public:
	List()
	{
		_head = new ListNode;
		_head->_next = _head;
		_head->_prev = _head;
	}

	//��posλ��ǰ����һ��Ԫ��
	void Insert(Iterator pos,const T& x)
	{
		ListNode* cur = pos._Node;
		ListNode* prev = cur->_prev;

		ListNode* newNode = new ListNode(x);
		prev->_next = newNode;
		newNode->_prev = prev;
		
		newNode->_next = cur;
		cur->_prev = newNode;
	}

	//ɾ��posλ�ö�Ӧ��Ԫ�أ�����pos��ָ��Ԫ�ص���һ��λ��
	Iterator Erase(Iterator pos)
	{
		assert(pos != End());
		ListNode* next = pos._Node->_next;
		ListNode* prev = pos._Node->_prev;

		prev->_next = next;
		next->_prev = prev;

		delete pos._Node;

		return Iterator(next);
	}

	/*void PushBack(const T& x)
	{
		ListNode* tail = _head->_prev;
		ListNode* newNode = new ListNode(x);
		tail->_next = newNode;
		newNode->_prev = tail;
		_head->_prev = newNode;
		newNode->_next = _head;
	}*/

	void PushFront(const T& x)
	{
		Insert(Begin(),x);
	}

	void PushBack(const T& x)
	{
		Insert(End(),x);
	}

	void PopBack()
	{
		Erase(--End());
	}

	void PopFront()
	{
		Erase(Begin());
	}

	Iterator Begin()
	{
		return Iterator(_head->_next);
	}

	Iterator End()
	{
		return Iterator(_head);
	}

	ReverseIterator RBegin()
	{
		return ReverseIterator(End());
	}

	ReverseIterator REnd()
	{
		return ReverseIterator(Begin());
	}

	constIterator Begin() const
	{
		return constIterator(_head->_next);
	}

	constIterator End() const
	{
		return _head;
	}



protected:
	ListNode* _head;
};

void Print1(List<int>& list)
{
	List<int>::Iterator it = list.Begin();
	while (it != list.End())
	{
		//(*it)++;
		cout<<*it<<" ";
		it++;
	}
	cout<<endl;
}

void Print2(const List<int>& list)
{
	List<int>::constIterator it = list.Begin();
	while (it != list.End())
	{
		//(*it)++;�޸Ĳ���
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
	Print1(list);

	list.PopBack();
	list.PopBack();
	Print2(list);

	list.PopFront();
	Print2(list);
}
