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


//������ջʵ��һ������
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
		//stack1ֻ��Ҫֱ��ѹ��
		stack1.Push(x);
	}

	T DeleteHead()
	{
		if(stack2.Size() <= 0)//stack2Ϊ��
		{
			//���ν�ջ1�е�Ԫ�ص�����ѹ��stack2����ʱλ��stack2ջ���ϵ�Ԫ��Ϊͷ��㣬��Ҫɾ����ֱ��pop�Ϳ����ˣ���ʱ�������Ҫѹ��Ԫ��ֱ��ѹ��stack1���ɣ�λ��stack2ջ����Ԫ����ȻΪͷ��㣬����ʱstack2���ˣ�����Ҫ��stack1��Ԫ�ص�����ѹ��stack2�У�ɾ��ֻ��pop��stack2��ջ��Ԫ�ؼ���
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
		cout<<"ɾ��ͷ��㣺"<<head<<endl;
		stack2.Pop();
		return head;//����ɾ����ͷ���
	}

protected:
	Stack<T> stack1;
	Stack<T> stack2;
};