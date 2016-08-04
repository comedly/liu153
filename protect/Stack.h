/**************************************************************************
	>file name:Stack.h
	>auther:Comedly
	>create time:2016-8-4
***************************************************************************/

#pragma once
#include<assert.h>
using namespace std;

template<class T>
class Stack
{
public:
	Stack()//默认构造函数
		:_a(NULL)
		 ,_top(0)
		 ,_capacity(0)
	{ }

	Stack(Stack<T>& stack)//拷贝构造函数
	{
		size_t i = 0;
		size_t top = stack._top;
		_a = new T[top];
		for(;i < top;i++)
		{
			_a[i] = stack._a[i];
		}
		_capacity = stack._capacity;
	}

	Stack& operator=(Stack<T>& stack)//赋值函数
	{
		swap(_a,stack._a);
		_top = stack._top;
		_capacity = stack._capacity;
		return *this;
	}

	void Push(const T& x)
	{
		CheckCapacity();
		_a[_top++] = x;
	}

	void Pop()
	{
		assert(_top > 0);
		_top--;
	}

	T& Top()//栈顶元素
	{
		assert(_top > 0);
		return _a[_top - 1];
	}

	bool IsEmpty()//判空
	{
		if(_top == 0)
			return true;
		return false;
	}

	size_t Size()//大小
	{
		return _top;
	}

	void Print()
	{
		for(size_t i = 0 ;i < _top;i++)
		{
			cout<<_a[i]<<" ";
		}
		cout<<endl;
	}

	~Stack()//析构函数
	{
		if(_a != NULL)
		{
			delete[] _a;
		}
	}

protected:
	void CheckCapacity()
	{
		if(_top == _capacity)
		{
			_capacity = 2*_capacity + 3;
			T* temp = new T[_capacity];
			for(int i = 0;i < _top;i++)
			{
				temp[i] = _a[i];
			}
			delete [] _a;
			_a = temp;
		}
	}
protected:
	T* _a;//用一个数组来存储数据
	size_t _top;//当前栈中元素的个数
	size_t _capacity;//当前栈的容量
};
