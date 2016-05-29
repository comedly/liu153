#pragma once 
#include<iostream>
#include<vector>
using namespace std;

class BitMap
{
public:
	BitMap()
		:_size(0)
	{ }

	BitMap(size_t size)//size��ʾ����λ���������ݵĸ���
		:_size(size)
	{//������СΪsize/32 + 1������5λ��1��Ϊ�μ�1������100/32=3,���ֻ����3����С�Ŀռ䣨��ֻ�ܱ���0��96�������ڣ����ܱ���97��99�Ƿ���ڣ���������Ҫ�࿪��һ���ռ䣩
		_a.resize((size >> 5) + 1);
	}

	//λͼ��ע��1����λʱΪ����numλ��������32-num
	void Set(size_t x)//����x������Ӧ��λ��1
	{
		size_t index = x >> 5;
		size_t num = x % 32;
		++_size;
		_a[index] |= (1 << num);//1����3λ������|����ʹ_a�ж�Ӧ��λΪ1
	}

	void Remove(size_t x)//ɾ��x����0
	{
		size_t index = x >> 5;
		size_t num = x %32;
		--_size;
		_a[index] &= ~(1<<num);//1����numλ������&�������_a��Ӧ��λ��0
	}

	bool Test(size_t x)//�жϸ����Ƿ����
	{
		size_t index = x >> 5;
		size_t num = x % 32;
		if(_a[index] & (1 << num))//��λ��Ϊ1�����
		{
			return true;
		}
		return false;
	}

	void Resize(size_t size)//���ô�С
	{
		_a.resize((size>>5)+1);
	}

	size_t Size()//����Ϊͼ����λ��
	{
		return _size;
	}
	size_t _capacity()//���ظ��������ݵĸ���
	{
		return _a.size();
	}

	void Print()
	{
		for(size_t i = 0;i < _a.size();i++)
		{
			cout<<_a[i]<<" "<<endl;
		}
		cout<<endl;
	}

protected:
	vector<size_t> _a;
	size_t _size;
};

void TestBitMap()
{
	BitMap bm(60);
	bm.Set(23);
	bm.Set(47);
	bm.Set(54);
	bm.Set(33);
	bm.Print();
	cout<<"is 23 EXIST? "<<bm.Test(23)<<endl;
	cout<<"is 13 EXIST? "<<bm.Test(13)<<endl;

	bm.Remove(54);
	cout<<"is 54 EXIST? "<<bm.Test(54)<<endl;
	
	cout<<"size : "<<bm.Size()<<endl;
	cout<<"_capacity : "<<bm._capacity()<<endl;

}