#pragma once

#include<iostream>
using namespace std;

template<class T>
class Vector
{
public:
	typedef T ValueType;
	typedef ValueType* Iterator;
	typedef const ValueType* ConstIterator;

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

	void Insert(Iterator pos, const T& x)
	{
		CheckStorage();
		for(Iterator it = _finish;it != pos;it--)
		{

		}
		
		for()
	}
	Iterator Erase(Iterator pos);
	T& operator[](size_t index);// v[0] = 10;

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
	Iterator _start;//ָ���һ��Ԫ�ص�λ��
	Iterator _finish;//ָ���������ӵ�е�Ԫ�ص����һ��λ�õ���һ��λ��
	Iterator _EndOfStorage;//ָ��������������ɵ������������һ��λ��
};

void Print1(Vector<int>& vec)
{
	Vector<int>::Iterator it = vec.Begin();
	while (it != vec.End())
	{
		cout<<*it<<" ";
		++it;
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
	Print2(vec);
}