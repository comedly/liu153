//【面试题】给40亿个不重复的无符号整数，没排过序。给一个无符号的整数，如何判断该该数是否在这40亿个数中。

//在看到这个题后最先想到的方法是遍历这40亿个数，依次进行判断，但此做法需要的内存很大，大约为15G（4000000000*4/(1024*1024*1024)）,可见此算法不可取。

//如果内存够的话可以用位图实现，位图是一个数组的每一个元素数据的每个二进制位表示一个数据，每一位用0、1表示当前这个位置上是否存有值，同样是利用哈希存储的方法，此方法可以大大减少内存，对于此题是一个int类型就可以用32个位，需要的内存从15G降到500MB。

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
	{
		//调整大小为size/32+1即右移5位加1（为何+1：例如：100/32=3,如果只开辟3个大小的空间（即只能保存0-96的数的存在，不能保存97-99是否存在），所以需要多开辟一个空间）
		_a.resize((size>>5) + 1);
	}

	//位图，注意1在移位时为左移num不是32-num，因为该机器是大端模式，字数据的高字节存储在低地址，字数据的低字节存储在高地址。所以左移num
	void Set(size_t x)//存入x，将对应的位置设置为1
	{
		size_t index = x>>5;
		size_t num = x%32;
		++_size;
		_a[index] |= (1<<num);//1左移num位，进行|运算，使对应的位为1.
	}

	void Remove(size_t x)//删除x，置0
	{
		size_t index = x>>5;
		size_t num = x%32;
		--_size;
		_a[index] &= ~(1<<num);//1左移num位，进行&运算后使_a对应的位为0
	}
	
	bool Test(size_t x)//判断该数是否存在
	{
		size_t index = x>>5;
		size_t num = x % 32;
		if(_a[index] & (1<<num))//判断该位是否为1。
			return true;
		return false;
	}

	void Resize(size_t size)//重置大小
	{
		_a.resize((size>>5) + 1);
	}

	size_t Size()//返回图的总位数
	{
		return _size;
	}

	size_t _capacity()//返回该数据类型的个数
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