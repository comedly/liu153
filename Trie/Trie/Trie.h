//Name:Trie树的基本实现
//Description：Trie树的基本实现
#pragma once
#include<iostream>
using namespace std;

const int sonnum = 26,base = 'a';
struct Trie
{
	int num;//记录多少单词途径该节点，即多少单词拥有以该结点为末尾的后缀
	bool terminal;//若terminal=true，该节点没有后续结点
	int count;//记录单词的出现次数，此结点即一个完整单词的末尾字母
	struct Trie *son[sonnum];//后续结点
};

//创建一个新节点
Trie* newTire()
{
	Trie *temp = new Trie;
	temp->num = 1;
	temp->terminal = false;
	temp->count = 0;
	for(int i = 0;i < sonnum;i++)
		temp->son[i] = NULL;
	return temp;
}

//插入一个新词到字典树
//pnt：树根
//s:新词
//len：新词长度
void Insert(Trie* pnt,char*s,int len)
{
	Trie* temp = pnt;
	for(int i = 0;i<len;i++)
	{
		if(temp->son[s[i]-base] == NULL)
			temp->son[s[i]-base] = newTire();
		else
		{
			temp->son[s[i]-base]->num++;
			temp->terminal = false;
		}
		temp = temp->son[s[i] - base];
	}
	temp->terminal = true;
	temp->count++;
}

//删除整个树
//pnt:树根
void Delete(Trie* pnt)
{
	if(pnt != NULL)
	{
		for(int i=0;i<sonnum;i++)
		{
			if(pnt->son[i] != NULL)
				Delete(pnt->son[i]);
		}
	}
	delete pnt;
	pnt = NULL;
}

//查找单词在字典中的末尾结点
//pnt：树根
//s:单词
//len：单词长度
Trie* Find(Trie* pnt,char *s,int len)
{
	Trie* temp = pnt;
	for (int i = 0; i < len; i++)
	{
		if(temp->son[s[i] - base] != NULL)
			temp = temp->son[s[i]-base];
		else
		{
			return NULL;
		}
	}
	return temp;
}

void test()
{
	Trie* pnt = newTire();
	Insert(pnt,"abort",5);
	Insert(pnt,"ab",2);
	Insert(pnt,"cde",3);
}

