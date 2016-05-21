#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stack>

typedef int DataType;

typedef struct LinkNode
{
	DataType data;//
	struct LinkNode* next;//指向单链表的下一个结点
}LinkNode,*pLinkNode,*pLinkList;

void InitLinkList(pLinkList* pHead)//初始化单链表
{
	assert(pHead);
	*pHead = NULL;
}

void Destory(pLinkList* pHead) //销毁单链表
{
	if(*pHead == NULL)
		return;
	else
	{
		pLinkNode cur = *pHead;
		while (cur)  //依次删除单链表的结点
		{
			pLinkNode del = cur;
			cur = cur->next;
			free(del);
			del = NULL;
		}
	}
}

void HeadToTailPrintList(pLinkList* pHead) //从头到尾打印单链
{
	pLinkNode cur = *pHead;
	while (cur)
	{
		printf("%d  ",cur->data);
		cur = cur->next;
	}
	printf("over\n");
}

void TailToHeadPrintList1(pLinkList pHead)//从尾部到头打印单链表
{
	std::stack<LinkNode*> Nodes;
	LinkNode* pNode = pHead;
	while (pNode != NULL)
	{
		Nodes.push(pNode);
		pNode = pNode->next;
	}
	while(!Nodes.empty())
	{
		pNode = Nodes.top();
		printf("%d ",pNode->data);
		Nodes.pop();
	}
	printf("\n");
}

void TailToHeadPrintList2(pLinkList pHead)//因为递归本身就是一种栈的结构，于是基于递归实现反向打印
{
	if(pHead != NULL)
	{
		if(pHead->next != NULL)
		{
			TailToHeadPrintList2(pHead->next);
		}
		printf("%d ",pHead->data);
	}
	printf("\n");
}

pLinkNode BuyNode(DataType x)//创建一个结点
{
	pLinkNode NewNode = (pLinkNode)malloc(sizeof(LinkNode));
	NewNode->data = x;
	NewNode->next = NULL;
	return NewNode;
}

void PushBack(pLinkList* pHead,DataType x)//尾部插入
{
	pLinkNode cur = *pHead;
	pLinkNode NewNode = BuyNode(x);
	assert(pHead);
	if(cur == NULL)
	{
		*pHead = NewNode;
		return;
	}
	while (cur->next)
	{
		cur = cur->next;
	}
	cur->next = NewNode;
}

void PopBack(pLinkList* pHead)//尾删
{
	pLinkNode cur = *pHead;
	assert(pHead);
	if(*pHead == NULL)
	{
		return;
	}
	else if((*pHead)->next == NULL)
	{
		free(*pHead);
		*pHead = NULL;
	}
	else
	{
		pLinkNode del = NULL;
		while (cur->next->next)
		{
			cur = cur->next;
		}
		del = cur->next;
		cur->next = NULL;
		free(del);
		del = NULL;
	}
}

void PushFront(pLinkList* pHead,DataType x)//头插
{
	pLinkNode newNode = BuyNode(x);
	pLinkNode cur = *pHead;
	if(*pHead == NULL)
	{
		*pHead = newNode;
		return;
	}
	else
	{
		newNode->next = *pHead;
		*pHead = newNode;
	}
}

void PopFront(pLinkList* pHead)//头删
{
	assert(pHead);
	if(*pHead == NULL)
	{
		return;
	}
	else 
	{
		pLinkNode del = *pHead;
		*pHead = (*pHead)->next;
		free(del);
		del = NULL;
	}
}

void InsertList(pLinkList* pHead,pLinkNode pos,DataType x)//在pos所指向的结点前插入一个结点
{
	pLinkNode newNode = BuyNode(x);
	pLinkNode cur = *pHead;
	assert(pHead);
	assert(pos);
	if(*pHead == pos)
	{
		newNode->next = *pHead;
		*pHead = newNode;
	}
	else
	{
		while (cur->next != pos)
		{
			cur = cur->next;
		}
		newNode->next = cur->next;
		cur->next = newNode;
	}
}

int GetListLength(pLinkList* pHead)//链表的长度
{
	pLinkNode cur = *pHead;
	int count = 0;
	assert(pHead);
	while (cur)
	{
		count++;
		cur = cur->next;
	}
	return count;
}

pLinkNode Find(pLinkList* pHead,DataType x)//查找
{
	pLinkNode cur = *pHead;
	assert(pHead);
	while (cur)
	{
		if(cur->data == x)
			return cur;
		cur = cur->next;
	}
	return NULL;
}

pLinkNode FindKToTail(pLinkNode pHead,unsigned int k)//求链表倒数第k个结点
//增设两个指针都指向头结点，第一个指针先走k-1步后，两个指针同时走，当第一个指针指向最后一个结点时，第二个指针指向倒数第k个结点
{
	if(pHead == NULL || k == 0)
	{
		return NULL;
	}
	pLinkNode pAhead = pHead;
	pLinkNode pBehind = NULL;
	while (--k)
	{
		if(pAhead->next != NULL)
			pAhead = pAhead->next;
		else
		{
			return NULL;
		}
	}
	pBehind = pHead;
	while (pAhead->next != NULL)
	{
		pAhead = pAhead->next;
		pBehind = pBehind->next;
	}
	return pBehind;
}

void Remove1(pLinkList* pHead,DataType x)//借助Find（）函数删除结点
{
	pLinkNode pos = Find(pHead,x);
	pLinkNode cur = *pHead;
	pLinkNode del = NULL;
	assert(pHead);
	if((*pHead) == pos)
	{
		del = *pHead;
		*pHead = (*pHead)->next;
		free(del);
		del = NULL;
	}
	else
	{
		while (cur->next != pos)
		{
			cur = cur->next;
		}
		del = cur->next;
		cur->next = del->next;
		free(del);
		del = NULL;
	}
}

void Remove2(pLinkList* pHead,DataType x)//不需要借助Find函数，增设一个指向当前结点的指针
{
	pLinkNode cur = *pHead;
	pLinkNode del = NULL;
	pLinkNode prev = NULL;
	assert(pHead);
	if(cur == NULL)
	{
		return;
	}
	while (cur)
	{
		if(cur->data == x)
		{
			del = cur;
			if(cur == *pHead)
			{
				*pHead = (*pHead)->next;
			}
			else
			{
				prev->next = cur->next;
			}
			free(del);
			break;
		}
		prev = cur;
		cur = cur->next;
	}
}

void RemoveAll(pLinkList* pHead,DataType x)//删除所有相同的结点
{
	pLinkNode cur = *pHead;
	pLinkNode del = NULL;
	pLinkNode prev = NULL;
	assert(pHead);
	while (cur)
	{
		if(cur->data == x)
		{
			del = cur;
			if(cur == *pHead)
			{
				cur = (*pHead)->next;
			}
			else
			{
				prev->next = cur->next;
				cur = prev->next;
			}
			free(del);
		}
		else
		{
			prev = cur;
			cur = cur->next;
		}
	}
}

void Erase(pLinkList* pHead,pLinkNode pos)//删除指定位置的结点
{
	pLinkNode cur = *pHead;
	pLinkNode del = NULL;
	assert(pHead);
	if(*pHead == NULL)
	{
		return;
	}
	else if(*pHead == pos)
	{
		cur = (*pHead)->next;
		free(*pHead);
		*pHead = cur;
	}
	else
	{
		while (cur->next)
		{
			if(cur->next == pos)
			{
				del = cur->next;
				cur->next = del->next;
				free(del);
				del = NULL;
			}
			cur = cur->next;
		}
	}
}

void EraseNotTail(pLinkNode pos)//删除无头的非尾结点
{
	pLinkNode del = pos->next;
	pos->data = del->data;
	pos->next = del->next;
	free(del);
	del = NULL;
}

void ReverseList(pLinkList* pHead)//链表的逆序
{
	pLinkNode pNewNode = NULL;
	pLinkNode cur = *pHead;
	pLinkNode prev = NULL;
	assert(pHead);
	if((cur == NULL) || (cur->next == NULL))
	{
		return;
	}
	while (cur)
	{
		prev = cur;
		cur = cur->next;
		prev->next = pNewNode;
		pNewNode = prev;
	}
	*pHead = pNewNode;
}

void BubbleSort(pLinkList* pHead)//冒泡排序
{
	pLinkNode cur = *pHead;
	assert(pHead);
	while (cur)
	{
		if(cur->next != NULL)
		{
			pLinkNode pos = cur->next;
			while (pos)
			{
				if(cur->data > pos->data)
				{
					DataType temp = cur->data;
					cur->data = pos->data;
					pos->data = temp;
				}
				pos = pos->next;
			}
			cur = cur->next;
		}
		else
		{
			return;
		}
	}
}

void InsertFrontNode(pLinkNode pos,DataType x)//无头结点的情况下，再当前结点前插入一个数据
{
	pLinkNode NewNode = BuyNode(x);
	DataType temp = 0;
	assert(pos);
	NewNode->next = pos->next;
	pos->next = NewNode;
	temp = pos->data;
	pos->data = NewNode->data;
	NewNode->data = temp;
}

pLinkNode Merge(pLinkList l1,pLinkList l2)//非递归法实现两个有序链表的合并
{
	pLinkNode newHead = NULL;
	pLinkNode cur = NULL;
	if(l1 == l2)
	{
		return l1;
	}
	if((l1 != NULL) && (l2 == NULL))
	{
		return l1;
	}
	if((l1 == NULL) && (l2 != NULL))
	{
		return l2;
	}
	if(l1->data < l2->data)
	{
		newHead = l1;
		l1 = l1->next;
	}
	else
	{
		newHead = l2;
		l2 = l2->next;
	}
	cur = newHead;
	while ((l1) && (l2))
	{
		if(l1->data < l2->data)
		{
			cur->next = l1;
			l1 = l1->next;
		}
		else
		{
			cur->next = l2;
			l2 = l2->next;
		}
		cur = cur->next;
	}
	if(l1)
	{
		cur->next = l1;
	}
	else
	{
		cur->next = l2;
	}
}

pLinkNode _Merge(pLinkList l1,pLinkList l2)//基于递归实现两个有序链表的合并
{
	pLinkNode newHead = NULL;
	if((l1 == NULL) && (l2 == NULL))
	{
		return NULL;
	}
	else if((l1 != NULL) && (l2 == NULL))
	{
		return l1;
	}
	else if((l1 == NULL) && (l2 != NULL))
	{
		return l2;
	}
	if(l1->data < l2->data)
	{
		newHead = l1;
		newHead->next = _Merge(l1->next,l2);
	}
	else
	{
		newHead = l2;
		newHead->next = _Merge(l1,l2->next);
	}
	return newHead;
}

pLinkNode FindMidNode(pLinkList* pHead)//查找链表的中间结点
{
	pLinkNode fast = *pHead;
	pLinkNode slow = *pHead;
	while(fast && fast->next)
	{
		fast = fast->next->next;
		slow = slow->next;
	}
	return slow;
}

void DelKNode(pLinkList *pHead,int k)//删除单链表的倒数第k（k>1）个结点
{
	pLinkNode fast = *pHead;
	pLinkNode slow = *pHead;
	pLinkNode del = NULL;
	assert(pHead);
	assert(k>1);
	while (--k)
	{
		fast = fast->next;
	}
	while (fast->next)
	{
		fast = fast->next;
		slow = slow->next;
	}
	del = slow->next;
	slow->data = slow->next->data;
	slow->next = slow->next->next;
	free(del);
}

pLinkNode JosephCycle(pLinkList* pHead,int num)//约瑟夫环
{
	pLinkNode cur = *pHead;
	pLinkNode del = NULL;
	int count = 0;
	assert(pHead);
	while (1)
	{
		count = num;
		if(cur->next == cur)
		{
			break;
		}
		while (--count)
		{
			cur = cur->next;
		}
		printf("%d ",cur->data);
		del = cur->next;
		cur->data = cur->next->data;
		cur->next = cur->next->next;
		free(del);
	}
	*pHead = cur;
	return cur;
}

//链表带环问题
pLinkNode CheckCycle(pLinkList plist)//判断链表是否带环
{
	pLinkList fast = plist;
	pLinkList slow = plist;
	while (fast && fast->next)
	{
		slow = slow->next;
		fast = fast->next->next;
		if(fast == slow)
		{
			return slow;
		}
	}
	return NULL;
}

int GetCircleLength(pLinkNode meet)//若带环则求环的长度
{
	int count = 0;
	pLinkNode pos = meet;
	do
	{
		pos = pos->next;
		count++;
	}while (pos != meet);
	return count;
}

pLinkNode GetCycleEntryNode(pLinkList plist,pLinkNode meetNode)//获取环的入口结点
{
	pLinkNode entry = plist;
	pLinkNode meet = meetNode;
	while (entry != meet)
	{
		entry = entry->next;
		meet = meet->next;
	}
	return entry;
}
