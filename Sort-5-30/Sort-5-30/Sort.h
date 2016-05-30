#pragma once
#include<iostream>
#include<assert.h>
using namespace std;


void Print(int* a,int size)//��ӡ
{
	for(int i = 0;i < size;i++)
	{
		cout<<a[i]<<" ";
	}
	cout<<endl;
}

void InsertSort(int* a,int size)//��������
{
	assert(a);
	for(int begin = 0;begin < size;begin++)
	{
		//ѡȡ��һ�����֣�������Ϊ�����������õڶ��������һ�����Ƚϣ�С�ڵ�һ�����򽻻�����֮�õ���������ǰ�������ź��������ĵڶ������Ƚϣ���С���򽻻������ø������һ�������бȽϣ����õ��ĸ�����ǰ�����ź��������Ӻ���ǰ�Ƚϣ��Դ�����
		int temp = a[begin];
		int end = begin - 1;
		while (end >= 0 && temp < a[end])
		{
			a[end + 1] = a[end];
			a[end] = temp;
			end--;
		}
	}
}

void TestInsertSort()
{
	int a[] = {2,5,1,4,9,8,0,3,6,7};
	int size = sizeof(a)/sizeof(a[0]);
	InsertSort(a,size);
	Print(a,size);
}

//ϣ������
void ShellSort(int* a,int size)
{
	assert(a);
	int gap = size;
	while (gap > 1)
	{
		gap = gap/3 + 1;
		for(int i = 0;i < size - gap;i++)
		{
			int end = i;
			int temp = a[end + gap];
			while (end >= 0 && temp < a[end])
			{
				a[end + gap] = a[end];
				a[end] = temp;
				end -= gap;
			}
		}

	}
}

void TestShellSort()
{
	int a[] = {2,5,1,4,9,8,0,3,6,7};
	int size = sizeof(a)/sizeof(a[0]);
	ShellSort(a,size);
	Print(a,size);
}

//ѡ������
void SelectSort(int* a,int size)
{
	assert(a);
	for (int i = 0; i < size; i++)
	{
		int minnum = i;//minnum��¼����һ��������С����λ�����±꣬
		for(int j = i + 1;j < size;j++)
		{
			if(a[minnum] > a[j])
			{
				minnum = j;
			}
		}
		if(i != minnum)//���i������minnum������Ҫ�����±�Ϊminnum��i��Ӧ��������С�������Ƶ�ǰ��ȥ
		{
			swap(a[i],a[minnum]);
		}
	}
}

void TestSelectSort()
{
	int a[] = {2,5,1,4,7,8,0,3,6,9};
	int size = sizeof(a)/sizeof(a[0]);
	SelectSort(a,size);
	Print(a,size);
}

//������
void AdjustDown(int parent,int* a,int size)//����
{
	int child = 2*parent + 1;
	while (child < size)
	{
		if(child + 1 <size && a[child + 1] > a[child])
			child++;
		if(a[child] > a[parent])
		{
			swap(a[child],a[parent]);
			parent = child;
			child = 2*parent +1;
		}
		else
		{
			break;
		}
	}
}

void HeapSort(int* a,int size)
{
	assert(a);
	for(int i = (size - 2)/2;i >= 0;i--)
	{
		AdjustDown(i,a,size);
	}
	for(int i = 0;i < size - 1;i++)//����дi<size,��ʱ���һ��i = size-1;size-i-1����0��a[0]��Ҫ��a[0]�ڽ���һ�Σ���д��i<size-1ʱ�ɼ���һ��ѭ�������Ч�� 
	{
		swap(a[0],a[size - i - 1]);
		AdjustDown(0,a,size - i - 1);
	}
}

void TestHeapSort()
{
	int a[] = {2,5,1,4,7,8,0,3,6,9};
	int size = sizeof(a)/sizeof(a[0]);
	HeapSort(a,size);
	Print(a,size);
}

//ð������
void BubbleSort(int* a,int size)
{
	assert(a);
	for(int i = 0;i < size;i++)
	{
		for(int j = 0;j < size - i - 1;j++)
		{
			if(a[j] > a[j+1])
			{
				swap(a[j],a[j+1]);
			}
		}
	}
}

void TestBubbleSort()
{
	int a[] = {2,5,1,4,7,8,0,3,6,9};
	int size = sizeof(a)/sizeof(a[0]);
	BubbleSort(a,size);
	Print(a,size);
}

//��������
void QuickSort(int* a,int left,int right)
{
	int low = left;
	int high = right;
	int key = a[low];
	while (low < high)
	{
		while (low < high && key <= a[high])
		{
			--high;
		}
		a[low] = a[high];
		while (low < high && key >= a[low])
		{
			++low;
		}
		a[high] = a[low];
	}
	a[low] = key;
	if(left <= right)
	{
		QuickSort(a,left,low-1);
		QuickSort(a,low+1,right);
	}
}

void TestQuickSort()
{
	int a[] = {2,5,1,4,7,8,0,3,6,9};
	int size = sizeof(a)/sizeof(a[0]);
	QuickSort(a,0,9);
	Print(a,size);
}
