#include <iostream>
using namespace std;

//字符串是回文，返回true，否，返回false

bool Huiwen(char*s)
{
	char *p=s,*q=s;
	char *L=0; //指向结束符号的前一个位置
	int len=0; //记录字串串的字符个数
	while (*(p+1) != '\0')
	{
		p++;
		len++;
	}
	L=p;//L指向结束符号的前一个位置
	while (*q==' ') //开头的空格跳过去
	{
		q++; //每移动一步，len的长度减1
		len--;
	}
	while ((*q==*L || abs(*q-*L)==32) && len>=0 ) //当前后两个字符相等或是一个是大写一个是小写，且未遍历完时，接着遍历
	{  
		q++;
		len--;
		L--;
		len--;
		while(*q==' ')
		{
			q++;
			len--;
		}
		while (*L==' ')
		{
			L--;
			len--;
		}
	}
	if (len<0) //如果字符串遍历完了，说明是回文
		return true;
	else
		return false;
}

int main(){
	char a[]="A man a plan a canal panama";
	if (Huiwen(a))
		cout<<"this is huiwen\n";
	else
		cout<<"this is not huiwen\n";
	system("pause");
	return 0;
}