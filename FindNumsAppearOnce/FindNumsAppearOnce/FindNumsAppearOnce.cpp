#include<iostream>
using namespace std;

//一个整形数组里除了两个数字之外，其他的数字都出现了两次，找出这两个数字。

//判断在num的二进制表示中找到最右边是1的位
unsigned int FindFirstBitIs1(int num)
{
	int indexBit = 0;
	while(((num & 1) == 0) && (indexBit < 8 * sizeof(int)))
	{
		num = num>>1;
		++indexBit;
	}

	return indexBit;
} 

//判断在num的二进制表示中从右边起的indexBit位是不是1.
bool IsBit1(int num,unsigned int indexBit)
{
	num = num >> indexBit;
	return (num & 1);
}

void FindNumsAppearOnce(int data[],int length,int* num1,int* num2)
{
	if(data == NULL || length == 2)
		return;

	int resultExclusiveOR = 0;

	for (int i = 0; i < length; ++i)
		resultExclusiveOR ^= data[i];

	unsigned int indexOf1 = FindFirstBitIs1(resultExclusiveOR);

	*num1 = *num2 = 0;
	for(int j = 0;j < length;++j)
	{
		if(IsBit1(data[j],indexOf1))
			*num1 ^= data[j];
		else
		{
			*num2 ^= data[j];
		}
	}

}

int main()
{
	int array[] = {2,4,3,6,3,2,5,5};
	int num1,num2;
	int length = sizeof(array)/sizeof(array[0]);
	FindNumsAppearOnce(array,length,&num1,&num2);

	cout<<num1<<endl;
	cout<<num2<<endl;

	system("pause");
	return 0;
}