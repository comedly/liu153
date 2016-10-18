#pragma once

#include<iostream>
using namespace std;

typedef int DataType;

struct Node
{
	Node(const DataType& d)
		:_data(d)
		,_next(NULL)
		,_prev(NULL)
	{ }
	DataType _data;
	Node* _next;
	Node* _prev;
};

class DList
{
public:
	friend ostream& operator<<(ostream& os,DList& s);
	DList()
		:_head(NULL)
		,_tail(NULL)
	{
	}

	~DList()
	{
		Node* cur = _head;
		while(cur)
		{
			Node* del = cur;
			cur = cur->_next;
			delete del;
		}
	}

public:
	void PushBack(const DataType& d);
	void PopBack();
	void PushFront(const DataType& d);
	void PopFront();
	Node* Find(const DataType& d);
	void Insert(Node* pos,const DataType& d);
	void Sort();
	void Reverse();
	void Remove(const DataType& d);
	void RemoveAll(const DataType& d);
	void Erase(Node* pos);

private:
	Node* _head;
	Node* _tail;
};