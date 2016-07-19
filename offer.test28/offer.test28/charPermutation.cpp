#include<iostream>
#include<assert.h>
using namespace std;

//输入一个字符串，打印出该字符串中所有字符的排列

void Permutation(char* pStr,char* pBegin)
{
	if(*pBegin == '\0')
	{
		printf("%s\n",pStr);
	}
	else
	{
		for(char* pCh = pBegin;*pCh != '\0';++pCh)
		{
			char temp = *pCh;
			*pCh = *pBegin;
			*pBegin = temp;

			Permutation(pStr,pBegin+1);
			
			temp = *pCh;
			*pCh = *pBegin;
			*pBegin = temp;
		}
	}
}

void Permutation(char* pStr)
{
	if(pStr == NULL)
		return;
	Permutation(pStr,pStr);
}

void charPermutation(char* pStr,char* pBegin)
{
	assert(pStr && pBegin);
	if(*pBegin == '\0')
	{
		printf("%s\n",pStr);
	}
	else
	{
		for(char* pCh = pBegin;*pCh != '\0';pCh++)
		{
			swap(*pBegin,*pCh);
			charPermutation(pStr,pBegin+1);
			swap(*pBegin,*pCh);
		}
	}
}


int main()
{
	char str[] = "abc";
	//Permutation(str);
	charPermutation(str,str);
	printf("%s,%5.3s\n","computer","computer");
	system("pause");
	return 0;
}