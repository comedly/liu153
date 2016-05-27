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

	Stack(const Stack<T>& st)//拷贝构造函数
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

	Stack<T>& operator=(Stack<T>& st)//赋值
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

	void Push(const T& x)//压栈
	{
		_CheckCapacity();
		_a[_top++] = x;
	}

	void Pop()//出栈
	{
		assert(_top > 0);
		--_top;
	}

	bool Empty()//判空
	{
		if(_top == 0)
			return true;
		return false;
	}

	T& Top()//求取栈顶元素
	{
		assert(_top >= 0);
		return _a[_top - 1];

	}
	
	size_t Size()//栈中所包含元素
	{
		return _top;
	}

protected:
	void _CheckCapacity()//检测容量
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
	size_t _top;//实际存储元素的个数
	size_t _capacity;//容量
};


//用两个栈实现一个队列
template<class T>
class Cqueue
{
public:
	Cqueue()
	{ }

	~Cqueue()
	{ }

	void AppendTail(const T& x)
	{
		//stack1只需要直接压人
		stack1.Push(x);
	}

	T DeleteHead()
	{
		if(stack2.Size() <= 0)//stack2为空
		{
			//依次将栈1中的元素弹出并压人stack2，此时位于stack2栈顶上的元素为头结点，若要删除，直接pop就可以了，此时如果还需要压人元素直接压人stack1即可，位于stack2栈顶的元素仍然为头结点，若此时stack2空了，则需要将stack1的元素弹出并压人stack2中，删除只需pop掉stack2的栈顶元素即可
			while (stack1.Size() > 0)
			{
				T& data = stack1.Top();
				stack1.Pop();
				stack2.Push(data);
			}
		}
		if(stack2.Size() == 0)
		{
			throw new exception("queue isempty!");
		}
		T head = stack2.Top();
		cout<<"删除头结点："<<head<<endl;
		stack2.Pop();
		return head;//返回删除的头结点
	}

protected:
	Stack<T> stack1;
	Stack<T> stack2;
};