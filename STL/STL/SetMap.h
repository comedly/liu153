#pragma once

#include<set>
#include<map>
#include<string>
#include<iostream>
using namespace std;

void SetTest()
{
	int i;
	int ia[5] = {9,1,8,3,4};
	set<int> iset(ia,ia+5);

	set<int>::iterator it;
	it = iset.begin();
	while (it != iset.end())
	{
		cout<<*it<<" ";
		++it;
	}
	cout<< endl;

	cout<<"size="<<iset.size()<<endl;
	cout<<"3 count = "<<iset.count(3)<<endl;

	iset.insert(3);
	cout<<"size="<<iset.size()<<endl;//size = 5
	cout<<"3 count = "<<iset.count(3)<<endl; //3 count = 1

	iset.insert(6);
	cout<<"size="<<iset.size()<<endl;
	cout<<"3 count = "<<iset.count(3)<<endl;

	iset.erase(1);
	cout<<"size="<<iset.size()<<endl; //size = 5
	cout<<"1 count = "<<iset.count(0)<<endl;//1 count = 0

	it = iset.begin();
	while (it != iset.end())
	{
		cout<<*it<<" ";
		++it;
	}
	cout<<endl;

	//ʹ��STL�㷨find(),����ѰԪ�أ�������Ч�������������Ǻð취
	it = find(iset.begin(),iset.end(),3);
	if(it != iset.end())
		cout<<"3 found"<<endl;

	//��Թ���ʽ������Ӧ��ʹ�������ṩ��find��������Ѱ	//Ԫ�أ����ʹ��STL�㷨find����������Ч�ʣ���ΪSTL�㷨find()ֻ��ѭ����Ѱ
	it = iset.find(3);
	if(it != iset.end())
		cout<<"3 found"<<endl;

	it = iset.find(1);
	if(it == iset.end())
		cout<<"1 not found" << endl;

	//��ͼͨ�����������ı�Ԫ�أ��ǲ��������
	//*it = 9;//error 
}

void MapTest()
{
	map<string,int> mymap;//��stringΪ��ֵ��intΪʵֵ
	mymap[string("job")] = 1;
	mymap[string("jack")] = 2;
	mymap[string("blose")] = 3;
	mymap[string("tom")] = 4;

	pair<string,int> value(string("limit"),5);
	mymap.insert(value);

	map<string,int>::iterator sim_it = mymap.begin();
	while (sim_it != mymap.end())
	{
		cout<<sim_it->first<<' '<<sim_it->second<<endl;
		++sim_it;
	}

	int number = mymap[string("blose")];
	cout<<number<<endl;//3

	map<string ,int>::iterator it;

	//���Թ���ʽ������Ӧ��ʹ�������ṩ��find��������ѰԪ�أ����ʹ��STL�㷨find����������Ч����ΪSTL�㷨findֻ��ѭ����Ѱ

	it = mymap.find(string("aksk"));
	if(it == mymap.end())
		cout<<"aksk not find"<<endl;

	it = mymap.find(string("limit"));
	if(it != mymap.end())
		cout<<"limit  find"<<endl;

	it->second = 9;//����ͨ��map�������޸�"value (not key)"
	int number2 = mymap[string("limit")];
	cout<<number2<<endl;
}