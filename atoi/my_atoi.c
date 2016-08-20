/***************************************************************************	
	>file name:my_atoi.c
	>author:Comedly
	>create time:2016-8-20
***************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//将字符串转换为整数
int my_atoi(char *pstr)
{
	int Ret_Integer = 0;
	int Integer_sign = 1;

	//判断指针是否为空
	if(pstr == NULL)
	{
		printf("Pointer is NULL\n");
		return 0;
	}

	//越过前面的空格字符串
	while(isspace(*pstr) != 0)
	{
		pstr++;
	}

	//判断正负号
	//如果时负号，把符号标记Integer_sign置-1，然后再把指针指向下一个字符
	//如果是正号，指针指向下一个字符
	if(*pstr == '-')
	{
		Integer_sign = -1;
	}
	if(*pstr == '+' || *pstr == '-')
	{
		pstr++;
	}

	//将数字字符串逐个转换为整数,并把最后转换好的整数赋给Ret_Integer
	while(*pstr >= '0' && *pstr <= '9')
	{
		Ret_Integer = Ret_Integer*10 + *pstr - '0';
		pstr++;
	}
	Ret_Integer = Integer_sign * Ret_Integer;
	return Ret_Integer;
}

//将整数n转换成对应的字符串
static int i = 0;//定义全局变量i，作为s的下标
void my_itoa(int n,char s[])
{
	if(n < 10)
	{
		s[i] = n + '0';
	}
	else
	{
		my_itoa(n/10,s);
		i++;
		n = n%10;//最后一位的数字
		s[i] = n + '0';
	}
	s[i+1] = '\0';//字符串结束标志
}

//将整数n转换为b进制的数，保存在s中
void my_itob(int n,char s[],int b)
{
	if(n < 2)
	{
		s[i] = n + '0';
	}
	else
	{
		my_itob(n/2,s,b);
		i++;
		n = n%2;
		s[i] = n+'0';
	}
	s[i+1] = '\0';
}

int main()
{
//	char p[] = "-1234";
//	printf("%d\n",my_atoi(p));
	
	char s[6];
//	my_itoa(13334,s);
//	printf("%s\n",s);

	my_itob(15,s,2);
	printf("%s\n",s);
	return 0;
}
