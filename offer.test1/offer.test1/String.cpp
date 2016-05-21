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

	MyString& operator=(const MyString& str)//赋值函数
	{
		if(this != &str)
		{
			MyString temp(str);    //创建一个临时变量，接着把temp._str和实例自身的_str做交换，由于temp是一个局部变量，出了作用域，会调用temp的析构函数，把temp._str指向的内存释放掉，由于temp._str指向的内存就是实例之前_str指向的内存，这就相当于自动调用析构函数释放实例的内存
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