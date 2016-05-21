#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stack>

typedef int DataType;

typedef struct LinkNode
{
	DataType data;//
	struct LinkNode* next;//ָ���������һ�����
}LinkNode,*pLinkNode,*pLinkList;

void InitLinkList(pLinkList* pHead)//��ʼ��������
{
	assert(pHead);
	*pHead = NULL;
}

void Destory(pLinkList* pHead) //���ٵ�����
{
	if(*pHead == NULL)
		return;
	else
	{
		pLinkNode cur = *pHead;
		while (cur)  //����ɾ��������Ľ��
		{
			pLinkNode del = cur;
			cur = cur->next;
			free(del);
			del = NULL;
		}
	}
}

void HeadToTailPrintList(pLinkList* pHead) //��ͷ��β��ӡ����
{
	pLinkNode cur = *pHead;
	while (cur)
	{
		printf("%d  ",cur->data);
		cur = cur->next;
	}
	printf("over\n");
}

void TailToHeadPrintList1(pLinkList pHead)//��β����ͷ��ӡ������
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

void TailToHeadPrintList2(pLinkList pHead)//��Ϊ�ݹ鱾�����һ��ջ�Ľṹ�����ǻ��ڵݹ�ʵ�ַ����ӡ
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

pLinkNode BuyNode(DataType x)//����һ�����
{
	pLinkNode NewNode = (pLinkNode)malloc(sizeof(LinkNode));
	NewNode->data = x;
	NewNode->next = NULL;
	return NewNode;
}

void PushBack(pLinkList* pHead,DataType x)//β������
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

void PopBack(pLinkList* pHead)//βɾ
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

void PushFront(pLinkList* pHead,DataType x)//ͷ��
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

void PopFront(pLinkList* pHead)//ͷɾ
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

void InsertList(pLinkList* pHead,pLinkNode pos,DataType x)//��pos��ָ��Ľ��ǰ����һ�����
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

int GetListLength(pLinkList* pHead)//����ĳ���
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

pLinkNode Find(pLinkList* pHead,DataType x)//����
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

pLinkNode FindKToTail(pLinkNode pHead,unsigned int k)//����������k�����
//��������ָ�붼ָ��ͷ��㣬��һ��ָ������k-1��������ָ��ͬʱ�ߣ�����һ��ָ��ָ�����һ�����ʱ���ڶ���ָ��ָ������k�����
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

void Remove1(pLinkList* pHead,DataType x)//����Find��������ɾ�����
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

void Remove2(pLinkList* pHead,DataType x)//����Ҫ����Find����������һ��ָ��ǰ����ָ��
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

void RemoveAll(pLinkList* pHead,DataType x)//ɾ��������ͬ�Ľ��
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

void Erase(pLinkList* pHead,pLinkNode pos)//ɾ��ָ��λ�õĽ��
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

void EraseNotTail(pLinkNode pos)//ɾ����ͷ�ķ�β���
{
	pLinkNode del = pos->next;
	pos->data = del->data;
	pos->next = del->next;
	free(del);
	del = NULL;
}

void ReverseList(pLinkList* pHead)//���������
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

void BubbleSort(pLinkList* pHead)//ð������
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

void InsertFrontNode(pLinkNode pos,DataType x)//��ͷ��������£��ٵ�ǰ���ǰ����һ������
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

pLinkNode Merge(pLinkList l1,pLinkList l2)//�ǵݹ鷨ʵ��������������ĺϲ�
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

pLinkNode _Merge(pLinkList l1,pLinkList l2)//���ڵݹ�ʵ��������������ĺϲ�
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

pLinkNode FindMidNode(pLinkList* pHead)//����������м���
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

void DelKNode(pLinkList *pHead,int k)//ɾ��������ĵ�����k��k>1�������
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

pLinkNode JosephCycle(pLinkList* pHead,int num)//Լɪ��
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

//�����������
pLinkNode CheckCycle(pLinkList plist)//�ж������Ƿ����
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

int GetCircleLength(pLinkNode meet)//���������󻷵ĳ���
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

pLinkNode GetCycleEntryNode(pLinkList plist,pLinkNode meetNode)//��ȡ������ڽ��
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
