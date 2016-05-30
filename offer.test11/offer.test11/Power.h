#pragma once

//数值的整数
//求base的exponent次方

bool equal(double num1,double num2)//定义一个比较两个值是否相等的函数,不能直接用==比较
{
	if((num1 - num2 > -0.0000001) && (num1 - num2 < 0.0000001))
	{
		return true;
	}
	return false;
}

double PowerWithUnsignedExponent1(double base,unsigned int exponent)//次数是无符号的整形,最简单的做法是某一个数的次方就循环做几次乘法
{
	double result = 1.0;
	for(int i = 1;i <= exponent;i++)
	{
		result *= base;
	}
	return result;
}

//减少循环次数的做法
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
	if(equal(base,0.0) && exponent < 0)//如果base等于0.0且次数为负数，则将对0求倒数，则会使程序崩溃
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

