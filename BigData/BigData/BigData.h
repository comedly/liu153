#ifndef __BIGDATA_H__
#define __BIGDATA_H__

#include<iostream>
using namespace std;
//�����Ĵ�����Ҫ�����ַ�����ʵ��
#include<string.h>
#include<assert.h>

#define UN_INT 0xCCCCCCCCCCCCCCCC
#define MAX_INT64 0x7FFFFFFFFFFFFFFF
#define MIN_INT64 0x8000000000000000
typedef long long INT64;

class  BigData
{
public:
	BigData(INT64 value = UN_INT)//���캯��
		:_value(value)
	 {
		 INT64ToString();
	 }

	BigData(const char* ptr)//�ַ������캯��
	{
		if(NULL == ptr)//��鴫����ַ����Ƿ�Ϊ��
			return;
		char* src = (char*)ptr;
		char cSymbol = ptr[0];//��¼����λ
		if(cSymbol == '+' || cSymbol == '-')//������ַ������ַ�Ϊ+/-
		{
			src++;
		}
		else if(cSymbol >= '0' && cSymbol <= '9')//������ַ�ֱ��Ϊ���֣�����+/-
		{
			cSymbol = '+';
		}
		else
		{
			return;
		}
		while ('0' == *src)//��ֹ000012345��������ĳ��֣�����ֱ�Ӱ�0����
		{
			src++;
		}
		_strData.resize(strlen(ptr)+1);//_strData��С������string����resize()����
		_strData[0] = cSymbol;//����һ���ռ���Ϊ����λ
		_value = 0;//�����ַ���ת���������
		int count = 1;
		while (*src >= '0' && *src <= '9')//�����ַ���
		{
			_value = _value * 10 + (*src - '0');
			_strData[count++] = *src;
			src++;
		}
		_strData.resize(count);//���µ�����С
		if(cSymbol == '-')
		{
			_value =(-1) * _value;
		}
	}

	//�ӷ�
	BigData operator+(const BigData& bigData)//+��������أ�(���ô�ֵ�ķ�ʽ�������û����this)�����Ƿ����
	{
		//������������û�����
		if(IsINT64OverFlow() && bigData.IsINT64OverFlow())
		{
			//��������������ţ�����������
			if(_strData[0] != bigData._strData[0])
			{
				return BigData(_value + bigData._value);//���ù��캯��
			}
			//������������ͬ�ţ�����п������
			//ͬΪ+�� �������ֵΪ10 ��_value:5  bigdata._value:4 ��10-5>4,��Ӳ����������_value:7 ��10-7<4,��ӻ�������
			//ͬΪ-�������ڴ˷�Χ����Сֵ(-10) - _value(-4)��ֵС�ڵ���bigdata._value(-5)��ֵ���򲻻��������֮���
			else if((_value >= 0 && MAX_INT64 - _value >= bigData._value) || (_value <= 0 && MIN_INT64 - _value <= bigData._value))
			{
				return BigData(_value + bigData._value);
			}
		}
		//����������������һ�����
		return BigData(Add(_strData,bigData._strData).c_str());
	}

	BigData operator-(const BigData& bigData)//�����-����
	{
		if(IsINT64OverFlow() && bigData.IsINT64OverFlow()) //������������û�����
		{
			//��ͬ��
			if(_strData[0] == bigData._strData[0]) 
			{
				return BigData(_value - bigData._value);//���ù��캯��
			}
			else
			{
				//���������������
				//����Χ�е����ֵ10��_value:6,bigData._value:-7   ��-10��+ 6 > -7 ������
				//����Χ�е����ֵ-10��_value:-6,bigData._value:7   10 + ��-6��< 7 ������
				if((_value >= 0 && MIN_INT64 + _value <= bigData._value) ||(_value <= 0 && MAX_INT64 + _value >= bigData._value))
				{
					return BigData(_value - bigData._value);
				}
			}
		}
		else
		{
			if(_strData[0] != bigData._strData[0])//���
			{
				return BigData(Add(_strData,bigData._strData).c_str());
			}
			else
			{
				return BigData(Sub(_strData,bigData._strData).c_str());
			}
		}
	}

	BigData operator*(const BigData& bigData)//�����*����
	{
		if(_value == 0 || bigData._value == 0)
		{
			return BigData(INT64(0));
		}
		if(IsINT64OverFlow() && bigData.IsINT64OverFlow())//�������ݶ�û�����
		{
			//ͬ��
			//����˷�Χ�����ֵΪ10��������������2 6����10/2 = 5 < 6,������
			//������������ -2 -6,10/(-2) = -5 > -6һ�������
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
				//����������2 -6 ��10/2 = 5 < -(-6)�������Ϊ-4�Ļ��Ͳ������
				//����������-2 6 ��10/-2 = -5 > -6 �������Ϊ4�Ļ��Ͳ������
				if((_value > 0 && MAX_INT64 / _value >= -bigData._value)
					|| (_value < 0 && MAX_INT64 / _value <= -bigData._value))
				{
					return _value * bigData._value;
				}
			}
		}
		return BigData(Mul(_strData,bigData._strData).c_str());
	}

	//���� ������Ϊ0 �����ֱ�ӳ�
	//��left < right���������ֵ
	//right == +1(-1) 
	//left = right ����Ϊ+1��-1��
	BigData operator/(const BigData& bigData)//�����������
	{
		if(0 == bigData._value)//�������Ƿ�Ϊ0
		{
			assert(false);
			return BigData(INT64(0));
		}
		if(IsINT64OverFlow() && bigData.IsINT64OverFlow())//�������ݶ������
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
		//����Ϊ1��-1
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

	friend ostream& operator<< (ostream& os,const BigData& bigdata)//������������
	{
		if(bigdata.IsINT64OverFlow())//��������
		{
			os<<bigdata._value<<endl;
		}
		else
		{
			char* ptr = (char*)bigdata._strData.c_str();
			//c_str����const char*���ͷ���string�е��ַ����������Ҫ����ǿ������ת��
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
	void INT64ToString()//��_valueת�����ַ���
	{
		char cSymbol = '+';//cSymbol��¼�����ķ���λ
		if(_value < 0)
		{
			cSymbol = '-';
		}
		_strData.append(1,cSymbol);//���Ƿ���λ������һλ�ַ�cSymbol��ɵ��ַ�����ʵ��Ϊ����λ��
		INT64 number = _value;
		while (number) //ת���ַ�����ת������ַ�����_value���෴��
		{
			int num = number % 10;
			if(number < 0)
			{
				num = 0 - num;
			}
			_strData.append(1,num + '0');
			number = number/10;
		}
		char* left = (char*)_strData.c_str()+1;//leftָ��һ��������һ���ַ�����λ��λ��
		char* right = left + _strData.size() - 2;//ָ�����һ��Ԫ��
		while (left < right)//�ַ������ã����ú��ַ�����ʾ��ֵ��_value���
		{
			char tmp = *left;
			*left = *right;
			*right = tmp;
			left++;
			right--;
		}
	}

	bool IsINT64OverFlow() const //const���������Ǿ�̬�ģ��������ֵ
	{
		string temp("+9223372036854775807");//string�Ķ���tempʵ����
		if('-' == _strData[0])
		{
			temp = "-9223372036854775807";
		}
		if(_strData.size() < temp.size())//���紦������true
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

	string Add(string left,string right)//�ַ�����ӣ�left��right��ͬ�ŵ�
	{
		int LSize = left.size();//�ַ������ֽ���
		int RSize = right.size();
		//�������ַ����任Ϊ��һ���ַ������ֽ������ڵڶ������ֽ������������ڼ���
		if(LSize < RSize)
		{
			swap(left,right);
			swap(LSize,RSize);		
		}
		string ret;//���������Ӻ�Ľṹ
		ret.resize(LSize+1);//resize�������൱�ڿ���һ��LSize+1����С�Ŀռ�
		ret[0] = left[0];//�Ƚ�����λ���п���
		char temp = 0;//�����λ
		for(int i = 1;i < LSize;i++)
		{
			int src = left[LSize - i] + temp - '0';
			if(i < RSize)//��ֹ�ڶ������ݻ�һֱ����ȡ�ַ���������Խ��
			{
				src += right[RSize - i] - '0';
			}
			ret[LSize - i +1] = src % 10 + '0';
			temp = src / 10;
		}
		ret[1] = temp + '0';
		return ret;
	}

	string Sub(string left,string right)//�ַ������
	{
		int LSize = left.size();
		int RSize = right.size();//�ַ������ֽ���
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
		string ret;//�洢�����Ľ��
		ret.resize(left.size()+1);//����һ���left + 1һ����С�Ŀռ�
		ret[0] = cSymbol;//��һλΪ����λ
		for(int i = 1;i < LSize;i++)
		{
			char src = left[LSize - i] - '0';
			if(i < RSize)
			{
				src -= right[RSize - i] - '0';
			}
			if(src < 0)//�ж��Ƿ���Ҫ��λ
			{
				left[LSize - i -1] -= 1;
				src += 10;
			}
			ret[LSize - i] = src + '0';
		}
		return ret;
	}

	string Mul(string left,string right)//�ַ������
	{
		int LSize = left.size();
		int RSize = right.size();//��¼�ַ������ֽ���
		char cSymbol = '+';
		if(left[0] != right[0])
		{
			cSymbol = '-';
		}
		if(LSize > RSize)//�����ֽ�С����Ϊ��һ�����ݣ��ܹ����ѭ��Ч��
		{
			swap(left,right);
			swap(LSize,RSize);
		}
		string ret;
		ret.assign(LSize + RSize - 1,'0');//assign()����LSize + RSize - 1���ռ䣬����ʼ��Ϊ0
		int len = ret.size();//���ַ����ĳ���
		int num = 0;//ÿһ��������ƶ���λ��
		ret[0] = cSymbol;//��¼����λ
		for(int i = 1;i < LSize;i++)
		{
			char src = left[LSize - i] - '0';
			char dst = 0;//�����λ
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

	string Div(string left,string right)//�ַ������
	{
		string ret;
		ret.resize(1,'+');
		if(left[0] != right[0])//ȷ���̵ķ���
		{
			ret[0] = '-';
		}
		char *pLeft = (char*)(left.c_str()+1);
		char *pRight = (char*)(right.c_str()+1);
		int len = right.size() - 1; //��Ϊ�з���λ
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
			if(len > right.size())//pLeft��pRight��һλ���Ϊ0����pLeft�к���0
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

	bool IsLeftString(const char* pleft,int Lsize,const char* pright,int Rsize)//�жϱ������Ƿ���ڻ�С�ڳ���
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
		while (1) //������ > ����
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