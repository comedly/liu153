#include<iostream>
using namespace std;

//输入一个英文句子，翻转句子中单词的顺序，但单词内的字符的
//顺序不变，例如：输入“I am a student.”则输出“student. a am I”。

//翻转字符串中的一段
void Reverse(char* begin,char* end)
{
	if(begin == NULL || end == NULL)
		return ;

	while(begin < end)
	{
		char temp = *begin;
		*begin = *end;
		*end = temp;
		begin++;
		end--;
	}
}

//先翻转整个句子，在翻转句子中的每一个单词
char* ReverseSentence(char* pData)
{
	if(pData == NULL)
		return NULL;

	char* begin = pData;
	char* end = pData;

	while (*end != '\0')
	{
		end++;
	}
	end--;

	//翻转整个句子
	Reverse(begin,end);

	//翻转句子中的每一个单词
	begin = end = pData;
	while (*begin != '\0')
	{
		if(*begin == ' ')
		{
			begin++;
			end++;
		}
		else if(*end == ' ' || *end == '\0')
		{
			Reverse(begin,--end);
			begin = ++end;
		}
		else
		{
			end++;
		}
	}
	return pData;
}

//字符串的左旋转，是把字符串前面的若干个字符转移到字符串的
//尾部，如：输入字符串“abcdefgh”和数字2，及左旋2位得
//到“cdefghab”

//方法：把前两个字符看做一部分，后边的字符看做一部分，我们
//先分别翻转这两个部分，于是得到“bahgfedc”，接哈来旋转整
//个字符串，得到旋转后的字符串，需要调用3次Reverse函数即可

char* LeftRotateString(char* pStr,int n)
{
	if(pStr != NULL)
	{
		int nLength = static_cast<int>(strlen(pStr));

		if(nLength > 0 && n > 0 && n < nLength)
		{
			char* pFirstStart = pStr;
			char* pFirstEnd = pStr + n -1;
			char* pSecondStart = pStr + n;
			char* pSecondEnd = pStr + nLength - 1;

			//翻转前n个字符
			Reverse(pFirstStart,pFirstEnd);

			//翻转后n个字符
			Reverse(pSecondStart,pSecondEnd);

			//翻转整个字符串
			Reverse(pFirstStart,pSecondEnd);
		}
	}
	return pStr;
}

int main()
{
	char str[] = "I am a student.";
	cout<<str<<endl;
	char* dest = ReverseSentence(str);
	cout<<dest<<endl;

	char rotratestr1[] = "abcdefgh";
	char rotratestr2[] = "";

	dest = LeftRotateString(rotratestr1,3);
	dest = LeftRotateString(rotratestr2,3);

	cout<<dest<<endl;
	system("pause");
	return 0;
}