#pragma once

//��ֵ������
//��base��exponent�η�

bool equal(double num1,double num2)//����һ���Ƚ�����ֵ�Ƿ���ȵĺ���,����ֱ����==�Ƚ�
{
	if((num1 - num2 > -0.0000001) && (num1 - num2 < 0.0000001))
	{
		return true;
	}
	return false;
}

double PowerWithUnsignedExponent1(double base,unsigned int exponent)//�������޷��ŵ�����,��򵥵�������ĳһ�����Ĵη���ѭ�������γ˷�
{
	double result = 1.0;
	for(int i = 1;i <= exponent;i++)
	{
		result *= base;
	}
	return result;
}

//����ѭ������������
double PowerWithUnsignedExponent2(double base,unsigned int exponent)
{
	if(exponent == 0)
	{
		return 1;
	}
	if(exponent == 1)
	{
		return base;
	}
	double result = PowerWithUnsignedExponent2(base,exponent>>1);
	result *= result;
	if(exponent && 0x1 == 1)
	{
		result *= base;
	}
	return result;
}

bool invalidInput = false;
double Power(double base,int exponent)
{
	invalidInput = false;
	if(equal(base,0.0) && exponent < 0)//���base����0.0�Ҵ���Ϊ�������򽫶�0���������ʹ�������
	{
		invalidInput = true;
		return 0.0;
	}
	unsigned int absExponent = (unsigned int)exponent;
	if(exponent < 0)
	{
		absExponent = (unsigned int)(-exponent);
	}
	double result = PowerWithUnsignedExponent1(base,absExponent);
	//double result = PowerWithUnsignedExponent2(base,absExponent);
	if(exponent < 0)
	{
		result = 1.0/result;
	}
	return result;
}

