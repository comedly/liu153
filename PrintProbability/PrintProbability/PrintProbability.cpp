#include<iostream>
#include<math.h>
using namespace std;


//把n个塞子扔到地上，所有塞子朝上一面的点数之和为s，输入n，打印出s的所有可能的值出现的概率

//基于递归求塞子点数，时间效率不够高。
int g_maxValue = 6;

void Probability(int original,int current,int sum,int* pProbabilities)
{
	if(current == 1)
	{
		pProbabilities[sum - original]++;
	}
	else
	{
		for (int i = 1; i <= g_maxValue; ++i)
		{
			Probability(original,current-1,i+sum,pProbabilities);
		}
	}
}

void Probability(int number,int* pProbabilities)
{
	for (int i = 1; i <= g_maxValue; ++i)
	{
		Probability(number,number,i,pProbabilities);
	}
}

void Pribability(int number)
{
	if(number < 1)
		return;

	int maxSum = number * g_maxValue;
	//开辟一个空间大小为6n-n+1的数组，勇于保存s出现的次数
	int* pProbabilities = new int[maxSum - number + 1];
	for (int i = number; i <= maxSum; i++)
	{
		pProbabilities[i - number] = 0;
	}

	Probability(number,pProbabilities);

	int total = pow((double)g_maxValue,number);

	for (int i = number; i <= maxSum; ++i)
	{
		double ratio = (double)pProbabilities[i - number]/total;
		printf("%d: %e\n",i,ratio);
	}

	delete[] pProbabilities;
}

//基于循环求塞子点数，时间性能好
void PrintProbability(int number)
{
	if(number < 1)
		return;

	int* pProbabilities[2];
	pProbabilities[0] = new int[g_maxValue * number + 1];
	pProbabilities[1] = new int[g_maxValue * number + 1];

	for (int i = 0; i < g_maxValue * number + 1; ++i)
	{
		pProbabilities[0][i] = 0;
		pProbabilities[1][i] = 0;
	}

	int flags = 0;
	for (int i = 1; i <= g_maxValue; ++i)
	{
		pProbabilities[flags][i] = 1;
	}

	for (int k = 2; k <= number; ++k)
	{
		for(int i = 0;i < k;++i)
			pProbabilities[1-flags][i] = 0;
		for (int i = k; i <= g_maxValue * k; ++i)
		{
			pProbabilities[1-flags][i] = 0;

			for(int j = 1;j <= i && j<= g_maxValue;++j)
				pProbabilities[1-flags][i] += pProbabilities[flags][i-j];
		}
		flags = 1 - flags;
	}

	double total = pow((double)g_maxValue,number);
	for(int i = number;i <= g_maxValue * number;++i)
	{
		double ratio = (double)pProbabilities[flags][i]/total;
		printf("%d: %e\n",i,ratio);
	}

	delete[] pProbabilities[0];
	delete[] pProbabilities[1];
}

int main()
{
	//Pribability(3);
	PrintProbability(3);
	system("pause");
	return 0;
}