#include<iostream>
using namespace std;

//不使用加减乘除做加法
int GetSum(int num1,int num2)
{
	int sum ,carry;

	while (num2)
	{
		sum = num1 ^ num2;
		carry = (num1 & num2)<<1;

		num1 = sum;
		num2 = carry;
	}
	return num1;
}

int main()
{
	int ret = GetSum(10,20);
	cout<<ret<<endl;
	system("pause");
	return 0;
}