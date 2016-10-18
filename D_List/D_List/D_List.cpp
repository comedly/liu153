#include "D_List.h"

ostream& operator<<(ostream& os,DList& d)
{
	Node* cur = d._head;
	while(cur)
	{
		os<<cur->_data<<" ";
		cur = cur->_next;
	}
	os<<"over"<<endl;
	return os;
}

void DList::PushBack(const DataType& d)
{
	Node* newNode = new Node(d);
	if(_head == NULL)
	{
		_head = newNode;
		_tail = _head;
	}
	else
	{
		_tail->_next = newNode;
		newNode->_prev = _tail;
		_tail = newNode;
	}
}

void DList::PopBack()
{
	if(_head == NULL)
	{
		return;
	}
	else if(_head == _tail)
	{
		delete _head;
		_head = NULL;
		_tail = NULL;
	}
	else
	{
		_tail = _tail->_prev;
		delete _tail->_next;
		_tail->_next = NULL;
	}
}

void DList::PushFront(const DataType& d)
{
	Node* newNode = new Node(d); 
	if(_head == NULL)
	{
		_head = newNode;
		_tail = _head;
	}
	else
	{
		_head->_prev = newNode;
		newNode->_next = _head;
		_head = newNode;
	}
}

void DList::PopFront()
{
	if(_head == NULL)
	{
		return;
	}
	else if(_head == _tail)
	{
		delete _head;
		_head = NULL;
		_tail = NULL;
	}
	else
	{
		Node* del = _head;
		_head = del->_next;
		delete del;
	}
}

Node* DList::Find(const DataType& d)
{
	Node* cur = _head;
	while(cur)
	{
		if(cur->_data == d)
		{
			return cur;
		}
		cur = cur->_next;
	}
	return NULL;
}

void DList::Insert(Node* pos,const DataType& d)
{
	Node* newNode = new Node(d);
	Node* cur = Find(pos->_data);
	newNode->_next = cur->_next;
	cur->_next =newNode;
}

void DList::Sort()
{
	Node* cur = _head;
	while(cur)
	{
		Node* pos = _head;
		while(pos->_next != NULL)
		{
			if(pos->_data > pos->_next->_data)
			{
				DataType tmp = pos->_data;
				pos->_data = pos->_next->_data;
				pos->_next->_data = tmp;
			}
			pos = pos->_next;
		}
		cur = cur->_next;
	}
}

void DList::Reverse()
{
	Node* start = _head;
	Node* end = _tail;
	while(!((start == end) || end->_next == start))
	{
		swap(start->_data,end->_data);
		start = start->_next;
		end = end->_prev;
	}
}

void DList::Remove(const DataType& d)
{
	if(_head == NULL)
		return;
	Node* del = Find(d);
	del->_prev->_next = del->_next;
	delete del;
}

void DList::RemoveAll(const DataType& d)
{
	if(_head == NULL)
	{
		return;	
	}
	if((_head == _tail) && (_head->_data == d))
	{
		delete _head;
		_head = NULL;
		_tail = NULL;
	}
	Node* cur = _head;
	while(cur)
	{
		Node* del = Find(d);
		while(del)
		{
			del->_prev->_next = del->_next;
			delete del;
			break;
		}
		cur= cur->_next;
	}
}

void DList::Erase(Node* pos)
{
	if(_head == NULL)
		return;
	if((_head == _tail) &&(_head == pos))
	{
		delete _head;
		_head = NULL;
		_tail = NULL;
		return;
	}
	Node* del = _head;
	while(del)
	{
		Node* cur = del;
		if(cur == pos)
		{
			cur->_prev->_next = cur->_next;
			delete cur;
		}
		del = del->_next;
	}
}