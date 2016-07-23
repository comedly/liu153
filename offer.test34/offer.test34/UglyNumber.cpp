#include<iostream>
using namespace std;

//求按从小到大的顺序第1500个丑数
//丑数：只包含因子2、3和5的数
//判断一个数是不是丑数：如果能被2整除，就连续被2整除；如果能被3整除，就连续被3整除；如果能被5整除，就连续被5整除，如果最后的结果是1，则是，反之不是

//方法一：判断每一个数是不是，利用计数器

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

//方法二：开辟一块空间来保存按从小到大的顺序排列的丑数，在给每个数乘以2、3和5就可以获得下一个较该数组中的最大者大的丑数。

int Min(int number1,int number2,int number3)//最小值
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
	int nextUglyIndex = 1;//当前丑数的个数

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