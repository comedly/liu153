#pragma once

#include<iostream>
using namespace std;

//��������1�ĸ���
//����������ѭ���Ľⷨ
//�������һ����������Ϊ���λ�ķ���λ��1����λ�Ĺ���������Ҫ��֤�����Ǹ��������һֱ���������㣬�ͻ�������ѭ��
int NumberOf1_1(int n)
{
	int count = 0;
	while (n)
	{
		if(n & 1)//������ұ�һλ��1�����㣬���Ϊ1��count++;
		{
			count++;
		}
		n = n >> 1;//����һλ
	}
	return count;
}

//������ѭ����д��
//�˴����ƶ�����n�����Ȱ�n��1�������㣬�ж�n�����λ�ǲ���1�����Ű�1������λ��������������......
int NumberOf1_2(int n)
{
	int count = 0;
	unsigned int flags = 1;
	while (flags)
	{
		//�˴�ѭ���Ĵ������ڶ����Ƶ�λ����32λ��Ҫѭ��32��
		if(n & flags)
		{
			count++;
		}
		flags = flags << 1;
	}
	return count;
}

//һ�������������м���1��ֻ��Ҫѭ������
//��������һ��������ȥ1���ٺ�ԭ���������������㣬���൱�ڰ�ԭ�����������ұߵ��Ǹ�1�ó�0����ôһ�����������ж��ٸ�1��ѭ�����ٴ�
int NumberOf1_3(int n)
{
	int count = 0;
	while (n)
	{
		count++;
		n = n & (n - 1);
	}
	return count;
}

void Test()
{
	int n = NumberOf1_1(10);
	cout<<n<<endl;
	n = NumberOf1_2(-10);
	cout<<n<<endl;
	n = NumberOf1_3(0);
	cout<<n<<endl;
}