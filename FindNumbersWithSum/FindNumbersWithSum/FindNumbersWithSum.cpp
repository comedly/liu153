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

//����һ������s����ӡ�����к�Ϊs�������������У����ٰ�����
//�����֣�����������9������2+3+4=4+5=9�����Խ����ӡ��2��
//����������
//��9Ϊ�����Ȱ�small��ʼ��Ϊ1��big��ʼ��Ϊ2����ʱ����small
//��big֮���������{1,2}����Ϊ3��С��9��������һ�������а�
//����������֣���big��ֵ����1��Ϊ3����ʱ����Ϊ{1,2,3}����
//Ϊ6С��9����������big��ʱ����Ϊ{1,2,3,4}����Ϊ10����9��
//����Ҫɾȥ�����е�һЩ���֣���������small���2����ʱ����
//Ϊ{2,3,4}����Ϊ9����������У��ӹ�����������big���ظ�ǰ
//��Ĺ��̣������ҵ��ڶ�����Ϊ9������{4,5}��

//�������������
void PrintContinuousSequence(int small,int big)
{
	for(int i = small;i <= big;i++)
	{
		printf("%d ",i);
	}
	printf("\n");
}

//��������������ʹ�ú�Ϊnum
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
			//����ʹ���num����CurNum-=small��small++��
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
		cout<<"û���ҵ�!"<<endl;
	}*/

	FindContinuousSequence(20);
	
	system("pause");
	return 0;
}