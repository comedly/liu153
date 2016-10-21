//Name:Trie���Ļ���ʵ��
//Description��Trie���Ļ���ʵ��
#pragma once
#include<iostream>
using namespace std;

const int sonnum = 26,base = 'a';
struct Trie
{
	int num;//��¼���ٵ���;���ýڵ㣬�����ٵ���ӵ���Ըý��Ϊĩβ�ĺ�׺
	bool terminal;//��terminal=true���ýڵ�û�к������
	int count;//��¼���ʵĳ��ִ������˽�㼴һ���������ʵ�ĩβ��ĸ
	struct Trie *son[sonnum];//�������
};

//����һ���½ڵ�
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

//����һ���´ʵ��ֵ���
//pnt������
//s:�´�
//len���´ʳ���
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

//ɾ��������
//pnt:����
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

//���ҵ������ֵ��е�ĩβ���
//pnt������
//s:����
//len�����ʳ���
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

