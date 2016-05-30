#pragma once
#include<iostream>
#include<assert.h>
using namespace std;


void Print(int* a,int size)//打印
{
	for(int i = 0;i < size;i++)
	{
		cout<<a[i]<<" ";
	}
	cout<<endl;
}

void InsertSort(int* a,int size)//插入排序
{
	assert(a);
	for(int begin = 0;begin < size;begin++)
	{
		//选取第一个数字，将其视为有序，再依次拿第二个数与第一个数比较，小于第一个数则交换，反之拿第三个数与前两个已排好序的数组的第二个数比较，若小于则交换，在用该数与第一个数进行比较，再拿第四个数与前三个排好序的数组从后向前比较，以此类推
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

//希尔排序
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

//选择排序
void SelectSort(int* a,int size)
{
	assert(a);
	for (int i = 0; i < size; i++)
	{
		int minnum = i;//minnum记录遍历一遍数组最小的那位数的下标，
		for(int j = i + 1;j < size;j++)
		{
			if(a[minnum] > a[j])
			{
				minnum = j;
			}
		}
		if(i != minnum)//如果i不等于minnum，则需要交换下标为minnum和i对应的数，将小的数字移到前面去
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

//堆排序
void AdjustDown(int parent,int* a,int size)//建堆
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
	for(int i = 0;i < size - 1;i++)//可以写i<size,此时最后一次i = size-1;size-i-1等于0，a[0]需要与a[0]在交换一次，当写成i<size-1时可减少一次循环，提高效率 
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

//冒泡排序
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

//快速排序
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
