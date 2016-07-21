#include<iostream>
#include<stdio.h>
using namespace std;

//输入一个数N，求1到N所有整数中1出现的次数

//方法一：对每个数mod（10），个位数是不是1，若为1则++，如果该数大于十，除以10继续求个位数是不是1
//如果输入数字为n，n就有O（logn）位，我们需要判断每一位是不是1，那么他的时间复杂度为O（n*logn），如果n太大，需要做大量的运算，效率不高。
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

//方法二:基于数字规律着手处理

//去掉最高位做递归，递归的次数与位数相同，一个数字n有O(log n)位，则该算法的时间复杂度为O(log n)

int PowerBase10(unsigned int n)//求10的次方
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

	//假设strN是“21345”
	//numFirstDigit是数字10000-19999的第一个位中的数目
	int numFirstDigit = 0;
	if(first > 1)
		numFirstDigit = PowerBase10(length - 1);
	else
		numFirstDigit = atoi(strN + 1) + 1;

	//numOtherDigit是1346~21345除了第一位之外的数位中的数目
	int numOtherDigit = first * (length - 1)*PowerBase10(length - 2);

	//numRecursive是1-1345中的数目
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