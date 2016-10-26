//�������⡿��40�ڸ����ظ����޷���������û�Ź��򡣸�һ���޷��ŵ�����������жϸø����Ƿ�����40�ڸ����С�

//�ڿ��������������뵽�ķ����Ǳ�����40�ڸ��������ν����жϣ�����������Ҫ���ڴ�ܴ󣬴�ԼΪ15G��4000000000*4/(1024*1024*1024)��,�ɼ����㷨����ȡ��

//����ڴ湻�Ļ�������λͼʵ�֣�λͼ��һ�������ÿһ��Ԫ�����ݵ�ÿ��������λ��ʾһ�����ݣ�ÿһλ��0��1��ʾ��ǰ���λ�����Ƿ����ֵ��ͬ�������ù�ϣ�洢�ķ������˷������Դ������ڴ棬���ڴ�����һ��int���;Ϳ�����32��λ����Ҫ���ڴ��15G����500MB��

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
	{
		//������СΪsize/32+1������5λ��1��Ϊ��+1�����磺100/32=3,���ֻ����3����С�Ŀռ䣨��ֻ�ܱ���0-96�����Ĵ��ڣ����ܱ���97-99�Ƿ���ڣ���������Ҫ�࿪��һ���ռ䣩
		_a.resize((size>>5) + 1);
	}

	//λͼ��ע��1����λʱΪ����num����32-num����Ϊ�û����Ǵ��ģʽ�������ݵĸ��ֽڴ洢�ڵ͵�ַ�������ݵĵ��ֽڴ洢�ڸߵ�ַ����������num
	void Set(size_t x)//����x������Ӧ��λ������Ϊ1
	{
		size_t index = x>>5;
		size_t num = x%32;
		++_size;
		_a[index] |= (1<<num);//1����numλ������|���㣬ʹ��Ӧ��λΪ1.
	}

	void Remove(size_t x)//ɾ��x����0
	{
		size_t index = x>>5;
		size_t num = x%32;
		--_size;
		_a[index] &= ~(1<<num);//1����numλ������&�����ʹ_a��Ӧ��λΪ0
	}
	
	bool Test(size_t x)//�жϸ����Ƿ����
	{
		size_t index = x>>5;
		size_t num = x % 32;
		if(_a[index] & (1<<num))//�жϸ�λ�Ƿ�Ϊ1��
			return true;
		return false;
	}

	void Resize(size_t size)//���ô�С
	{
		_a.resize((size>>5) + 1);
	}

	size_t Size()//����ͼ����λ��
	{
		return _size;
	}

	size_t _capacity()//���ظ��������͵ĸ���
	{
		return _a.size();
	}

	void Print()
	{
		for(size_t i = 0;i < _a.size();i++)
		{
			cout<<_a[i]<<" ";
		}
		cout<<endl;
	}
private:
	vector<size_t> _a;
	size_t _size;
};


void TestBitMap()
{
	BitMap bm(64);
	bm.Set(12);
	bm.Set(23);
	bm.Set(32);
	bm.Set(56);
	bm.Set(45);
	bm.Print();
	
	cout<<"Is 23 EXIST?  "<<bm.Test(23)<<endl;
	cout<<"Is 58 EXIST?  "<<bm.Test(58)<<endl;

	bm.Remove(23);
	cout<<"Is 23 EXIST?  "<<bm.Test(23)<<endl;

	cout<<"size:"<<bm.Size()<<endl;
	cout<<"_capacity:"<<bm._capacity()<<endl;
}