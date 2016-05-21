#include<iostream>
using namespace std;

class MyString
{
public:
	MyString(char* str = " ")
		:_str(new char[strlen(str) + 1])
	{
		strcpy(_str,str);
	}

	MyString(const MyString& str)
		:_str(NULL)
	{
		MyString temp(str._str);
		swap(_str,temp._str);
	}

	MyString& operator=(const MyString& str)//��ֵ����
	{
		if(this != &str)
		{
			MyString temp(str);    //����һ����ʱ���������Ű�temp._str��ʵ�������_str������������temp��һ���ֲ����������������򣬻����temp��������������temp._strָ����ڴ��ͷŵ�������temp._strָ����ڴ����ʵ��֮ǰ_strָ����ڴ棬����൱���Զ��������������ͷ�ʵ�����ڴ�
			swap(_str,temp._str);
		}
		return *this;
	}

	~MyString()
	{
		if(_str != NULL)
		{
			delete[] _str;
		}
	}
private:
	char* _str; 
};


int main()
{
	MyString str1("abcdefg");
	MyString str2(str1);
	MyString str3 = str1;
	system("pause");
	return 0;
}