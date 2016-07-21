#include<iostream>
#include<stdio.h>
using namespace std;

//����һ����N����1��N����������1���ֵĴ���

//����һ����ÿ����mod��10������λ���ǲ���1����Ϊ1��++�������������ʮ������10�������λ���ǲ���1
//�����������Ϊn��n����O��logn��λ��������Ҫ�ж�ÿһλ�ǲ���1����ô����ʱ�临�Ӷ�ΪO��n*logn�������n̫����Ҫ�����������㣬Ч�ʲ��ߡ�
int NumberOf1(unsigned int n)
{
	unsigned int number = 0;

	while (n)
	{
		if(n % 10 == 1)
			number++;
		n = n/10;
	}
	return number;
}

int NumberOf1Between1AndN_1(unsigned int n)
{
	unsigned int number = 0;
	for(unsigned int i = 1; i <= n;i++)
	{
		number += NumberOf1(i);
	}
	return number;
}

//������:�������ֹ������ִ���

//ȥ�����λ���ݹ飬�ݹ�Ĵ�����λ����ͬ��һ������n��O(log n)λ������㷨��ʱ�临�Ӷ�ΪO(log n)

int PowerBase10(unsigned int n)//��10�Ĵη�
{
	int result = 1;
	for(unsigned int i = 0;i < n;++i)
		result *= 10;

	return result;
}

int NumberOf1_2(const char* strN)
{
	if(strN == NULL || *strN < '0' || *strN > '9' || *strN == '\0')
		return 0;

	int first = *strN - '0';
	unsigned int length = static_cast<unsigned int>(strlen(strN));

	if(length == 1 && first == 0)
		return 0;

	if(length == 1 && first > 0)
		return 1;

	//����strN�ǡ�21345��
	//numFirstDigit������10000-19999�ĵ�һ��λ�е���Ŀ
	int numFirstDigit = 0;
	if(first > 1)
		numFirstDigit = PowerBase10(length - 1);
	else
		numFirstDigit = atoi(strN + 1) + 1;

	//numOtherDigit��1346~21345���˵�һλ֮�����λ�е���Ŀ
	int numOtherDigit = first * (length - 1)*PowerBase10(length - 2);

	//numRecursive��1-1345�е���Ŀ
	int numRecursive = NumberOf1_2(strN + 1);
	return numFirstDigit + numOtherDigit + numRecursive;
}

int NumberOf1Between1AndN_2(int n)
{
	if(n <= 0)
	{
		return 0;
	}
	char strN[50];
	sprintf(strN,"%d",n);

	return NumberOf1_2(strN);
}

int main()
{
	int n;
	cin>>n;
	cout<<NumberOf1Between1AndN_1(n)<<endl;

	cout<<NumberOf1Between1AndN_2(21345)<<endl;
	cout<<NumberOf1Between1AndN_2(12)<<endl;

	system("pause");
	return 0;
}