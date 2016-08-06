/**************************************************************************		>file name:Sort.h
	>author:Comedly
	>create time:2016-8-5
***************************************************************************/

#pragma once
#include<assert.h>
#include"Stack.h"

//2种插入排序
//1.直接插入
void InsertSort(int* a,int size)
{
	assert(a);
	for(int begin = 0; begin < size;begin++)
	{
		//选取第一个数，将其视为有序，再依次拿第二个数与第一个数比较，小于等一个数则交换，否则继续拿第三个数与前面两个排好序的数组的第二个元素进行比较，再用该数与第一个数继续比较，再拿第四个数与前三个排好序的数进行比较，以此类推
		int temp = a[begin];
		int end = begin - 1;
		while(end >= 0 && temp < a[end])
		{
			a[end+1] = a[end];
			a[end] = temp;
			--end;
		}
	}
}
//2.希尔排序

void ShellSort(int* a,int size)
{
	assert(a);
	int gap = size;
	while(gap > 1)
	{
		gap = gap/3 + 1;
		for(int i = 0;i < size - gap;i++)
		{
			int end = i;
			int temp = a[end + gap];
			while(end>=0 && temp<a[end])
			{
				a[end + gap] = a[end];
				a[end] = temp;
				end -= gap;
			}
		}
	}
}

//2种交换排序
//1 冒泡排序
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

//2 快速排序
//方法1：
//选定一个key值，一般选择头元素（或者尾元素），这里选择最后一个，设置两个指针///，一个指向第一个，另一个指向倒数第二个，从前选择比key大的，从后选择比key小得//进行交换

int PartSort1(int* a,int left,int right)
{
	assert(a);
	int begin = left;
	int end = right - 1;
	int key = a[right];//设置key为元素的最后一个元素

	while(begin < end)
	{
		while((begin < end) && (a[begin] <= key ))//查找比key大的元素
		{
			++begin;
		}
		while((begin < end) && (a[end] >= key))//查找比key小的
		{
			--end;
		}
		if(begin < end)
		{
			swap(a[begin],a[end]);
		}
	}
	if(a[begin] > a[right])//只有两个元素
	{
		swap(a[begin],a[right]);
		return begin;
	}
	else
	{
		return right;
	}
	return begin;
}

//方法2：挖坑法
//将右边的元素用key保存起来，此时最后一个位置相当与一个坑，将左指针找到的比key大的元素保存到key值对应的位置，此时左指针指向的位置相当与一个坑，再将右指针找到的比key小的数据放在坑中，右指针指向的位置相当与一个坑，以此类推，当相遇时，吧key值填入坑中。

//三数取中法
//若选取的数组中最大或者最小的元素作为key值，这是快速排序的最坏情况，利用三数取中法，能有效的解决这种问题，取数组头元素，尾元素，中间元素的最中间大小的数据作为key值，就能有避免这种问题

int GetMidIndex(int* a,int left,int right)
{
	assert(a);
	int mid = (left + right)/2;
	if(a[left] < a[right])
	{
		if(a[mid] < a[left])
		{
			return left;
		}
		else if(a[mid]>a[right])
		{
			return right;
		}
		else
		{
			return mid;
		}
	}
	else
	{
		if(a[mid] > a[left])
		{
			return left;
		}
		else if(a[mid] < a[right])
		{
			return right;
		}
		else
		{
			return mid;
		}
	}
}

//挖坑法
int PartSort2(int* a,int left,int right)
{
	int index = GetMidIndex(a,left,right);
	swap(a[index],a[right]);//将中间的数据与最右边的数据进行交换，将最右边的数据赋值给key
	int key = a[right];
	int begin = left;
	int end = right;
	while(begin < end)
	{
		while((begin < end)&&(a[begin] <= key))
		{
			++begin;
		}
		a[end]= a[begin];
		while((begin<end)&&(a[end] >= key))
		{
			--end;
		}
		a[begin] = a[end];
	}
	if(begin == end)
	{
		a[end] = key;
		return begin;
	}
}

//方法3：
//选定最右边的元素为key，将cur指针指向数组的头元素，cur查找较key值小的元素，
//prev指向cur-1的位置，当cur找到较小的元素，先进行prev++；若此时cur==prev，cur继续查找较key晓得元素，直到cur！=prev，则交换a[prev]和a[cur],直到cur指向数组的倒数第二个元素，这时将key与a[++prev]交换

int PartSort3(int* a,int left,int right)
{
	assert(a);
	int key = a[right];
	int cur = left;
	int prev = left - 1;
	while(cur < right)
	{
		if(a[cur] < key && ++prev != cur)
		{
			swap(a[prev],a[cur]);
		}
		++cur;
	}
	swap(a[right],a[++prev]);
	return prev;
}

//void QuickSort1(int* a,int left,int right)
//{
//	assert(a);
//	if(left >= right)
//		return;
//	//int div = PartSort1(a,left,right);
//	//int div = PartSort2(a,left,right);
//	int div = PartSort3(a,left,right);
//	QuickSort1(a,left,div-1);
//	QuickSort1(a,div+1,right);
//}

//优化
//当区间<13，采用插入排序效率高于快排，能减少程序压栈的开销
void QuickSort2(int* a,int left,int right)
{
	assert(a);
	if(left > right)
		return;
	int gap = right - left + 1;
	if(gap < 13)
	{
		InsertSort(a,gap);
	}
	int ret = PartSort1(a,left,right);
	QuickSort(a,left,ret - 1);
	QuickSort(a,ret + 1,right);
}

//利用非递归实现快速排序


//2种选择排序
//1.选择排序
void SelectSort(int* a,int size)
{
	assert(a);
	for(int i = 0; i < size ;i++)
	{
		int minnum = i;//记录遍历一遍数组后，最小数对应的下标
		for(int j = i+1;j < size;j++)
		{
			if(a[minnum] > a[j])
			{
				minnum = j;
			}
		}
		if(i != minnum)//如果i不等于minnum则需要交换这两个数据，将小的数据移到前面
		{
			swap(a[i],a[minnum]);
		}
	}
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
			parent = child;																child = 2*parent +1;													}
		else
		{
			break;																	}
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
