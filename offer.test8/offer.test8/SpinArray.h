#pragma once

#include<iostream>
using namespace std;

//һ����������һ������������ת���ã�����������С������
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
		if(array[indexMid] >= array[index1])//����м����ȵ�һ������˵����С����λ�ں�벿�֣����м��±긳��index1
		{
			index1 = indexMid;
		}
		else if(array[indexMid] <= array[index2])//����м��������һ������˵����С����λ��ǰ�벿�֣����м��±긳��index2
		{
			index2 = indexMid;
		}
	}
	return array[indexMid];
}

//˳�����
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

//{0,1,1,1,1}��������ת{1,0,1,1,1}��{1,1,1,0,1}
//��ʱ��һ�����֡����һ�����ֻ����м�����ֶ���1���޷��ƶ�ָ������С���ҵķ�Χ����ʱ��Ҫ������˳����������
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
		//����±�Ϊindex1��index2��indexMid��Ӧ��Ԫ�����
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