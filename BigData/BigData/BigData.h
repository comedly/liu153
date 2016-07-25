#ifndef __BIGDATA_H__
#define __BIGDATA_H__

#include<iostream>
using namespace std;
//大数的处理需要借助字符串来实现
#include<string.h>
#include<assert.h>

#define UN_INT 0xCCCCCCCCCCCCCCCC
#define MAX_INT64 0x7FFFFFFFFFFFFFFF
#define MIN_INT64 0x8000000000000000
typedef long long INT64;

class  BigData
{
public:
	BigData(INT64 value = UN_INT)//构造函数
		:_value(value)
	 {
		 INT64ToString();
	 }

	BigData(const char* ptr)//字符串构造函数
	{
		if(NULL == ptr)//检查传入的字符串是否为空
			return;
		char* src = (char*)ptr;
		char cSymbol = ptr[0];//记录符号位
		if(cSymbol == '+' || cSymbol == '-')//传入的字符串首字符为+/-
		{
			src++;
		}
		else if(cSymbol >= '0' && cSymbol <= '9')//传入的字符直接为数字，不是+/-
		{
			cSymbol = '+';
		}
		else
		{
			return;
		}
		while ('0' == *src)//防止000012345这种情况的出现，可以直接把0跳过
		{
			src++;
		}
		_strData.resize(strlen(ptr)+1);//_strData大小，调用string类中resize()方法
		_strData[0] = cSymbol;//留第一个空间作为符号位
		_value = 0;//保存字符串转换后的数据
		int count = 1;
		while (*src >= '0' && *src <= '9')//拷贝字符串
		{
			_value = _value * 10 + (*src - '0');
			_strData[count++] = *src;
			src++;
		}
		_strData.resize(count);//重新调整大小
		if(cSymbol == '-')
		{
			_value =(-1) * _value;
		}
	}

	//加法
	BigData operator+(const BigData& bigData)//+运算符重载，(采用传值的方式，传引用会更改this)考虑是否溢出
	{
		//两个操作数都没有溢出
		if(IsINT64OverFlow() && bigData.IsINT64OverFlow())
		{
			//若两个操作数异号，不会出现溢出
			if(_strData[0] != bigData._strData[0])
			{
				return BigData(_value + bigData._value);//调用构造函数
			}
			//若两个操作数同号，结果有可能溢出
			//同为+： 假设最大值为10 ，_value:5  bigdata._value:4 则10-5>4,相加不会溢出，若_value:7 则10-7<4,相加会产生溢出
			//同为-：若用在此范围的最小值(-10) - _value(-4)的值小于等于bigdata._value(-5)的值，则不会溢出，反之溢出
			else if((_value >= 0 && MAX_INT64 - _value >= bigData._value) || (_value <= 0 && MIN_INT64 - _value <= bigData._value))
			{
				return BigData(_value + bigData._value);
			}
		}
		//两个操作数至少有一个溢出
		return BigData(Add(_strData,bigData._strData).c_str());
	}

	BigData operator-(const BigData& bigData)//运算符-重载
	{
		if(IsINT64OverFlow() && bigData.IsINT64OverFlow()) //两个操作数都没有溢出
		{
			//若同号
			if(_strData[0] == bigData._strData[0]) 
			{
				return BigData(_value - bigData._value);//调用构造函数
			}
			else
			{
				//若两个操作数异号
				//若范围中的最大值10，_value:6,bigData._value:-7   （-10）+ 6 > -7 结果溢出
				//若范围中的最大值-10，_value:-6,bigData._value:7   10 + （-6）< 7 结果溢出
				if((_value >= 0 && MIN_INT64 + _value <= bigData._value) ||(_value <= 0 && MAX_INT64 + _value >= bigData._value))
				{
					return BigData(_value - bigData._value);
				}
			}
		}
		else
		{
			if(_strData[0] != bigData._strData[0])//异号
			{
				return BigData(Add(_strData,bigData._strData).c_str());
			}
			else
			{
				return BigData(Sub(_strData,bigData._strData).c_str());
			}
		}
	}

	BigData operator*(const BigData& bigData)//运算符*重载
	{
		if(_value == 0 || bigData._value == 0)
		{
			return BigData(INT64(0));
		}
		if(IsINT64OverFlow() && bigData.IsINT64OverFlow())//两个数据都没有溢出
		{
			//同号
			//假设此范围的最大值为10，给出两个正数2 6；则10/2 = 5 < 6,则会溢出
			//给出两个负数 -2 -6,10/(-2) = -5 > -6一样会溢出
			if(_strData[0] == bigData._strData[0])
			{
				if((_value > 0 && MAX_INT64 / _value >= bigData._value)
					||(_value < 0 && MAX_INT64 / _value <= bigData._value))
				{
					return BigData(_value * bigData._value);
				}
			}
			else
			{
				//给两个数据2 -6 若10/2 = 5 < -(-6)溢出，若为-4的话就不会溢出
				//给两个数据-2 6 若10/-2 = -5 > -6 溢出，若为4的话就不会溢出
				if((_value > 0 && MAX_INT64 / _value >= -bigData._value)
					|| (_value < 0 && MAX_INT64 / _value <= -bigData._value))
				{
					return _value * bigData._value;
				}
			}
		}
		return BigData(Mul(_strData,bigData._strData).c_str());
	}

	//除法 除数不为0 无溢出直接除
	//若left < right，则结果随机值
	//right == +1(-1) 
	//left = right 则结果为+1（-1）
	BigData operator/(const BigData& bigData)//运算符、重载
	{
		if(0 == bigData._value)//检查除数是否为0
		{
			assert(false);
			return BigData(INT64(0));
		}
		if(IsINT64OverFlow() && bigData.IsINT64OverFlow())//两个数据都不溢出
		{
			return BigData(_value / bigData._value);
		}
		//left < right
		if(_strData.size() < bigData._strData.size() 
			|| (_strData.size() == bigData._strData.size() 
			&& strcmp(_strData.c_str(),bigData._strData.c_str()) < 0))
		{
			return BigData(INT64(0));
		}
		//除数为1或-1
		if(bigData._strData.compare("+1") == 0 || bigData._strData.compare("-1") == 0)
		{
			string ret = _strData;
			if(_strData[0] != bigData._strData[0])
			{
				ret[0] = '-';
			}
			else
			{
				ret[0] = '+';
			}
			return BigData(ret.c_str());
		}
		//left == right
		if(strcmp(_strData.c_str() + 1,bigData._strData.c_str() + 1) == 0)
		{
			string temp = "+1";
			if(_strData[0] != bigData._strData[0])
			{
				temp = "-1";
			}
			return BigData(temp.c_str());
		}
		return BigData(Div(_strData,bigData._strData).c_str());
	}

	friend ostream& operator<< (ostream& os,const BigData& bigdata)//输出运算符重载
	{
		if(bigdata.IsINT64OverFlow())//无溢出情况
		{
			os<<bigdata._value<<endl;
		}
		else
		{
			char* ptr = (char*)bigdata._strData.c_str();
			//c_str是以const char*类型返回string中的字符串，因此需要进行强制类型转换
			if(ptr[0] == '+')
			{
				ptr++;
			}
			os<<ptr<<endl;
		}
		return os;
	}

	~ BigData()
	{
	}

private:
	void INT64ToString()//将_value转换成字符串
	{
		char cSymbol = '+';//cSymbol记录大数的符号位
		if(_value < 0)
		{
			cSymbol = '-';
		}
		_strData.append(1,cSymbol);//考虑符号位，附加一位字符cSymbol组成的字符串（实则为符号位）
		INT64 number = _value;
		while (number) //转换字符串，转换后的字符串与_value是相反的
		{
			int num = number % 10;
			if(number < 0)
			{
				num = 0 - num;
			}
			_strData.append(1,num + '0');
			number = number/10;
		}
		char* left = (char*)_strData.c_str()+1;//left指向一个跳过第一个字符符号位的位置
		char* right = left + _strData.size() - 2;//指向最后一个元素
		while (left < right)//字符串逆置，逆置后字符串表示的值与_value相等
		{
			char tmp = *left;
			*left = *right;
			*right = tmp;
			left++;
			right--;
		}
	}

	bool IsINT64OverFlow() const //const声明方法是静态的，声明最大值
	{
		string temp("+9223372036854775807");//string的对象temp实例化
		if('-' == _strData[0])
		{
			temp = "-9223372036854775807";
		}
		if(_strData.size() < temp.size())//无溢处，返回true
		{
			return true;
		}
		else if((_strData.size() == temp.size()) && _strData.compare(temp) < 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	string Add(string left,string right)//字符串相加，left与right是同号的
	{
		int LSize = left.size();//字符串的字节数
		int RSize = right.size();
		//将两个字符串变换为第一个字符串的字节数大于第二个的字节数，这样便于计算
		if(LSize < RSize)
		{
			swap(left,right);
			swap(LSize,RSize);		
		}
		string ret;//用来存放相加后的结构
		ret.resize(LSize+1);//resize的作用相当于开辟一块LSize+1个大小的空间
		ret[0] = left[0];//先将符号位进行拷贝
		char temp = 0;//保存进位
		for(int i = 1;i < LSize;i++)
		{
			int src = left[LSize - i] + temp - '0';
			if(i < RSize)//防止第二个数据会一直进行取字符操作，会越界
			{
				src += right[RSize - i] - '0';
			}
			ret[LSize - i +1] = src % 10 + '0';
			temp = src / 10;
		}
		ret[1] = temp + '0';
		return ret;
	}

	string Sub(string left,string right)//字符串相减
	{
		int LSize = left.size();
		int RSize = right.size();//字符串的字节数
		char cSymbol = left[0];
		if((left.compare(right) < 0 && LSize == RSize) || LSize < RSize)
		{
			swap(left,right);
			swap(LSize,RSize);
			if('+' == cSymbol)
			{
				cSymbol = '-';
			}
			else
			{
				cSymbol = '+';
			}
		}
		string ret;//存储相减后的结果
		ret.resize(left.size()+1);//开辟一块和left + 1一样大小的空间
		ret[0] = cSymbol;//第一位为符号位
		for(int i = 1;i < LSize;i++)
		{
			char src = left[LSize - i] - '0';
			if(i < RSize)
			{
				src -= right[RSize - i] - '0';
			}
			if(src < 0)//判断是否需要借位
			{
				left[LSize - i -1] -= 1;
				src += 10;
			}
			ret[LSize - i] = src + '0';
		}
		return ret;
	}

	string Mul(string left,string right)//字符串相乘
	{
		int LSize = left.size();
		int RSize = right.size();//记录字符串的字节数
		char cSymbol = '+';
		if(left[0] != right[0])
		{
			cSymbol = '-';
		}
		if(LSize > RSize)//将数字较小的作为第一个数据，能够提高循环效率
		{
			swap(left,right);
			swap(LSize,RSize);
		}
		string ret;
		ret.assign(LSize + RSize - 1,'0');//assign()申请LSize + RSize - 1个空间，并初始化为0
		int len = ret.size();//新字符串的长度
		int num = 0;//每一次向左边移动的位数
		ret[0] = cSymbol;//记录符号位
		for(int i = 1;i < LSize;i++)
		{
			char src = left[LSize - i] - '0';
			char dst = 0;//保存进位
			if(src == 0)
			{
				num++;
				continue;
			}
			for(int j = 1;j < RSize;j++)
			{
				char ptr = src * (right[RSize - j] - '0') + dst;
				ptr += ret[len - j - num] - '0';
				ret[len - j - num] = ptr % 10 + '0';
				dst = ptr /10;
			}
			ret[len - RSize - num] += dst;
			num++;
		}
		return ret;
	}

	string Div(string left,string right)//字符串相除
	{
		string ret;
		ret.resize(1,'+');
		if(left[0] != right[0])//确定商的符号
		{
			ret[0] = '-';
		}
		char *pLeft = (char*)(left.c_str()+1);
		char *pRight = (char*)(right.c_str()+1);
		int len = right.size() - 1; //因为有符号位
		for(int i = 0;i < left.size()-1;)
		{
			if(!(IsLeftString(pLeft,len,pRight,right.size() - 1)))
			{
				ret.append(1,'0');
				len++;
			}
			else
			{
				ret.append(1,loopmove(pLeft,len,pRight,right.size() - 1));
				while (*pLeft == '0' && len > 0)
				{
					pLeft++;
					i++;
					len--;
				}
				len++;
			}
			if(len > right.size())//pLeft比pRight大一位结果为0，则pLeft中含有0
			{
				pLeft++;
				len--;
				i++;
			}
			if(len + i > left.size() - 1)
			{
				break;
			}
		}
		return ret;
	}

	bool IsLeftString(const char* pleft,int Lsize,const char* pright,int Rsize)//判断被除数是否大于或小于除数
	{
		if(Lsize > Rsize || (Lsize == Rsize && strncmp(pleft,pright,Lsize) >= 0))
		{
			return true;
		}
		return false;
	}

	char loopmove(char* pleft,int Lsize,char* pright,int Rsize)
	{
		assert(pleft != NULL && pright != NULL);
		char pret = '0';
		while (1) //被除数 > 除数
		{
			if(!IsLeftString(pleft,Lsize,pright,Rsize))
			{
				break;
			}
			for(int i = 0;i < Rsize;i++)
			{
				char ret = pleft[Lsize - i - 1] - '0';
				ret -= pright[Rsize - i - 1] - '0';
				if(ret < 0)
				{
					pleft[Lsize - i - 2] -= 1;
					ret += 10;
				}
				pleft[Lsize - i - 1] = ret + '0';
			}
			while (*pleft == '0' && Lsize > 0)
			{
				pleft++;
				pright--;
			}
			pret++;
		}
		return pret;
	}

private:
	INT64 _value;
	string _strData;
};
#endif