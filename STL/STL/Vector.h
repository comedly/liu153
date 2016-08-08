#pragma once

#include<iostream>
#include"Iterator.h"
using namespace std;

template<class T>
class Vector
{
public:
	typedef T ValueType;
	typedef ValueType* Iterator;
	typedef const ValueType* ConstIterator;
	typedef ReverseIterator<Iterator> ReverseIterator;

	Vector()
		:_start(0)
		,_finish(0)
		,_EndOfStorage(0)
	{ }

	size_t Size()
	{
		return _finish - _start;
	}

	void PushBack(const ValueType& x)
	{
		CheckStorage();
		
		*_finish = x;
		++_finish;
	}

	Iterator Begin()
	{
		return _start;
	}

	Iterator End()
	{
		return _finish;
	}

	ConstIterator Begin() const
	{
		return _start;
	}

	ConstIterator End() const
	{
		return _finish;
	}

	void Insert(Iterator pos, const T& x)//在pos位置前插入一个元素
	{
		if(pos == _EndOfStorage)
		{
			CheckStorage();
		}
		size_t size = pos-_start;
		for(size_t i = Size();i>=size;i--)
		{
			_start[i+1] = _start[i];
		}
		*pos = x;
		++_finish;
	}

	Iterator Erase(Iterator pos)
	{
		if(pos+1 != _finish)
		{
			size_t size = pos - _start;
			for(size_t i = size;i < Size();i++)
			{
				_start[i] = _start[i+1];
			}
			--_finish;
		}
		return pos;
	}

	T& operator[](size_t index)// v[0] = 10
	{
		return *(Begin()+index);
	}

protected:
	void CheckStorage()
	{
		if(_finish == _EndOfStorage)
		{
			size_t size = Size();
			size_t newStorage = 2*size + 3;

			T* temp = new T[newStorage];
			if(_start != NULL)
			{
				for(size_t i = 0;i < size;i++)
				{
					temp[i] = _start[i];
				}
				delete[] _start;
			}

			_start = temp;
			_finish = _start+size;
			_EndOfStorage = _start + newStorage;
		}
	}

protected:
	Iterator _start;//指向第一个元素的位置
	Iterator _finish;//指向该容器所拥有的元素的最后一个位置的下一个位置
	Iterator _EndOfStorage;//指向该容器所能容纳的最大数量的下一个位置
};

void Print1(Vector<int>& vec)
{
	//Vector<int>::Iterator it = vec.Begin();
	//while (it != vec.End())
	//{
	//	//cout<<*it<<" ";
	//	++it;
	//}
	size_t size = vec.Size();
	for(size_t i = 0; i < size;i++)
	{
		cout<<vec[i]<<" ";
	}
	cout<<endl;
}

void Print2(const Vector<int>& vec)
{
	Vector<int>::ConstIterator it = vec.Begin();
	while (it != vec.End())
	{
		cout<<*it<<" ";
		++it;
	}
	cout<<endl;
}

void VectorTest()
{
	Vector<int> vec;
	vec.PushBack(1);
	vec.PushBack(2);
	vec.PushBack(3);
	vec.PushBack(4);
	vec.PushBack(5);
	Print1(vec);

	vec.Insert(vec.End(),7);
	cout<<"vector distance:"<<Distance(vec.Begin(),vec.End())<<endl;

	Vector<int>::Iterator it = vec.Begin();
	Advance(it,3);
	cout<<"vector Advance ? 3:  "<<*it<<endl;
	
	Print2(vec);
}