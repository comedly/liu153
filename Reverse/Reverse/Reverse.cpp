#include<iostream>
using namespace std;

//����һ��Ӣ�ľ��ӣ���ת�����е��ʵ�˳�򣬵������ڵ��ַ���
//˳�򲻱䣬���磺���롰I am a student.���������student. a am I����

//��ת�ַ����е�һ��
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

//�ȷ�ת�������ӣ��ڷ�ת�����е�ÿһ������
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

	//��ת��������
	Reverse(begin,end);

	//��ת�����е�ÿһ������
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

//�ַ���������ת���ǰ��ַ���ǰ������ɸ��ַ�ת�Ƶ��ַ�����
//β�����磺�����ַ�����abcdefgh��������2��������2λ��
//����cdefghab��

//��������ǰ�����ַ�����һ���֣���ߵ��ַ�����һ���֣�����
//�ȷֱ�ת���������֣����ǵõ���bahgfedc�����ӹ�����ת��
//���ַ������õ���ת����ַ�������Ҫ����3��Reverse��������

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

			//��תǰn���ַ�
			Reverse(pFirstStart,pFirstEnd);

			//��ת��n���ַ�
			Reverse(pSecondStart,pSecondEnd);

			//��ת�����ַ���
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