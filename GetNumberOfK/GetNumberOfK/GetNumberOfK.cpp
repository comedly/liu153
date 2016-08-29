#include<iostream>
using namespace std;

//����������������г��ֵĴ���
//����������������{1,2,3,3,3,3,4,5}����
//��3������3�������г�����4�Σ��������Ϊ4

//����kֵ��һ�γ��ֵ�λ��
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

//����kֵ���һ�γ��ֵ�λ��
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

//�ڷֱ��ҵ���һ��k�����һ��k���±�ʱ���Ϳ��Լ����k����
//���г��ֵĴ���
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
	cout<<"array ������4���ֵĴ���:"<<number<<endl;
	system("pause");
	return 0;
}