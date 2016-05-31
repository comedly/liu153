#pragma once
#include<iostream>
using namespace std;

//打印1到最大的n位数
//例如输入3 打印出1...999

bool Createnumber(char* number)//实现在表示数字的字符串number上加1，当字符串里的数字都是9时，此时加1时，第一位会产生进位，表示已达到最大数，停止加1
{
	bool IsOverFlow = false;
	int nTakeOver = 0;
	int nlength = strlen(number);
	for(int i = nlength - 1;i >= 0;i--)
	{
		int nSum = number[i] - '0' + nTakeOver;
		if(i == nlength - 1)
		{
			nSum++;
		}
		if(nSum >= 10)
		{
			if(i == 0)
			{
				IsOverFlow = true;
			}
			else
			{
				nSum -= 10;
				nTakeOver = 1;
				number[i] = '0' + nSum;
			}
		}
		else
		{
			number[i] = nSum + '0';
			break;
		}
	}
	return IsOverFlow;
}

void PrintNumber(char* number)//打印
{
	bool isBeginNumber = true;
	int length = strlen(number);
	for(int i = 0;i < length;i++)
	{
		if(isBeginNumber && number[i] != '0')
		{
			isBeginNumber = false;
		}
		if(!isBeginNumber)
		{
			printf("%c",number[i]);
		}
	}
	printf(" ");
}

void Print1ToMaxOfNDigits(int n)
{
	if(n <= 0)
		return ;

	char* number = new char[n + 1];
	memset(number,'0',n);
	number[n] = '\0';

	while (!Createnumber(number))
	{
		PrintNumber(number);
	}
	printf("\n");
	delete[] number;
}

//将数字转换为全排列问题，递归使用让代码更简洁

void Print1ToMaxOfNDigitsRecursively(char* number,int length,int index)
{
	if(index == length - 1)
	{
		PrintNumber(number);
		return;
	}
	for(int i = 0;i < 10;++i)
	{
		number[index + 1] = i + '0';
		Print1ToMaxOfNDigitsRecursively(number,length,index + 1);
	}
}

void Print1ToMaxOfNDigitsRecursion(int n)
{
	if(n <= 0)
		return;
	char* number = new char[n + 1];
	number[n] = '\0';
	
	for(int i = 0;i < 10;++i)
	{
		number[0] = i + '0';
		Print1ToMaxOfNDigitsRecursively(number,n,0);
	}
	delete[] number; 
}