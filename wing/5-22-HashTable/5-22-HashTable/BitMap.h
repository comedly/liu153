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

	BitMap(size_t size)//size表示多少位，不是数据的个数
		:_size(size)
	{//调整大小为size/32 + 1即右移5位加1（为何加1：例如100/32=3,如果只开辟3个大小的空间（即只能保存0到96的数存在，不能保存97到99是否存在），所以需要多开辟一个空间）
		_a.resize((size >> 5) + 1);
	}

	//位图，注意1在移位时为左移num位不是左移32-num
	void Set(size_t x)//存入x，将对应的位置1
	{
		size_t index = x >> 5;
		size_t num = x % 32;
		++_size;
		_a[index] |= (1 << num);//1左移3位，进行|运算使_a中对应的位为1
	}

	void Remove(size_t x)//删除x，置0
	{
		size_t index = x >> 5;
		size_t num = x %32;
		--_size;
		_a[index] &= ~(1<<num);//1左移num位，进行&运算后是_a对应的位置0
	}

	bool Test(size_t x)//判断该数是否存在
	{
		size_t index = x >> 5;
		size_t num = x % 32;
		if(_a[index] & (1 << num))//该位若为1则存在
		{
			return true;
		}
		return false;
	}

	void Resize(size_t size)//重置大小
	{
		_a.resize((size>>5)+1);
	}

	size_t Size()//返回为图的总位数
	{
		return _size;
	}
	size_t _capacity()//返回该类型数据的个数
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