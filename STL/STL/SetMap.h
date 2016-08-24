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

	//使用STL算法find(),来搜寻元素，可以有效的运作，但不是好办法
	it = find(iset.begin(),iset.end(),3);
	if(it != iset.end())
		cout<<"3 found"<<endl;

	//面对关联式容器，应该使用其所提供的find函数来搜寻	//元素，会比使用STL算法find（）更加有效率，因为STL算法find()只是循序搜寻
	it = iset.find(3);
	if(it != iset.end())
		cout<<"3 found"<<endl;

	it = iset.find(1);
	if(it == iset.end())
		cout<<"1 not found" << endl;

	//企图通过迭代器来改变元素，是不被允许的
	//*it = 9;//error 
}

void MapTest()
{
	map<string,int> mymap;//以string为键值，int为实值
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

	//两对关联式容器，应该使用其所提供的find函数来搜寻元素，会比使用STL算法find（）更加有效。因为STL算法find只是循序搜寻

	it = mymap.find(string("aksk"));
	if(it == mymap.end())
		cout<<"aksk not find"<<endl;

	it = mymap.find(string("limit"));
	if(it != mymap.end())
		cout<<"limit  find"<<endl;

	it->second = 9;//可以通过map迭代器修改"value (not key)"
	int number2 = mymap[string("limit")];
	cout<<number2<<endl;
}