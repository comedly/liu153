#include<iostream>
using namespace std;


//length为字符数组String的总容量
void ReplaceBlank(char String[],int length)
{
	if(String == NULL || length <= 0)
		return;
	int OriginalLength = 0;//记录String的实际长度
	int NumberOfBlank = 0;//记录字符串中的空格数
	int i = 0;
	while(String[i] != '\0')//遍历字符串统计空格的个数
	{
		++OriginalLength;
		if(String[i] == ' ')
			++NumberOfBlank;
		++i;
	}
	//NewLength记录把空格换成%20后字符串的长度
	int NewLength = OriginalLength + 2*NumberOfBlank;
	if(NewLength > length)
		return;
	int indexOfOriginal = OriginalLength;//记录原始字符串的下标
	int indexOfNew = NewLength;//记录替换后的字符串的下标
	while (indexOfOriginal >= 0 && indexOfNew > indexOfOriginal)//从后向前复制，遇到空格转换为%20
	{
		if(String[indexOfOriginal] == ' ')
		{
			String[indexOfNew--] = '0';
			String[indexOfNew--] = '2';
			String[indexOfNew--] = '%';
		}
		else
		{
			String[indexOfNew--] = String[indexOfOriginal];
		}
		--indexOfOriginal;
	}
}

int main()
{
	char Array[50] = "we are happy.";
	ReplaceBlank(Array,50);
	cout<<Array<<endl;
	system("pause");
	return 0;
}
