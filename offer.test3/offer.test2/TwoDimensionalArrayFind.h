#pragma once 

//��ά����Ĳ���
//ÿһ�д������ҵ�����ÿһ�д������µ���
//1  2  8  9
//2  4  9  12
//4  7  10 13
//6  8  11 15
//���������в���7���򷵻�true�����������в���5������false

bool Find(int* Array,int rows,int columns,int number)
{
	bool found = false;//��¼����ֵ
	if(Array != NULL && rows > 0 && columns > 0)
	{
		//�����Ͻǵ�Ԫ�ؿ�ʼ������Ҫ���ҵ�Ԫ�ط���true�������Ԫ���������л����ж��ǵ����ģ����һ�еĵ�һ��Ԫ���Ǹ�������С�ģ�����Ҫ���ҵ�Ԫ��ʱ���޳������У�column--���ٴ����Ͻǿ�ʼ��������Ͻǵ�Ԫ��С��Ҫ���ҵ�Ԫ��ʱ����Ϊÿһ�е����һ��Ԫ�������ģ�����row++���Դ����ƣ�ֱ���ҵ�Ϊֹ��
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
