#include<iostream>
using namespace std;

bool FindNumbersWithSum(int data[],int length,int Sum,int* num1,int* num2)
{
	bool found = false;
	if(data == NULL || num1 == NULL || num2 == NULL)
		return found;

	int begin = 0;
	int end = length - 1;

	while (begin < end)
	{
		long long CurSum = data[begin] + data[end];

		if(CurSum == Sum)
		{
			*num1 = data[begin];
			*num2 = data[end];
			found = true;
			break;
		}
		else if(CurSum > Sum)
		{
			end--;
		}
		else
		{
			begin++;
		}
	}
	return found;
}

//输入一个整数s，打印出所有和为s的连续正数序列（至少包含两
//个数字），例如输入9，由于2+3+4=4+5=9，所以结果打印出2个
//连续的序列
//以9为例，先把small初始化为1，big初始化为2，此时介于small
//和big之间的序列是{1,2}，和为3，小于9，所以下一步让序列包
//含更多的数字，将big的值增加1变为3，此时序列为{1,2,3}，和
//为6小于9，继续增加big此时序列为{1,2,3,4}，和为10大于9，
//我们要删去序列中的一些数字，于是增加small变成2，此时序列
//为{2,3,4}，和为9，输出该序列，接哈来继续增加big，重复前
//面的过程，可以找到第二个和为9的序列{4,5}。

//输出连续的序列
void PrintContinuousSequence(int small,int big)
{
	for(int i = small;i <= big;i++)
	{
		printf("%d ",i);
	}
	printf("\n");
}

//查找连续的序列使得和为num
void FindContinuousSequence(int num)
{
	if(num < 3)
		return ;

	int small = 1;
	int big = 2;
	int middle = (num + 1)/2;
	int CurNum = small + big;

	while (small < middle)
	{
		if(CurNum == num)
			PrintContinuousSequence(small,big);

		while (CurNum > num && small < middle)
		{
			//如果和大于num，则CurNum-=small，small++，
			CurNum -= small;
			small++;

			if(CurNum == num)
				PrintContinuousSequence(small,big);
		}
		big++;
		CurNum += big;
	}
}

int main()
{
	/*int array[] = {1,2,4,7,11,15};
	int length = sizeof(array)/sizeof(array[0]);
	int num1,num2;
	if(FindNumbersWithSum(array,length,16,&num1,&num2))
		cout<<"num1:"<<num1<<" "<<"num2:"<<num2<<endl;
	else
	{
		cout<<"没有找到!"<<endl;
	}*/

	FindContinuousSequence(20);
	
	system("pause");
	return 0;
}