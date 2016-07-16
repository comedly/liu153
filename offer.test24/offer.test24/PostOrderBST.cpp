#include<iostream>
using namespace std;

//�ж�һ�������Ƿ�Ϊ�����������ĺ����������
bool verifySequenceOfBST(int sequence[],int length)
{
	if(sequence == NULL || length <= 0)
		return false;
	int root = sequence[length - 1];//���һ��Ԫ��Ϊ���ڵ�
	int i = 0;
	for(i = 0;i < length - 1;i++)
	{
		//С�ڸ��ڵ��ֵΪ������
		if(sequence[i] > root)
			break;
	}
	int j = i;
	for(;j < length - 1;j++)
	{
		//������Ӧ�ö����ڸ��ڵ�
		if(sequence[j] < root)
			return false;
	}

	bool left = true;//�ݹ�ʵ��������
	if(i > 0)
	{
		left = verifySequenceOfBST(sequence,i);
	}
	bool right = true;//�ݹ�ʵ��������
	if(j < length - 1)
	{
		right = verifySequenceOfBST(sequence + i,length - i - 1);
	}
	return left && right;
}

//�ж�һ�������Ƿ�Ϊ�����������ĺ����������
bool PrevSequenceOfBST(int sequence[] ,int length)
{
	if(sequence == NULL || length <= 0)
		return false;
	int root = sequence[0];//��һ���ڵ�Ϊ���ڵ�
	int i = 1;
	for(;i < length;i++)//��rootС�Ķ�Ϊ������
	{
		if(sequence[i] > root)
			break;
	}
	int j = i;
	for(;j < length;j++)//��root�����������
	{
		if(sequence[j] < root)
			return false;
	}

	bool left = true;//�ݹ����������
	if(i > 1)
	{
		left = PrevSequenceOfBST(sequence + 1,i);
	}
	bool right = true;//�ݹ����������
	if(j < length)
	{
		right = PrevSequenceOfBST(sequence + i,length - i);
	}
	return (left && right);
}

int main()
{
	int a[] = {5,7,6,9,11,10,8};
	int b[] = {8,6,5,7,10,9,11};
	cout<<"����a�Ƿ�Ϊ�����������ĺ���������У�"<<verifySequenceOfBST(a,sizeof(a)/sizeof(a[0]))<<endl;
	cout<<"����b�Ƿ�Ϊ������������ǰ��������У�"<<PrevSequenceOfBST(b,sizeof(b)/sizeof(b[0]))<<endl;
	system("pause");
	return 0;
}