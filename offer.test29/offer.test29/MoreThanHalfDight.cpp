#include<iostream>
using namespace std;

//方法一：基于Partition函数的O（n）算法
//实现一次快排
int Partition(int data[],int length,int left,int right)
{
	if(data == NULL || left < 0 || right >= length)
		throw new exception("Invalid Array!");
	int key = data[right];
	int begin = left;
	int end = right - 1;
	while (begin < end)
	{
		while (begin < end && data[begin] <= key)
		{
			++begin;
		}
		while (begin < end && data[end] >= key)
		{
			--end;
		}
		if(begin < end)
		{
			swap(data[begin],data[end]);
		}
	}
	if(data[begin] > data[right])
	{
		swap(data[begin],data[right]);
		return begin;
	}
	else
	{
		return right;
	}
	return begin;
}

bool g_bInputInvalid = false;

bool CheckInvalidArray(int* numbers,int length)//判断该数组是否有效，无效返回true
{
	g_bInputInvalid = false;
	if(numbers == NULL && length <= 0)
		g_bInputInvalid = true;
	return g_bInputInvalid;
}

//检查查找的结果是否正确，即出现的次数是否大数组长度的一半
bool CheckMoreThanHalf(int* numbers,int length,int number)
{
	int times = 0;
	for(int i = 0;i < length;++i)
	{
		if(numbers[i] == number)
			times++;
	}
	bool IsMoreThanHalf = true;
	if(times*2 <= length)
	{
		IsMoreThanHalf = false;
		g_bInputInvalid = true;
	}
	return IsMoreThanHalf;
}

int MoreThanHalfArray1(int* numbers,int length)
{
	if(CheckInvalidArray(numbers,length))
		return 0;
	int middle = length>>1;
	int start = 0;
	int end = length - 1;
	int index = Partition(numbers,length,start,end);
	while (index != middle)
	{
		if(index > middle)
		{
			end = index - 1;
			index = Partition(numbers,length,start,end);
		}
		else
		{
			start = index + 1;
			index = Partition(numbers,length,start,end);
		}
	}
	int result = numbers[middle];
	if(!CheckMoreThanHalf(numbers,length,result))
		result = 0;
	return result;
}

//方法二：根据数组特点找出O（n）的算法
//遍历数组保存两个值，一个是数组中的一个数字，一个是次数，如果下一个数字和我们之前保存的数字不同，则次数减1，如果次数为0，保存下一个数字，由于我们要找的数字出现的次数比其他所有数字出现的次数之和还要多，那么要找的数字肯定是最后一次把次数设为1时对应的数字。
int MoreThanHalfArray2(int* numbers,int length)
{
	if(CheckInvalidArray(numbers,length))
		return 0;
	int result = numbers[0];
	int times = 1;
	for(int i = 1;i < length;++i)
	{
		if(times == 0)
		{
			result = numbers[i];
			times = 1;
		}
		else if(numbers[i] == result)
		{
			times++;
		}
		else
		{
			times--;
		}
	}
	if(!CheckMoreThanHalf(numbers,length,result))
		return 0;
	return result;
}

int main()
{
	int a[] = {1,2,3,2,2,2,5};
	cout<<MoreThanHalfArray1(a,sizeof(a)/sizeof(a[0]))<<endl;
	cout<<MoreThanHalfArray2(a,sizeof(a)/sizeof(a[0]))<<endl;

	system("pause");
	return 0;
}