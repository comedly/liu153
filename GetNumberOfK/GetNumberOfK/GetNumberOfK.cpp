#include<iostream>
using namespace std;

//数字在排序的数组中出现的次数
//例如输入排序数组{1,2,3,3,3,3,4,5}和数
//字3，由于3在数组中出现了4次，所以输出为4

//查找k值第一次出现的位置
int GetFirstK(int* data,int length,int k,int start,int end)
{
	if(start > end)
		return -1;

	int middleIndex = (start + end) / 2;
	int middleData = data[middleIndex];

	if(middleData == k)
	{
		if ((middleIndex > 0 && data[middleIndex-1] != k) || middleIndex == 0)
		{
			return middleIndex;
		}
		else
		{
			end = middleIndex - 1;
		}
	}
	else if(middleData > k)
	{
		end = middleIndex - 1;
	}
	else
	{
		start = middleIndex + 1;
	}

	return GetFirstK(data,length,k,start,end);
}

//查找k值最后一次出现的位置
int GetLastK(int* data,int length,int k,int start,int end)
{
	if(start > end)
		return -1;

	int middleIndex = (start + end) / 2;
	int middleData = data[middleIndex];

	if(middleData == k)
	{
		if((middleIndex < length - 1 && data[middleIndex + 1] != k) || middleIndex == length - 1)
		{
			return middleIndex;
		}
		else
		{
			start = middleIndex + 1;
		}
	}
	else if(middleData < k)
	{
		start =middleIndex + 1;
	}
	else
	{
		end = middleIndex - 1;
	}

	return GetLastK(data,length,k,start,end);
}

//在分别找到第一个k和最后一个k的下标时，就可以计算出k在数
//组中出现的次数
int GetNumberOfK(int* data,int length,int k)
{
	int number = 0;
	
	if(data != NULL && length > 0)
	{
		int first = GetFirstK(data,length,k,0,length-1);
		int last = GetLastK(data,length,k,0,length-1);

		if(first > -1 && last > -1)
		{
			number = last - first + 1;
		}
	}
	return number;
}

int main()
{
	int array[] = {1,2,3,4,4,4,4,5,6};
	int length = sizeof(array)/sizeof(array[0]);
	int number = GetNumberOfK(array,length,4);
	cout<<"array 数组中4出现的次数:"<<number<<endl;
	system("pause");
	return 0;
}