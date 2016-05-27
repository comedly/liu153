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

//86