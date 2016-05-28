#pragma once
#include<iostream>
using namespace std;

//递归实现斐波那契数列
unsigned long long Fib(int n)
{
	return (n <= 1)? n : (Fib(n-1) + Fib(n-2));
}

//非递归实现斐波那契数列
unsigned long long Fib2(int n)
{
	unsigned long long first = 0;
	unsigned long long second = 1;
	unsigned long long ret = 0;
	if(n <= 1)
	{
		return n;
	}
	for(int i = 2;i <= n;i++)
	{
		ret = first + second;
		first = second;
		second = ret;
	}
	return ret;
}

//斐波那契数列优化1
unsigned long long FibArray1(size_t n)
{
	unsigned long long* fibarray = new unsigned long long[n + 1];
	unsigned long long ret = 0;
	fibarray[0] = 0;
	fibarray[1] = 1;
	for(size_t i = 2;i <= n;++i)
	{
		fibarray[i] = fibarray[i-1] + fibarray[i-2];
	}
	ret = fibarray[n];
	delete[] fibarray;
	return ret;
}

//斐波那契数列优化2
unsigned long long FibArray2(size_t n)
{
	unsigned long long fibarray[3] = {0,1,n};
	for(size_t i = 2;i <= n;++i)
	{
		fibarray[2] = fibarray[0] + fibarray[1];
		fibarray[0] = fibarray[1];
		fibarray[1] = fibarray[2];
	}
	return fibarray[2];
}

void Test()
{
	size_t ret = 0;
	ret = Fib(10);
	cout<<ret<<endl;
	ret = Fib2(20);
	cout<<ret<<endl;
	ret = FibArray1(100);
	cout<<ret<<endl;
	ret = FibArray2(100);
	cout<<ret<<endl;
}