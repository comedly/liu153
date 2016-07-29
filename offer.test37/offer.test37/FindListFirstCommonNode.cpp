#include<iostream>
#include<assert.h>
using namespace std;

//面试题：查找两个单链表的第一个公共结点
//分别求取两个单链表的长度，并求出差n，在设两个指针分别指向两个链表的头，
//令长得先走n步，之后两个一起走，返回指向长链表的指针指向的节点

struct ListNode//链表的节点结构
{
	int _data;
	ListNode* _next;
	ListNode(int x = 0)
		:_data(x)
		,_next(NULL)
	{ }
};

unsigned int GetListLength(ListNode* head)//求取单链表的长度
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

ListNode* FindFirstCommonNode(ListNode* plist1,ListNode* plist2)//查找两个链表的第一个公共结点
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