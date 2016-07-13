#include<iostream>
using namespace std;

void PrintMatrixInCircle(int numbers[][4],int columns,int rows,int start)//打印一圈
{
	int endX = columns - 1 - start;
	int endY = rows - 1- start;
	//从左向右打印出来
	for(int i = start;i <= endX;++i)
	{
		printf("%d ",numbers[start][i]);
	}

	//从上往下打印
	if(start < endY)
	{
		for(int i = start + 1;i <= endY;++i)
		{
			printf("%d ",numbers[i][endX]);
		}
	}

	//从右往左打印
	if(start < endX && start < endY)
	{
		for (int i = endX - 1; i >= start; --i)
		{
			printf("%d ",numbers[endY][i]);
		}
	}

	//从下往上打印
	if(start < endX - 1 && start < endY)
	{
		for (int i = endY - 1; i > start;--i)
		{
			printf("%d ",numbers[i][start]);
		}
	}
}

//输入一个矩阵，顺时针打印该矩阵，每次打印一圈
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