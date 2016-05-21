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

}