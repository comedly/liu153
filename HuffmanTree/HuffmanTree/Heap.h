#pragma once

#include<iostream>
using namespace std;
#include<assert.h>
#include"HuffmanTree.h"
#include<vector>

//仿函数
template<class T>
struct Less //小于
{
	bool operator() (const T& l,const T& r)
	{
		return l < r;
	}
};

template<class T>
struct Greater //大于
{
	bool operator() (const T& l,const T& r)
	{
		return l > r;
	}
};

template<class T ,class Comper = Greater<T>> //默认为大堆
class Heap
{
public:
	Heap()
		:_a(NULL)
	{ }

	//构造堆
	Heap(const T* a,int size)
	{
		//_a.reserve(size);
		assert(a);
		for(int i=0;i<size;i++)
		{
			_a.push_back(a[i]);
		}
		//建堆
		int Size = size;
		for(int i = (_a.size()-2)/2;i >= 0;i--)
		{
			_AdjustDown(i,Size);
		}
	}

	//拷贝构造
	Heap(const vector<T>& vec)
		:_a(NULL)
	{
		_a.reserve(vec.size());
		for(int i=0;i<size;i++)
		{
			_a.push_back(vec[i]);
		}
	}

	//插入一个元素x，先插入数组中，再根据具体元素大小向上调整确定插入元素的位置
	void Push(const T& x)
	{
		_a.push_back(x);
		_AdjustUp(_a.size()-1);
	}

	//删除根节点
	void Pop()
	{
		size_t size = _a.size();
		assert(size>0);//防御式编程，确保是否可以删除元素
		swap(_a[0],_a[size-1]);//若直接删除堆的根节点，会使堆的结构混乱
		_a.pop_back();//将根节点与堆的最后一个结点交换位置，此时在对元素进行删除，再进行调试
		size = _a.size();
		_AdjustDown(0,size);
	}

	//访问堆的根节点
	T& GetTop()
	{
		size_t size = _a.size();
		assert(size>0);
		return _a[0];
	}

	bool Empty()//判空
	{
		size_t size = _a.size();
		assert(size>=0);
		return size==0;
	}

	int Size()//求大小
	{
		assert(!_a.empty());
		return _a.size();
	}

	void PrintHeap()//打印
	{
		cout<<"堆的序列："<<endl;
		for(int i = 0;i < (int)Size();i++)
		{
			cout<<_a[i]<<" ";
		}
		cout<<endl;
	}

protected:
	void _AdjustDown(int parent,int size)//向下调整
	{
		//指向左孩子
		int child = parent*2 + 1; 
		while (child < size)
		{
			Comper com;
			//选出左右子节点大的那一个
			if(child+1<size && com(_a[child+1],_a[child]))
			{
				child++;
			}
			//如果子>父，则交换，并继续往下调整
			if(com(_a[child],_a[parent]))
			{
				swap(_a[child],_a[parent]);
				parent = child;
				child = parent*2+1;
			}
			else
			{
				break;
			}
		}
	}

	//向上调整
	void _AdjustUp(int child)
	{
		int parent = (child - 1)/2;
		int size = _a.size();//size 的类型为int，若为size_t循环条件且为>=0,则死循环
		Comper com;
		while (child>0)//若child为0，则说明已到根节点，无需上调
		{
			//向上调整时，无需看左右结点哪个值大，只需要看是否父节点<子节点
			if(com(_a[child],_a[parent]))
			{
				swap(_a[child],_a[parent]);
				child = parent;
				parent = (child-1)/2;
			}
			else
			{
				break;
			}
		}
	}

protected:
	vector<T> _a;
};
