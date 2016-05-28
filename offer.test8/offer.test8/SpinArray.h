#pragma once

#include<iostream>
using namespace std;

//一个数组是另一个有序数组旋转所得，求数组中最小的数字
int SpinArrayMin(int* array,int length)
{
	if(array == NULL || length <= 0)
	{
		throw new exception("Invalid array!");
	}
	int index1 = 0;
	int index2 = length - 1;
	int indexMid = index1;
	while (array[index1] >= array[index2])
	{
		if(index2 - index1 == 1)
		{
			indexMid = index2;
			break;
		}
		indexMid = (index1 + index2)/2;
		if(array[indexMid] >= array[index1])//如果中间数比第一个数大，说明最小的数位于后半部分，将中间下标赋给index1
		{
			index1 = indexMid;
		}
		else if(array[indexMid] <= array[index2])//如果中间数比最后一个数大，说明最小的数位于前半部分，将中间下标赋给index2
		{
			index2 = indexMid;
		}
	}
	return array[indexMid];
}

//顺序查找
int MinOrder(int* array,int index1,int index2)
{
	int result = array[index1];
	for(int i = index1;i <= index2;i++)
	{
		if(result > array[i])
			result = array[i];
	}
	return result;
}

//{0,1,1,1,1}的两个旋转{1,0,1,1,1}和{1,1,1,0,1}
//此时第一个数字、最后一个数字还有中间的数字都是1，无法移动指针来缩小查找的范围，此时需要我们用顺序查找来解决
int Min(int* array,int length)
{
	if(array == NULL || length <= 0)
		throw new exception("invalid array!");
	int index1 = 0;
	int index2 = length - 1;
	int indexMid = index1;
	while (array[index1] >= array[index2])
	{
		if(index2 - index1 == 1)
		{
			indexMid = index2;
			break;
		}
		indexMid = (index1 + index2)/2;
		//如果下标为index1、index2、indexMid对应的元素相等
		if(array[index1] == array[index2] && array[indexMid] == array[index1])
		{
			return MinOrder(array,index1,index2);
		}
		if(array[index1] <= array[indexMid])
			index1 = indexMid;
		else if(array[index2] >= array[indexMid])
			index2 = indexMid;
	}
	return array[indexMid];
}