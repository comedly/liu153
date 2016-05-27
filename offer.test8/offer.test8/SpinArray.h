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

//86