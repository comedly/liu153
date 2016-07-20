#include<iostream>
using namespace std;

//输入一个数组，有正有负，输出所有连续子数组的和的最大值

bool g_InvalidInput = false;//定义一个全局变量，来标记输入是否有效，如果返回的是0，以区分字数组的和的最大值为0还是无效输入的返回值

//{1,-2,3,10,-4,7,2,-5 }
//步骤            操作              累加子数组的和             最大子数组的和
//1               加1                   1                          1
//2               加-2                  -1                         1
//3            抛弃前面的和-1，加3      3                          3
//4               加10                  13                         13
//5               加-4                  9                          13
//6               加7                   16                         16
//7               加2                   18                         18
//8               加-5                  13                         18

int FindGreatestSumOfSubarray(int* Numbers,int length)
{
	if((Numbers == NULL) || (length <= 0))
	{
		g_InvalidInput = true;
		return 0;
	}

	g_InvalidInput = false;

	int nCurSum = 0;//当前字数组的和
	int nGreatestSum = 0x80000000;//当前字数组和的最大值
	for(int i = 0;i < length;i++)
	{
		if(nCurSum <= 0)
			nCurSum = Numbers[i];
		else
			nCurSum += Numbers[i];

		if(nCurSum > nGreatestSum)
			nGreatestSum = nCurSum;
	}
	return nGreatestSum;
}

int main()
{
	int a[] = {1,-2,3,10,-4,7,2,-5 };
	cout<<FindGreatestSumOfSubarray(a,sizeof(a)/sizeof(a[0]))<<endl;
	system("pause");
	return 0;
}