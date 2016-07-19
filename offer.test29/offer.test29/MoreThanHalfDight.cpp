#include<iostream>
using namespace std;

//����һ������Partition������O��n���㷨
//ʵ��һ�ο���
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

bool CheckInvalidArray(int* numbers,int length)//�жϸ������Ƿ���Ч����Ч����true
{
	g_bInputInvalid = false;
	if(numbers == NULL && length <= 0)
		g_bInputInvalid = true;
	return g_bInputInvalid;
}

//�����ҵĽ���Ƿ���ȷ�������ֵĴ����Ƿ�����鳤�ȵ�һ��
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

//�����������������ص��ҳ�O��n�����㷨
//�������鱣������ֵ��һ���������е�һ�����֣�һ���Ǵ����������һ�����ֺ�����֮ǰ��������ֲ�ͬ���������1���������Ϊ0��������һ�����֣���������Ҫ�ҵ����ֳ��ֵĴ����������������ֳ��ֵĴ���֮�ͻ�Ҫ�࣬��ôҪ�ҵ����ֿ϶������һ�ΰѴ�����Ϊ1ʱ��Ӧ�����֡�
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