#pragma once 

//二维数组的查找
//每一行从左向右递增，每一列从上向下递增
//1  2  8  9
//2  4  9  12
//4  7  10 13
//6  8  11 15
//若在数组中查找7，则返回true，若在数组中查找5，返回false

bool Find(int* Array,int rows,int columns,int number)
{
	bool found = false;//记录返回值
	if(Array != NULL && rows > 0 && columns > 0)
	{
		//从右上角的元素开始，等于要查找的元素返回true，数组的元素无论是行还是列都是递增的，最后一列的第一个元素是该列中最小的，大于要查找的元素时，剔除掉该列，column--，再从右上角开始，如果右上角的元素小于要查找的元素时，因为每一行的最后一个元素是最大的，所以row++；以此类推，直到找到为止。
		int row = 0;
		int column = columns - 1;
		while (row < rows && column >= 0)
		{
			if(Array[row*columns + column] == number)
			{
				found = true;
				break;
			}
			else if(Array[row*columns + column] > number)
			{
				--column;
			}
			else
			{
				++row;
			}
		}
	}
	return found;
}
