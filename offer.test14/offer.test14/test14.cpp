#include<iostream>
using namespace std;

//输入一个数组，把奇数排在前半部分，偶数排在后半部分
void ReOrderOddEven1(int* array,unsigned int length)
{
	if(array == NULL || length <= 0)
		return ;
	int* pBegin = array;//该指针指向第一个元素
	int* pEnd = array + length - 1;//该元素指向最后一个元素
	while (pBegin < pEnd)
	{
		while (pBegin < pEnd && (*pBegin & 1) != 0)//指向的元素为奇数，不用移动，指向下一个元素
		{
			pBegin++;
		}
		while (pBegin < pEnd && (*pEnd & 1) == 0)//指向的元素为偶数，向前移动，指向前一个元素
		{
			pEnd--;
		}
		if(pBegin < pEnd)
		{
			swap(*pBegin,*pEnd);
		}
	}
}

bool isEven(int n)//判断n是不是偶数
{
	return (n & 1) == 0;
}

void ReOrder(int* array,unsigned int length,bool (*func)(int))
{
	if(array == NULL || length <= 0)
		return ;
	int* pBegin = array;//该指针指向第一个元素
	int* pEnd = array + length - 1;//该元素指向最后一个元素
	while (pBegin < pEnd)
	{
		while (pBegin < pEnd && !func(*pBegin))//指向的元素为奇数，不用移动，指向下一个元素
		{
			pBegin++;
		}
		while (pBegin < pEnd && func(*pEnd))//指向的元素为偶数，向前移动，指向前一个元素
		{
			pEnd--;
		}
		if(pBegin < pEnd)
		{
			swap(*pBegin,*pEnd);
		}
	}
}

void ReOrderOddEven2(int* array,unsigned int length)
{
	ReOrder(array,length,isEven);
}

void Test()
{
	int a[] = {1,4,2,3,8,6,7,9};
	int size = sizeof(a)/sizeof(a[0]);
	//ReOrderOddEven1(a,size);
	ReOrderOddEven2(a,size);
	for(int i = 0;i < size;i++)
	{
		cout<<a[i]<<" ";
	}
	cout<<endl;
}

int main()
{
	Test();
	system("pause");
	return 0;
}