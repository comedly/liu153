#ifndef _LIANBIAO_H__
#define _LIANBIAO_H__

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

typedef int DataType;

typedef struct LinkNode
{
	DataType data;
	struct LinkNode *next;
}LinkNode, *pLinkNode, *pList;

void InitLinkList(pList* pHead);
void Destroy(pList *pHead);
void PushBack(pList* pHead, DataType x);
void PopBack(pList* pHead);
void PushFront(pList* pHead, DataType x);
void PopFront(pList* pHead);
void PrintList(pList list);
int GetListLength(pList head);
pLinkNode Find(pList head, DataType x);
void Insert(pList *pHead, pLinkNode pos, DataType x);
void Remove(pList *pHead, DataType x);
void RemoveAll(pList *pHead, DataType x);
void Erase(pList *pHead, pLinkNode pos);
pLinkNode JosephCycle(pList* pHead,int num);
pLinkNode FindMidNode(pList plist);//查找中间结点
void DelNode(pList plist,int k);//删除链表的第k个结点
pLinkNode CheckCycle(pList list);//判断链表是否带环
int GetCycleLength(pLinkNode meet);//求环的长度
pLinkNode GetCycleEnterNode(pList plist,pLinkNode meetNode);//求取带环链表的入口结点
int CheckCross(pList list1,pList list2);//判断两个链表是否相交
pLinkNode _Merge(pList l1,pList l2);//合并单链表的递归算法

pLinkNode buyNode(DataType x)
{
	pLinkNode newNode=(pLinkNode)malloc(sizeof(LinkNode));
	newNode->data=x;
	newNode->next=NULL;
	return newNode;
}

void InitLinkList(pList* pHead)
{
	assert(pHead);
	(*pHead)=NULL;
}

void Destroy(pList *pHead)
{
	pLinkNode cur=*pHead;
	if(*pHead==NULL)
	{
		return;
	}
	else
	{
		while(cur->next)
		{
			pLinkNode del=cur;
			cur=cur->next;
			free(del);
		}
	}
}

void PushBack(pList* pHead, DataType x)//尾插
{ 
	pLinkNode cur=*pHead;
	assert(pHead);
	pLinkNode newNode=buyNode(x);
	if(cur==NULL)
	{
		*pHead=newNode;
		return;
	}
	while(cur->next)
	{
		cur=cur->next;
	}
	cur->next=newNode;
}

void PopBack(pList* pHead)
{
	assert(pHead);
	pLinkNode cur=*pHead;
	if(*pHead==NULL)//没有结点
	{
		return;
	}
	else if((*pHead)->next==NULL)//一个结点
	{
		free(*pHead);
		*pHead=NULL;
	}
	else 
	{
		pLinkNode del;
		while(cur->next->next)
		{
			cur=cur->next;
		}
		del=cur->next;
		cur->next=NULL;
		free(del);
	}
}

void PushFront(pList* pHead, DataType x)//头插
{
	assert(pHead);
	pLinkNode cur=*pHead;
	pLinkNode newNode=buyNode(x);
	if(cur==NULL)
	{
		*pHead=newNode;
		return;
	}
	else 
	{
		newNode->next=(*pHead);
		*pHead=newNode;
	}
}

void PopFront(pList* pHead)
{
	assert(pHead);
	if(*pHead==NULL)
	{
		return;
	}
	else 
	{
		pLinkNode del=*pHead;
		*pHead=(*pHead)->next;
		free(del);
		del=NULL;
	}
}

void PrintList(pList list)
{
	pLinkNode cur=list;
	printf("list is:\n");
	while(cur)
	{
		printf("%d->",cur->data);
		cur=cur->next;
	}
	printf("over\n");
}

int GetListLength(pList head)
{
	int count=0;
	assert(head);
	while(head)
	{
		count++;
		head=head->next;
	}
	return count;
}

pLinkNode Find(pList head, DataType x)
{
	pLinkNode cur=head;
	assert(head);
	if(head==NULL)
	{
		return NULL;
	}
	else
	{
		while(cur)
		{
			if(cur->data==x)
			{
				return cur;
			}
			else 
			{
				cur=cur->next;
			}
		}
		return NULL;
	}
}

void Insert(pList *pHead, pLinkNode pos, DataType x)
{
	assert(pHead);
	pLinkNode cur=*pHead;
	pLinkNode newNode=buyNode(x);
	while(cur->next!=pos)
	{
		cur=cur->next;
	}
	newNode->next=cur->next;
	cur->next=newNode;
}

void Remove(pList *pHead, DataType x)
{
	pLinkNode cur=*pHead;
	pLinkNode del=NULL,prev=NULL;
	assert(pHead);
	while(cur)
	{
		if(cur->data==x)
		{
			del=cur;
			if(cur==*pHead)
			{
				*pHead=(*pHead)->next;	
			}
			else
			{
				prev->next=cur->next;
			}
			free(del);
			break;
		}
		prev=cur;
		cur=cur->next;
	}
	del=NULL;
}
void RemoveAll(pList *pHead, DataType x)
{
	pLinkNode cur=*pHead;
	pLinkNode del=NULL,prev=NULL;
	assert(pHead);
	if(cur==NULL)
	{
		return;
	}
	while(cur)
	{
		if(cur->data==x)
		{
			del=cur;
			if(cur==*pHead)
			{
				*pHead=(*pHead)->next;
				cur=*pHead;
			}
			else
			{
				prev->next=cur->next;
				cur=prev->next;
			}
			free(del);
		}
		else
		{
			prev=cur;
			cur=cur->next;
		}
	}
}

void Erase(pLinkNode* pHead,pLinkNode pos)//删除指定位置的结点
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
		free(*pHead);
		*pHead =NULL;
	}
	else
	{
		while(cur->next)
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

//约瑟夫环
pLinkNode JosephCycle(pList* pHead,int num)
{
	pLinkNode cur=*pHead;
	int count=0;
	while(1)
	{
		count=num;
		if(cur->next==cur)
		{
			break;
		}
		while(--count)
		{
			cur=cur->next;
		}
		printf("%d ",cur->data);
		pLinkNode del=cur->next;
		cur->data=cur->next->data;
		cur->next=cur->next->next;
		free(del);
	}
	*pHead=cur;
	return cur;
}

pLinkNode FindMidNode(pList plist)//查找中间结点
{
	pLinkNode fast=plist;
	pLinkNode slow=plist;
	while(fast&&fast->next)
	{
		fast=fast->next->next;
		slow=slow->next;
	}
	return slow;
}

void DelNode(pList plist,int k)//删除链表的第k个结点
{
	assert(k>1);
	pLinkNode l1=plist;
	pLinkNode l2=plist;
	while(--k)
	{
		l1=l1->next;
	}
	while(l1->next)
	{
		l1=l1->next;
		l2=l2->next;
	}
	pLinkNode del=l2->next;
	l2->data=l2->next->data;
	l2->next=l2->next->next;
	free(del);
}

pLinkNode CheckCycle(pList list)//判断链表是否带环
{
	pLinkNode fast=list;
	pLinkNode slow=list;
	while(fast&&fast->next)
	{
		fast=fast->next->next;
		slow=slow->next;
		if(fast==slow)
		{
			return fast;
		}	
	}
	return NULL;
}

int GetCycleLength(pLinkNode meet)//求环的长度
{
	pLinkNode start=meet;
	int count=0;
	do
	{
		start=start->next;
		count++;
	}while(start&&start!=meet);
	return count;
}

pLinkNode GetCycleEnterNode(pList plist,pLinkNode meetNode)//求取带环链表的入口结点
{
	pLinkNode enter=plist;
	pLinkNode meet=meetNode;
	while(enter!=meet)
	{
		enter=enter->next;
		meet=meet->next;
	}
	return enter;
}

int CheckCross(pList list1,pList list2)//判断两个链表是否相交
{
	while(list1 && list1->next)
	{
		list1=list1->next;
	}
	while(list2 && list2->next)
	{
		list2=list2->next;
	}
	if(list1==list2)
	{
		return 1;
	}
	else 
	{
		return 0;
	}
}

pLinkNode _Merge(pList l1,pList l2)//合并单链表的递归算法
{
	if((l1==NULL) && (l2==NULL))
	{
		return NULL;
	}
	else if((l1==NULL)&&(l2!=NULL))
	{
		return l2;
	}
	else if((l1!=NULL)&&(l2==NULL))
	{
		return l1;
	}
	pLinkNode newHead=NULL;
	if(l1->data<l2->data)
	{
		newHead=l1;
		newHead->next=_Merge(l1->next,l2);
	}
	else 
	{
		newHead=l2;
		newHead->next=_Merge(l1,l2->next);
	}
	return newHead;
}

#endif