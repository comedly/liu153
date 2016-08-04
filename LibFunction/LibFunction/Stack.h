/**************************************************************************
	>file name:Stack.h
	>auther:Comedly
	>create time:2016-8-4
***************************************************************************/

#pragma once
#include<assert.h>

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

//包含min函数的栈
//在该类型中实现一个能够得到栈的最小元素的min函数，在该函数中调用min、push、pop，其时间复杂度为O(1)
template<class T>
class StackWithMin
{
public:
	void Push(const T& value)//插入
	{
		//先向数据栈中插入数据，然后判断辅助栈或者让该元素比较辅助栈的栈顶元素，若小于栈顶元素，插入该元素，否则插入栈顶元素
		m_data.Push(value);
		if(m_min.Size() == 0 || value < m_min.Top())
			m_min.Push(value);
		else
			m_min.Push(m_min.Top());
	}

	void Pop()//弹出
	{
		if(m_data.Size() > 0 && m_min.Size() > 0)//当数据栈和辅助栈都不为空时，弹出栈顶元素
		{
			m_data.Pop();
			m_min.Pop();
		}
	}

	T& Min()//获取当期栈中最小的值
	{
		if(m_data.Size() > 0 && m_min.Size() > 0)//当数据栈和辅助栈都不为空时，返回辅助栈的栈顶元素
			return m_min.Top();
	}
protected:
	Stack<T> m_data;//数据栈
	Stack<T> m_min;//辅助栈，保存当前栈中的的最小值，每比较一次，插入一次当前栈中最小的元素
};
