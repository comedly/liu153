#pragma once
#include<iostream>
using namespace std;

//��ӡ1������nλ��
//��������3 ��ӡ��1...999

bool Createnumber(char* number)//ʵ���ڱ�ʾ���ֵ��ַ���number�ϼ�1�����ַ���������ֶ���9ʱ����ʱ��1ʱ����һλ�������λ����ʾ�Ѵﵽ�������ֹͣ��1
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

void PrintNumber(char* number)//��ӡ
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

//������ת��Ϊȫ�������⣬�ݹ�ʹ���ô�������

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