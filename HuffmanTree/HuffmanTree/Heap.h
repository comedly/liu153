#pragma once

#include<iostream>
using namespace std;
#include<assert.h>
#include"HuffmanTree.h"
#include<vector>

//�º���
template<class T>
struct Less //С��
{
	bool operator() (const T& l,const T& r)
	{
		return l < r;
	}
};

template<class T>
struct Greater //����
{
	bool operator() (const T& l,const T& r)
	{
		return l > r;
	}
};

template<class T ,class Comper = Greater<T>> //Ĭ��Ϊ���
class Heap
{
public:
	Heap()
		:_a(NULL)
	{ }

	//�����
	Heap(const T* a,int size)
	{
		//_a.reserve(size);
		assert(a);
		for(int i=0;i<size;i++)
		{
			_a.push_back(a[i]);
		}
		//����
		int Size = size;
		for(int i = (_a.size()-2)/2;i >= 0;i--)
		{
			_AdjustDown(i,Size);
		}
	}

	//��������
	Heap(const vector<T>& vec)
		:_a(NULL)
	{
		_a.reserve(vec.size());
		for(int i=0;i<size;i++)
		{
			_a.push_back(vec[i]);
		}
	}

	//����һ��Ԫ��x���Ȳ��������У��ٸ��ݾ���Ԫ�ش�С���ϵ���ȷ������Ԫ�ص�λ��
	void Push(const T& x)
	{
		_a.push_back(x);
		_AdjustUp(_a.size()-1);
	}

	//ɾ�����ڵ�
	void Pop()
	{
		size_t size = _a.size();
		assert(size>0);//����ʽ��̣�ȷ���Ƿ����ɾ��Ԫ��
		swap(_a[0],_a[size-1]);//��ֱ��ɾ���ѵĸ��ڵ㣬��ʹ�ѵĽṹ����
		_a.pop_back();//�����ڵ���ѵ����һ����㽻��λ�ã���ʱ�ڶ�Ԫ�ؽ���ɾ�����ٽ��е���
		size = _a.size();
		_AdjustDown(0,size);
	}

	//���ʶѵĸ��ڵ�
	T& GetTop()
	{
		size_t size = _a.size();
		assert(size>0);
		return _a[0];
	}

	bool Empty()//�п�
	{
		size_t size = _a.size();
		assert(size>=0);
		return size==0;
	}

	int Size()//���С
	{
		assert(!_a.empty());
		return _a.size();
	}

	void PrintHeap()//��ӡ
	{
		cout<<"�ѵ����У�"<<endl;
		for(int i = 0;i < (int)Size();i++)
		{
			cout<<_a[i]<<" ";
		}
		cout<<endl;
	}

protected:
	void _AdjustDown(int parent,int size)//���µ���
	{
		//ָ������
		int child = parent*2 + 1; 
		while (child < size)
		{
			Comper com;
			//ѡ�������ӽڵ�����һ��
			if(child+1<size && com(_a[child+1],_a[child]))
			{
				child++;
			}
			//�����>�����򽻻������������µ���
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

	//���ϵ���
	void _AdjustUp(int child)
	{
		int parent = (child - 1)/2;
		int size = _a.size();//size ������Ϊint����Ϊsize_tѭ��������Ϊ>=0,����ѭ��
		Comper com;
		while (child>0)//��childΪ0����˵���ѵ����ڵ㣬�����ϵ�
		{
			//���ϵ���ʱ�����迴���ҽ���ĸ�ֵ��ֻ��Ҫ���Ƿ񸸽ڵ�<�ӽڵ�
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
