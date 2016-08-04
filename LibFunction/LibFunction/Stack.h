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
	Stack()//Ĭ�Ϲ��캯��
		:_a(NULL)
		 ,_top(0)
		 ,_capacity(0)
	{ }

	Stack(Stack<T>& stack)//�������캯��
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

	Stack& operator=(Stack<T>& stack)//��ֵ����
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

	T& Top()//ջ��Ԫ��
	{
		assert(_top > 0);
		return _a[_top - 1];
	}

	bool IsEmpty()//�п�
	{
		if(_top == 0)
			return true;
		return false;
	}

	size_t Size()//��С
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

	~Stack()//��������
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
	T* _a;//��һ���������洢����
	size_t _top;//��ǰջ��Ԫ�صĸ���
	size_t _capacity;//��ǰջ������
};

//����min������ջ
//�ڸ�������ʵ��һ���ܹ��õ�ջ����СԪ�ص�min�������ڸú����е���min��push��pop����ʱ�临�Ӷ�ΪO(1)
template<class T>
class StackWithMin
{
public:
	void Push(const T& value)//����
	{
		//��������ջ�в������ݣ�Ȼ���жϸ���ջ�����ø�Ԫ�رȽϸ���ջ��ջ��Ԫ�أ���С��ջ��Ԫ�أ������Ԫ�أ��������ջ��Ԫ��
		m_data.Push(value);
		if(m_min.Size() == 0 || value < m_min.Top())
			m_min.Push(value);
		else
			m_min.Push(m_min.Top());
	}

	void Pop()//����
	{
		if(m_data.Size() > 0 && m_min.Size() > 0)//������ջ�͸���ջ����Ϊ��ʱ������ջ��Ԫ��
		{
			m_data.Pop();
			m_min.Pop();
		}
	}

	T& Min()//��ȡ����ջ����С��ֵ
	{
		if(m_data.Size() > 0 && m_min.Size() > 0)//������ջ�͸���ջ����Ϊ��ʱ�����ظ���ջ��ջ��Ԫ��
			return m_min.Top();
	}
protected:
	Stack<T> m_data;//����ջ
	Stack<T> m_min;//����ջ�����浱ǰջ�еĵ���Сֵ��ÿ�Ƚ�һ�Σ�����һ�ε�ǰջ����С��Ԫ��
};
