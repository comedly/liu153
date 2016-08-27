#include<iostream>
using namespace std;


//���ַ���ת��Ϊ����

enum Status
{
	kValid = 0,
	kInvalid
};

int g_nStatus = kValid;

long long StrToIntCore(const char* digit,bool minus)
{
	long long num = 0;

	while (*digit != '\0')
	{
		if(*digit >= '0' && *digit <= '9')
		{
			int flag = minus ? -1:1;
			num = num * 10 + flag * (*digit - '0');

			if((!minus && num > 0x7FFFFFFF) || (minus && num < (signed int)0x80000000))//����������ʾ��Χ�ģ�����0
			{
				num = 0;
				break;
			}
			digit++;
		}
		else//�������֣����������ַ����򷵻�0
		{
			num = 0;
			break;
		}
	}

	if(*digit == '\0')
	{
		g_nStatus = kValid;
	}
	return num;
}

int StrToInt(const char* str)
{
	g_nStatus = kInvalid;
	long long num = 0;

	if(str != NULL && *str != '\0')
	{
		bool minus = false;//minusΪtrue��ʾ����

		if(*str == '+')
			str++;
		else if(*str == '-')
		{
			str++;
			minus = true;
		}

		if(*str != '\0')
		{
			num = StrToIntCore(str,minus);
		}
	}

	return (int)num;
}

int main()
{
	cout<<StrToInt("-12342432554632453256")<<endl;
	cout<<StrToInt("-1234243")<<endl;
	cout<<StrToInt("-123adsa")<<endl;

	system("pause");
	return 0;
}