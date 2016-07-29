#include<iostream>
#include<assert.h>
using namespace std;

//�����⣺��������������ĵ�һ���������
//�ֱ���ȡ����������ĳ��ȣ��������n����������ָ��ֱ�ָ�����������ͷ��
//�������n����֮������һ���ߣ�����ָ�������ָ��ָ��Ľڵ�

struct ListNode//����Ľڵ�ṹ
{
	int _data;
	ListNode* _next;
	ListNode(int x = 0)
		:_data(x)
		,_next(NULL)
	{ }
};

unsigned int GetListLength(ListNode* head)//��ȡ������ĳ���
{
	unsigned int count=0;
	assert(head);
	while(head)
	{
		count++;
		head=head->_next;
	}
	return count;
}

ListNode* FindFirstCommonNode(ListNode* plist1,ListNode* plist2)//������������ĵ�һ���������
{
	unsigned int count1 = GetListLength(plist1);
	unsigned int count2 = GetListLength(plist2);
	unsigned int nLengthDif = count1 - count2;

	ListNode* pLinkHeadLong = plist1;
	ListNode* pLinkHeadShort = plist2;

	if(count2 > count1)
	{
		pLinkHeadLong = plist2;
		pLinkHeadShort = plist1;
		nLengthDif = count2 - count1;
	}

	while (nLengthDif--)
	{
		pLinkHeadLong = pLinkHeadLong->_next;
	}

	while (pLinkHeadLong != NULL && pLinkHeadShort != NULL && pLinkHeadLong != pLinkHeadShort)
	{
		pLinkHeadLong = pLinkHeadLong->_next;
		pLinkHeadShort = pLinkHeadShort->_next;
	}

	ListNode* pFirstCommonNode = pLinkHeadLong;
	return pFirstCommonNode;
}


int main()
{
	ListNode* list11 = new ListNode(1);
	ListNode* list12 = new ListNode(2);
	ListNode* list13 = new ListNode(3);
	ListNode* list14 = new ListNode(6);
	ListNode* list15 = new ListNode(7);
	 list11->_next = list12;
	list12->_next = list13;
	list13->_next = list14;
	list14->_next = list15;

	ListNode* list21 = new ListNode(4);
	ListNode* list22 = new ListNode(5);
	list21->_next = list22;
	list22->_next = list14;

	ListNode* ret = FindFirstCommonNode(list11,list21);
	cout<<ret->_data<<endl;
	system("pause");
	return 0;
}