#pragma once

#include<iostream>
#include<fstream>
#include<vector>
#include<list>

using namespace std;

//STL ������vector �� list ��ϰ
//-------------------------- vector ---------------------
void PrintVector(vector<int>& v)//˳���ӡ
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
	vector<int>::reverse_iterator it = v.rbegin();//�����ӡ
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
	while (vec.back() != 0)//�ж�vector��ĩβԪ��
	{
		vec.push_back(vec.back()-1);
	}
	cout<<"vec contains:";
	PrintVector(vec);
}

//vector::at 
//���ص�ǰvectorָ��λ�õ�Ԫ�ص����ã�at()��[]��������Ӱ�ȫ����Ϊ����������ȥ����vector��Խ���Ԫ��
void attest()
{
	vector<int> vec(5,1);
	PrintVector(vec);

	/*for(int i = 0;i < 10;i++)
	{
		cout<<"elements:"<<i<<"is"<<vec[i]<<endl;//������vectorĩβ��Ԫ�أ��ᵼ�³����������
	}*/

	for(int i = 0;i < vec.size();i++)
	{
		cout<<"elements:"<<i<<"is "<<vec.at(i)<<endl;//at�����ܹ��������Ƿ�Խ�粢����Խ��ʱ�׳�һ���쳣
	}
	cout<<"��ǰ������������"<<vec.size()<<endl;
}

//vector::capacity()//����vector�����½����ڴ����ǰ�������ɵ�Ԫ������
//vector::size()��ǰԪ�صĸ���
void capacitytest()
{
	vector<int> vec;
	for(int i = 0;i<100;i++)
	{
		vec.push_back(i);
	}
	cout<<"size��"<<vec.size()<<endl;
	cout<<"capacity��"<<vec.capacity()<<endl;
}
 
//vector::erase(iterator loc)ɾ��ָ��λ�õ�Ԫ��
//vector::erase(iterator start,iterator end);ɾ��������[start,end)������Ԫ�أ�����ɾ�������һ��Ԫ�ص���һ��λ�õĵ�����

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

//vector::resize()//�ı䵱ǰvector�Ĵ�СΪsize���Ҷ��´�����Ԫ�ظ�ֵ
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

//Ϊ��ǰvectorԤ�����ٹ�����size��Ԫ�صĿռ䣨ע�⣺ʵ�ʿռ���ܴ���size��

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

//vector::insert(itertor loc,const TYPE& val)��locλ��ǰ����val��Ԫ�أ�����ָ�����Ԫ�صĵ�����
//vector::insert(itertor loc,size_type num,const TYPE& val)��ָ��λ��locǰ����num��ֵΪval��Ԫ��
//vector::insert(iterator loc, input_iterator start,input_iterator end)��ָ��λ��ǰ����ָ������[start��end)������Ԫ��

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

//vector::front()//���ص�ǰvector��ʼԪ�ص�����

void fronttest()
{
	vector<int> vec;
	vec.push_back(78);
	vec.push_back(16);
	//now front equals 78,and back 16

	vec.front() -= vec.back();
	cout<<"vec.front() is now "<<vec.front()<<endl;

}

//vector::swap()������ǰvector������һ��vector��Ԫ��
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

//list::unique()ȡ�أ���֤Ψһ��
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

//void assign( input_iterator start, input_iterator end );������[start, end)��Ԫ�ظ�����ǰvector 
//void assign( size_type num, const TYPE &val );��num��ֵΪval��Ԫ�ص�vector��.����������������Ϊvector��ֵ��ǰ������.


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


