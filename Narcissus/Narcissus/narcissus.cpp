#include<iostream>
using namespace std;

//Ë®ÏÉ»¨Êı

int cubic(int x)
{
	return x*x*x;
}

int main()
{
	int bit_0 = 0;
	int bit_1 = 0;
	int bit_2 = 0;
	for(int i = 100;i <= 999;i++)
	{
		bit_0 = i/100;
		bit_1 = i/10 - bit_0 * 10;
		bit_2 = i % 10;

		if(i == (cubic(bit_0) + cubic(bit_1) + cubic(bit_2)))
		{
			cout<<i<<"  ";
		}
	}
	cout<<endl;
	system("pause");
	return 0;
}