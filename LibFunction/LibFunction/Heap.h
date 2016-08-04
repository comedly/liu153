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

// �º���
// <С��
template<class T>
struct Less
{
	bool operator()(const T& l,const T& r)
	{
		return l < r;
	}
};

// >����
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

		Heap(const T* a,int size)//�����
		{
			assert(a);
			for(int i = 0;i < size;i++)
			{
				_a.push_back(a[i]);
			}
			//����
			int Size = size;
			for(int i = (_a.size() - 2)/2;i >= 0;i--)
			{
				_AdjustDown(i,Size);
			}
		}

		//��������
		Heap(const vector<T>& vec)
			:_a(NULL)
		{
			_a.reserve(vec.size());
			for(int i = 0;i < vec.size();i++)
			{
				_a.push_back(vec[i]);
			}
		}

		//����һ��Ԫ�أ��Ȳ��������У��ڸ��ݾ���Ԫ�ش�С���ϵ���ȷ������Ԫ�ص�λ��
		void push(const T& x)
		{
			_a.push_back(x);
			_AdjustUp(_a.size() - 1);
		}

		//ɾ�����ڵ�
		void pop()
		{
			size_t size = _a.size();
			assert(size > 0);//����ʽ��̣�ȷ���Ƿ����ɾ��Ԫ��
			swap(_a[0],_a[size - 1]);//��ֱ��ɾ�����ڵ㣬��ʹ�ѻ���
			_a.pop_back();//�����ڵ���ѵ����һ���ڵ㽻�����ٶѸ�Ԫ��ɾ�����ٽ��е���
			size = _a.size();
			_AdjustDown(0,size);
		}

		T& GetTop()//���ʶѵĸ��ڵ�
		{
			size_t size = _a.size();
			assert(size > 0);
			return _a[0];
		}

		bool empty()//�п�
		{
			size_t size = _a.size();
			assert(size >= 0);
			return size == 0;
		}

		size_t Size()//���С
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
		void _AdjustDown(int parent,int size)//���µ���
		{
			int child = 2*parent+1;//ָ��parent����ڵ�
			Comp com; 
			while(child < size)
			{
				//ѡ�����ҽڵ�����һ��
				if(child + 1 < size && com(_a[child+1],_a[child]))
					child++;

				//�����>�����򽻻����������µ���
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


		void _AdjustUp(int child)//���ϵ���
		{
			int parent = (child - 1)/2;
			int Size = _a.size();//Size������Ϊint����Ϊsize_tѭ��������Ϊ���ڵ���0��������ѭ��
			Comp com;
			while(child > 0)//��childΪ0��˵���ѵ����ڵ㣬��������
			{
				//���ϵ�������Ƚ����ҽڵ�Ĵ�С��ֻ��Ƚϸ��ӽڵ�
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


//���ö�����
//��һ�����

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
	for(int i = (size - 2)/2;i >= 0;i--)//���ɴ��
	{
		AdjustDown(a,size,i);
	}
	
	//������һ��Ԫ�غ����һ��Ԫ�أ��ټ������������Ž�����һ���͵����ڶ���Ԫ�أ��������Դ�����
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

//�ҳ�N���������ǰK����
//ͨ������һ������K�����ֵ�С�ѣ���N������С�ѵĸ��ڵ���бȽϣ����ڸ��ڵ㣬����������ڵ㽻��,���µ�����

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
	int *arr = new int[K];//����һ���µĿռ���������K��ֵ
	for(int i = 0;i < K;i++)
	{
		arr[i] = a[i];
	}
	for(int i= (K - 2)/2;i >= 0;i--)//����
	{
		_AdjustDownSmall(arr,K,i);
	}

	//����
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