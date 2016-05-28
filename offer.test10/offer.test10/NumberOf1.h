#pragma once

#include<iostream>
using namespace std;

//二进制中1的个数
//可能引起死循环的解法
//如果输入一个负数，因为最高位的符号位是1，移位的过程中仍需要保证该数是负数，如果一直做右移运算，就会陷入死循环
int NumberOf1_1(int n)
{
	int count = 0;
	while (n)
	{
		if(n & 1)//如果最右边一位与1与运算，结果为1，count++;
		{
			count++;
		}
		n = n >> 1;//右移一位
	}
	return count;
}

//避免死循环的写法
//此处不移动数字n，首先把n和1做与运算，判断n的最低位是不是1，接着把1左移移位，这样反复进行......
int NumberOf1_2(int n)
{
	int count = 0;
	unsigned int flags = 1;
	while (flags)
	{
		//此处循环的次数等于二进制的位数，32位需要循环32次
		if(n & flags)
		{
			count++;
		}
		flags = flags << 1;
	}
	return count;
}

//一个二进制数中有几个1就只需要循环几次
//方法：把一个整数减去1，再和原来的数进行与运算，就相当于把原来的数中最右边的那个1置成0，那么一个二进制中有多少个1就循环多少次
int NumberOf1_3(int n)
{
	int count = 0;
	while (n)
	{
		count++;
		n = n & (n - 1);
	}
	return count;
}

void Test()
{
	int n = NumberOf1_1(10);
	cout<<n<<endl;
	n = NumberOf1_2(-10);
	cout<<n<<endl;
	n = NumberOf1_3(0);
	cout<<n<<endl;
}