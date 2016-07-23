#include<iostream>
using namespace std;

//�󰴴�С�����˳���1500������
//������ֻ��������2��3��5����
//�ж�һ�����ǲ��ǳ���������ܱ�2��������������2����������ܱ�3��������������3����������ܱ�5��������������5������������Ľ����1�����ǣ���֮����

//����һ���ж�ÿһ�����ǲ��ǣ����ü�����

bool IsUgly(int number)
{
	if(number < 0)
		return false;
	while (number % 2 == 0)
		number /= 2;
	while (number % 3 == 0)
		number /= 3;
	while(number % 5 == 0)
		number /= 5;

	return (number == 1)? true:false;
}

int GetUgly(int index)
{
	if(index <= 0)
		return 0;

	int UglyFind = 0;
	int num = 0;
	while (UglyFind < index)
	{
		++num;
		if(IsUgly(num))
		{
			++UglyFind;
		}
	}
	return num;
}

//������������һ��ռ������水��С�����˳�����еĳ������ڸ�ÿ��������2��3��5�Ϳ��Ի����һ���ϸ������е�����ߴ�ĳ�����

int Min(int number1,int number2,int number3)//��Сֵ
{
	int min = (number1 < number2) ? number1 : number2;

	min = (min < number3) ? min : number3;

	return min;
}

int GetUgly_Solution(int index)
{
	if(index <= 0)
		return 0;

	int *pUglyNumbers = new int[index];
	pUglyNumbers[0] = 1;
	int nextUglyIndex = 1;//��ǰ�����ĸ���

	int *pMultiply2 = pUglyNumbers;
	int *pMultiply3 = pUglyNumbers;
	int *pMultiply5 = pUglyNumbers;

	while (nextUglyIndex < index)
	{
		int min = Min(*pMultiply2 * 2,*pMultiply3 * 3,*pMultiply5 * 5);
		pUglyNumbers[nextUglyIndex] = min;

		while (*pMultiply2 * 2 <= pUglyNumbers[nextUglyIndex])
			++pMultiply2;
		while (*pMultiply3 * 3 <= pUglyNumbers[nextUglyIndex])
			++pMultiply3;
		while (*pMultiply5 * 5 <= pUglyNumbers[nextUglyIndex])
			++pMultiply5;

		++nextUglyIndex;
	}

	int ugly = pUglyNumbers[nextUglyIndex - 1];
	delete[] pUglyNumbers;
	return ugly;
}

int main()
{
	//cout<<GetUgly(1500)<<endl;
	//cout<<GetUgly_Solution(1500)<<endl;
	cout<<GetUgly(2)<<endl;
	cout<<GetUgly_Solution(2)<<endl;

	system("pause");
	return 0;
}