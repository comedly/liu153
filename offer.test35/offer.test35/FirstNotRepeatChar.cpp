#include<iostream>
using namespace std;

//第一个只出现一次的字符
//利用哈希表实现
char FirstNotRepeatChar(char* pString)
{
	if(pString == NULL)
		return '\0';

	const int HashSize = 256;
	unsigned int hashTable[HashSize];
	for(unsigned int i = 0;i < 256;i++)
	{
		hashTable[i] = 0;
	}

	char* pHashKey = pString;
	while (*(pHashKey) != '\0')
	{
		hashTable[*(pHashKey)]++;
		pHashKey++;
	}

	pHashKey = pString;
	while (*pHashKey != '\0')
	{
		if(hashTable[*pHashKey] == 1)
			return *pHashKey;
		pHashKey++;
	}
	return '\0';
}

int main()
{
	char* a ="dbaeccbdeff";
	cout<<FirstNotRepeatChar(a)<<endl;
	system("pause");
	return 0;
}