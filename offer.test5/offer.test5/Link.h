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

}