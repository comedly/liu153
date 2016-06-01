#include<iostream>
using namespace std;

//����һ�����飬����������ǰ�벿�֣�ż�����ں�벿��
void ReOrderOddEven1(int* array,unsigned int length)
{
	if(array == NULL || length <= 0)
		return ;
	int* pBegin = array;//��ָ��ָ���һ��Ԫ��
	int* pEnd = array + length - 1;//��Ԫ��ָ�����һ��Ԫ��
	while (pBegin < pEnd)
	{
		while (pBegin < pEnd && (*pBegin & 1) != 0)//ָ���Ԫ��Ϊ�����������ƶ���ָ����һ��Ԫ��
		{
			pBegin++;
		}
		while (pBegin < pEnd && (*pEnd & 1) == 0)//ָ���Ԫ��Ϊż������ǰ�ƶ���ָ��ǰһ��Ԫ��
		{
			pEnd--;
		}
		if(pBegin < pEnd)
		{
			swap(*pBegin,*pEnd);
		}
	}
}

bool isEven(int n)//�ж�n�ǲ���ż��
{
	return (n & 1) == 0;
}

void ReOrder(int* array,unsigned int length,bool (*func)(int))
{
	if(array == NULL || length <= 0)
		return ;
	int* pBegin = array;//��ָ��ָ���һ��Ԫ��
	int* pEnd = array + length - 1;//��Ԫ��ָ�����һ��Ԫ��
	while (pBegin < pEnd)
	{
		while (pBegin < pEnd && !func(*pBegin))//ָ���Ԫ��Ϊ�����������ƶ���ָ����һ��Ԫ��
		{
			pBegin++;
		}
		while (pBegin < pEnd && func(*pEnd))//ָ���Ԫ��Ϊż������ǰ�ƶ���ָ��ǰһ��Ԫ��
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