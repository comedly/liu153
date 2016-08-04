/**************************************************************************
	>file name:Heap.h
	>auther:Comedly
	>create time:2016-8-4
***************************************************************************/

#pragma once

#include<iostream>
#include<assert.h>
#include<vector>
using namespace std;

// 仿函数
// <小于
template<class T>
struct Less
{
	bool operator()(const T& l,const T& r)
	{
		return l < r;
	}
};

// >大于
template<class T>
struct Greater
{
	bool operator()(const T& l,const T& r)
	{
		return l > r;
	}
};

template<class T,class Comp = Greater<T> >//default big Heap
class Heap
{
	public:
		Heap()
			:_a(NULL)
		{ }

		Heap(const T* a,int size)//构造堆
		{
			assert(a);
			for(int i = 0;i < size;i++)
			{
				_a.push_back(a[i]);
			}
			//建堆
			int Size = size;
			for(int i = (_a.size() - 2)/2;i >= 0;i--)
			{
				_AdjustDown(i,Size);
			}
		}

		//拷贝构造
		Heap(const vector<T>& vec)
			:_a(NULL)
		{
			_a.reserve(vec.size());
			for(int i = 0;i < vec.size();i++)
			{
				_a.push_back(vec[i]);
			}
		}

		//插入一个元素，先插入数组中，在根据具体元素大小向上调整确定插入元素的位置
		void push(const T& x)
		{
			_a.push_back(x);
			_AdjustUp(_a.size() - 1);
		}

		//删除根节点
		void pop()
		{
			size_t size = _a.size();
			assert(size > 0);//防御式编程，确保是否可以删除元素
			swap(_a[0],_a[size - 1]);//若直接删除根节点，会使堆混乱
			_a.pop_back();//将根节点与堆的最后一个节点交换，再堆该元素删除，再进行调试
			size = _a.size();
			_AdjustDown(0,size);
		}

		T& GetTop()//访问堆的根节点
		{
			size_t size = _a.size();
			assert(size > 0);
			return _a[0];
		}

		bool empty()//判空
		{
			size_t size = _a.size();
			assert(size >= 0);
			return size == 0;
		}

		size_t Size()//求大小
		{
			size_t size = _a.size();
			assert(size >= 0);
			return size;
		}
		
		void Print()
		{
			size_t size = _a.size();
			for(size_t i = 0;i < size;i++)
			{
				cout<<_a[i]<<" ";
			}
			cout<<endl;
		}

	protected:
		void _AdjustDown(int parent,int size)//向下调整
		{
			int child = 2*parent+1;//指向parent的左节点
			Comp com; 
			while(child < size)
			{
				//选出左右节点大的那一个
				if(child + 1 < size && com(_a[child+1],_a[child]))
					child++;

				//如果子>父，则交换，继续向下调整
				if(com(_a[child],_a[parent]))
				{
					swap(_a[child],_a[parent]);
					parent = child;
					child = 2 * child + 1;
				}
				else
					break;
			}
		}


		void _AdjustUp(int child)//向上调整
		{
			int parent = (child - 1)/2;
			int Size = _a.size();//Size的类型为int，若为size_t循环条件且为大于等于0，出现死循环
			Comp com;
			while(child > 0)//若child为0，说明已到根节点，无需上移
			{
				//向上调整无需比较左右节点的大小，只需比较父子节点
				if(com(_a[child],_a[parent]))
				{
					swap(_a[child],_a[parent]);
					child = parent;
					parent = (child - 1)/2;
				}
				else
					break;
			}
		}

	protected:
		vector<T> _a;
};


//利用堆排序
//建一个大堆

void AdjustDown(int* a,int size,int parent)
{
	int child = 2*parent+1;
	Greater<int> great;
	while(child < size)
	{
		if(child+1 < size && great(a[child+1],a[child]))
		{
			++child;
		}
		if(great(a[child],a[parent]))
		{
			swap(a[child],a[parent]);
			parent = child;
			child = 2*parent+1;
		}
		else
			break;
	}
}

void Heap_Sort(int* a,int size)
{
	if(a == NULL)
		return;
	for(int i = (size - 2)/2;i >= 0;i--)//建成大堆
	{
		AdjustDown(a,size,i);
	}
	
	//交换第一个元素和最后一个元素，再继续调整，接着交换第一个和倒数第二个元素，调整，以此类推
	for(int i = 0;i < size;i++)
	{
		swap(a[0],a[size - i - 1]);
		AdjustDown(a,size - i - 1,0);
	}
}


void Print(int* a,int size)
{
	assert(a);
	for(int i = 0;i < size;i++)
	{
		cout<<a[i]<<" ";
	}
	cout<<endl;
}

//找出N个数中最大前K个数
//通过建立一个含有K个数字的小堆，让N个数与小堆的根节点进行比较，大于根节点，将该数与根节点交换,重新调整堆

void _AdjustDownSmall(int* a,int size,int parent)
{
	assert(a);
	int child = 2*parent+1;
	while(child < size)
	{
		if(child + 1 < size && a[child] > a[child + 1])
		{
			++child;
		}
		if(a[child] < a[parent])
		{
			swap(a[child],a[parent]);
			parent = child;
			child = 2*parent+1;
		}
		else
		{
			break;
		}
	}
}

//find big k digits in N digits
int* HeapSet(int* a,int N,int K)
{
	assert(a);
	assert(K>0);
	int *arr = new int[K];//开辟一块新的空间来保存这K个值
	for(int i = 0;i < K;i++)
	{
		arr[i] = a[i];
	}
	for(int i= (K - 2)/2;i >= 0;i--)//建堆
	{
		_AdjustDownSmall(arr,K,i);
	}

	//调整
	for(int i = K;i < N;i++)
	{
		if(a[i] >arr[0])
		{
			arr[0] = a[i];
			_AdjustDownSmall(arr,K,0);
		}
	}
	return arr;
	delete[] arr;
}