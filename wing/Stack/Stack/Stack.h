#pragma once
#include<iostream>
#include<cassert>
using namespace std;

template<class T>
class Stack
{
public:
	Stack()
		:_a(NULL)
		,_top(0)
		,_capacity(0)
	{ }

	Stack(const Stack<T>& st)//�������캯��
	{
		size_t i = 0;
		_top = st._top;
		_a = new T[_top];
		for(i = 0;i < _top;i++)
		{
			_a[i] = st._a[i];
		}
		_capacity = st._top;
	}

	Stack<T>& operator=(Stack<T>& st)//��ֵ
	{
		if(this != &st)
		{
			swap(_a,st._a);
			swap(_top,st._top);
			swap(_capacity,st._capacity);
		}
		return *this;
	}

	~Stack()
	{
		if(_a != NULL)
		{
			delete[] _a;
		}
	}

	void Push(const T& x)//ѹջ
	{
		_CheckCapacity();
		_a[_top++] = x;
	}

	void Pop()//��ջ
	{
		assert(_top > 0);
		--_top;
	}

	bool Empty()//�п�
	{
		if(_top == 0)
			return true;
		return false;
	}

	T& Top()//��ȡջ��Ԫ��
	{
		assert(_top >= 0);
		return _a[_top - 1];

	}
	
	size_t Size()//ջ��������Ԫ��
	{
		return _top;
	}

protected:
	void _CheckCapacity()//�������
	{
		if(_top == _capacity)
		{
			_capacity = 2*_capacity+3;
			T* temp = new T[_capacity];
			for(size_t i = 0;i < _top;i++)
			{
				temp[i] = _a[i];
			}
			delete[] _a;
			_a = temp;
		}
	}

protected:
	T* _a;
	size_t _top;//ʵ�ʴ洢Ԫ�صĸ���
	size_t _capacity;//����
};