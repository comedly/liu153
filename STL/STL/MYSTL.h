#pragma once

#include<iostream>
#include<fstream>
#include<vector>
#include<list>

using namespace std;

//STL 中容器vector 和 list 练习
//-------------------------- vector ---------------------
void PrintVector(vector<int>& v)//顺序打印
{
	vector<int>::iterator it = v.begin();
	while (it != v.end())
	{
		cout<<*it<<" ";
		it++;
	}
	cout<<endl;
}

void ReversePrintVector(vector<int>& v)
{
	vector<int>::reverse_iterator it = v.rbegin();//反向打印
	while (it != v.rend())
	{
		cout<<*it<<" ";
		it++;
	}
	cout<<endl;
}

//vector::back
void backtest()
{
	vector<int> vec;
	vec.push_back(10);
	while (vec.back() != 0)//判断vector的末尾元素
	{
		vec.push_back(vec.back()-1);
	}
	cout<<"vec contains:";
	PrintVector(vec);
}

//vector::at 
//返回当前vector指定位置的元素的引用，at()比[]运算符更加安全，因为他不会让你去访问vector内越界的元素
void attest()
{
	vector<int> vec(5,1);
	PrintVector(vec);

	/*for(int i = 0;i < 10;i++)
	{
		cout<<"elements:"<<i<<"is"<<vec[i]<<endl;//访问了vector末尾的元素，会导致出错，程序崩溃
	}*/

	for(int i = 0;i < vec.size();i++)
	{
		cout<<"elements:"<<i<<"is "<<vec.at(i)<<endl;//at函数能够辨别访问是否越界并且在越界时抛出一个异常
	}
	cout<<"当前容器的数量："<<vec.size()<<endl;
}

//vector::capacity()//返回vector在重新进行内存分配前所能容纳的元素数量
//vector::size()当前元素的个数
void capacitytest()
{
	vector<int> vec;
	for(int i = 0;i<100;i++)
	{
		vec.push_back(i);
	}
	cout<<"size："<<vec.size()<<endl;
	cout<<"capacity："<<vec.capacity()<<endl;
}
 
//vector::erase(iterator loc)删除指定位置的元素
//vector::erase(iterator start,iterator end);删除在区间[start,end)的所有元素，返回删除的最后一个元素的下一个位置的迭代器

void erasetest()
{
	vector<int> vec;
	for(int i = 1;i <= 10;i++)
		vec.push_back(i);
	PrintVector(vec);

	//erase 3th element
	vec.erase(vec.begin()+2);
	PrintVector(vec);

	//erase the first 3 element
	vec.erase(vec.begin(),vec.begin()+3);
	PrintVector(vec);
}

//vector::resize()//改变当前vector的大小为size，且对新创建的元素赋值
void resizetest()
{
	vector<int> vec;
	unsigned int i;
	for(i = 1; i <= 10;i++)
	{
		vec.push_back(i);
	}
	vec.resize(5);
	vec.resize(8,100);
	vec.resize(12);
	PrintVector(vec);
}

//为当前vector预留至少共容纳size个元素的空间（注意：实际空间可能大于size）

void reservetest()
{
	vector<int> content;
	size_t filesize;

	ifstream file("test.bin",ios::in|ios::ate|ios::binary);

	if(file.is_open())
	{
		filesize = file.tellg();
		content.reserve(filesize);

		file.seekg(0);
		while (!file.eof())
		{
			content.push_back(file.get());
		}

		vector<int>::iterator it;
		for(it=content.begin();it<content.end();it++)
		{
			cout<<hex<<*it;
		}
	}
}

//vector::insert(itertor loc,const TYPE& val)在loc位置前插入val的元素，返回指向这个元素的迭代器
//vector::insert(itertor loc,size_type num,const TYPE& val)在指定位置loc前插入num个值为val的元素
//vector::insert(iterator loc, input_iterator start,input_iterator end)在指定位置前插入指定区间[start，end)的所有元素

void inserttest()
{
	vector<int> vec(3,100);
	vector<int>::iterator it;
	PrintVector(vec);//100 100 100

	it = vec.begin();
	it = vec.insert(it,200);
	PrintVector(vec);//200 100 100 100

	vec.insert(it,2,300);
	PrintVector(vec);//300 300 200 100 100 100

	it = vec.begin();
	vector<int> anvec(2,400);
	vec.insert(it+2,anvec.begin(),anvec.end());
	PrintVector(vec);//300 300 400 400 200 100 100 100
}

//vector::front()//返回当前vector起始元素的引用

void fronttest()
{
	vector<int> vec;
	vec.push_back(78);
	vec.push_back(16);
	//now front equals 78,and back 16

	vec.front() -= vec.back();
	cout<<"vec.front() is now "<<vec.front()<<endl;

}

//vector::swap()交换当前vector与另外一个vector的元素
void swaptest()
{
	vector<int> vec1(2,100);
	vector<int> vec2(2,200);
	vec1.swap(vec2);
	cout<<"vec1's element: ";
	PrintVector(vec1);

	cout<<"vec2's element: ";
	PrintVector(vec2);
}

//------------------------ list -----------------------------
void PrintList(list<int>& l)
{
	list<int>::iterator it = l.begin();
	while (it != l.end())
	{
		cout<<*it<<" ";
		it++;
	}
	cout<<endl;
}

//list::unique()取重，保证唯一性
void uniquetest()
{
	list<int> l;
	l.push_back(1);
	l.push_back(3);
	l.push_back(2);
	l.push_back(3);
	l.push_back(4);
	l.push_back(3);
	PrintList(l);
	l.sort();
	PrintList(l);
	l.unique();
	PrintList(l);
}

//void assign( input_iterator start, input_iterator end );将区间[start, end)的元素赋到当前vector 
//void assign( size_type num, const TYPE &val );赋num个值为val的元素到vector中.这个函数将会清除掉为vector赋值以前的内容.


//list::splice()
void splicetest()
{
	list<int> l1;
	list<int> l2;
	list<int>::iterator it;
	l1.push_back(1);
	l1.push_back(2);
	l1.push_back(3);
	l1.push_back(4);
	PrintList(l1);

	l2.push_back(10);
	l2.push_back(20);
	l2.push_back(30);
	PrintList(l2);

	it = l1.begin();
	++it;

	l1.splice(it,l2);
	PrintList(l1);
	PrintList(l2);

	l2.splice(l2.begin(),l1,it);

	PrintList(l1);
	PrintList(l2);
}


