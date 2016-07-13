#include<iostream>
using namespace std;

void PrintMatrixInCircle(int numbers[][4],int columns,int rows,int start)//��ӡһȦ
{
	int endX = columns - 1 - start;
	int endY = rows - 1- start;
	//�������Ҵ�ӡ����
	for(int i = start;i <= endX;++i)
	{
		printf("%d ",numbers[start][i]);
	}

	//�������´�ӡ
	if(start < endY)
	{
		for(int i = start + 1;i <= endY;++i)
		{
			printf("%d ",numbers[i][endX]);
		}
	}

	//���������ӡ
	if(start < endX && start < endY)
	{
		for (int i = endX - 1; i >= start; --i)
		{
			printf("%d ",numbers[endY][i]);
		}
	}

	//�������ϴ�ӡ
	if(start < endX - 1 && start < endY)
	{
		for (int i = endY - 1; i > start;--i)
		{
			printf("%d ",numbers[i][start]);
		}
	}
}

//����һ������˳ʱ���ӡ�þ���ÿ�δ�ӡһȦ
void printmatrixclockwisely(int numbers[][4],int columns,int rows)
{
	if(numbers == NULL || columns < 0 || rows < 0)
		return;
	int start = 0;
	while (start * 2 < columns && start * 2 < rows)
	{
		PrintMatrixInCircle(numbers,columns,rows,start);
		++start;
	}
	cout<<endl;
}

int main()
{
	int numbers[][4] = {{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16}};
	//int numbers[][1] = {1,2,3,4,5};
	printmatrixclockwisely(numbers,4,4);
	system("pause");
	return 0;
}