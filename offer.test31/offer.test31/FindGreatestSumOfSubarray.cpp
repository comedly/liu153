#include<iostream>
using namespace std;

//����һ�����飬�����и��������������������ĺ͵����ֵ

bool g_InvalidInput = false;//����һ��ȫ�ֱ���������������Ƿ���Ч��������ص���0��������������ĺ͵����ֵΪ0������Ч����ķ���ֵ

//{1,-2,3,10,-4,7,2,-5 }
//����            ����              �ۼ�������ĺ�             ���������ĺ�
//1               ��1                   1                          1
//2               ��-2                  -1                         1
//3            ����ǰ��ĺ�-1����3      3                          3
//4               ��10                  13                         13
//5               ��-4                  9                          13
//6               ��7                   16                         16
//7               ��2                   18                         18
//8               ��-5                  13                         18

int FindGreatestSumOfSubarray(int* Numbers,int length)
{
	if((Numbers == NULL) || (length <= 0))
	{
		g_InvalidInput = true;
		return 0;
	}

	g_InvalidInput = false;

	int nCurSum = 0;//��ǰ������ĺ�
	int nGreatestSum = 0x80000000;//��ǰ������͵����ֵ
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