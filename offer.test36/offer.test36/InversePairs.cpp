#include<iostream>
#include<assert.h>
using namespace std;

//求一个数组的逆序对
//如7 5 6 4 //逆序对：（7，5）（7,6）（7,4）（6,4）（5,4）5对
//将他分成两个数组，第一个数组存前半部分，第二个存后半部分，两个数组排序，
//p1指向第一个的最后一个位置，p2指向第二个的最后一个位置，再新开辟一块辅助
//数组，p3指向辅助数组的最后一个，如果p1指向的数大于p2指向的数，则count+第
//二个数组的个数，并把该数拷给辅助数组的最后一个，p3前移吗，否则，p2前移，
//再用p1指向的数组继续与p2指向的数比较，以此类推。

void BubbleSort(int* a,int size)
{
	assert(a);
	assert(size>0);
	for(int i = 0;i < size;i++)
	{
		for(int j = 0;j < size - i - 1;j++)
		{
			if(a[j] > a[j+1])
			{
				swap(a[j],a[j+1]);
			}
		}
	}
}

int InversePairsCore(int* data,int* copy,int start,int end)//求数组的逆序对的个数
{
	if(start == end)
	{
		copy[start] = data[start];
		return 0;
	}

	int length = (end - start)/2;

	int left = InversePairsCore(copy,data,start,start+length);
	int right = InversePairsCore(copy,data,start+length+1,end);
	
	int i = start + length;//指向第一部分的最后一个元素的下标
	int j = end;//指向第二部分的最后一个元素的下标
	int indexcopy = end;
	int count = 0;
	while (i >= start && j >= start+length+1)
	{
		//BubbleSort(data,i+1);
		//BubbleSort(data+length+1,j-i+1);
		if(data[i] > data[j])
		{
			copy[indexcopy--] = data[i--];
			count += j - length -start;
		}
		else
		{
			copy[indexcopy--] = data[j--];
		}
	}

	for(;i >= start;i--)
	{
		copy[indexcopy--] = data[i];
	}
	for(;j >= start+length+1;j--)
		copy[indexcopy--] = data[j];

	return count + left + right;
}

int InversePairs(int data[],int length)
{
	if(data == NULL || length < 0)
		return 0;

	int* copy = new int[length];
	for(int i = 0;i < length;i++)
	{
		copy[i] = data[i];
	}
	int count = InversePairsCore(data,copy,0,length-1);

	delete[] copy;
	return count;
}

int main()
{
	int a[] = { 7, 5, 6, 4};
	cout<<InversePairs(a,sizeof(a)/sizeof(a[0]))<<endl;
	system("pause");
	return 0;
}
