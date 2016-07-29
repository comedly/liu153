#include<iostream>
#include<assert.h>
using namespace std;

//��һ������������
//��7 5 6 4 //����ԣ���7��5����7,6����7,4����6,4����5,4��5��
//�����ֳ��������飬��һ�������ǰ�벿�֣��ڶ������벿�֣�������������
//p1ָ���һ�������һ��λ�ã�p2ָ��ڶ��������һ��λ�ã����¿���һ�鸨��
//���飬p3ָ������������һ�������p1ָ���������p2ָ���������count+��
//��������ĸ��������Ѹ�������������������һ����p3ǰ���𣬷���p2ǰ�ƣ�
//����p1ָ������������p2ָ������Ƚϣ��Դ����ơ�

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

int InversePairsCore(int* data,int* copy,int start,int end)//�����������Եĸ���
{
	if(start == end)
	{
		copy[start] = data[start];
		return 0;
	}

	int length = (end - start)/2;

	int left = InversePairsCore(copy,data,start,start+length);
	int right = InversePairsCore(copy,data,start+length+1,end);
	
	int i = start + length;//ָ���һ���ֵ����һ��Ԫ�ص��±�
	int j = end;//ָ��ڶ����ֵ����һ��Ԫ�ص��±�
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
