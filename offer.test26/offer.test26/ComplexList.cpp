#include<iostream>
using namespace std;

//复杂链表节点的结构，除了一个指向下一个节点的指针外，还多了一个指向任意节点的指针
struct ComplexListNode
{
	ComplexListNode()
		:pNext(NULL)
		,pSibling(NULL)
	{ }
	ComplexListNode(const int& x)
		:pData(x)
		,pNext(NULL)
		,pSibling(NULL)
	{ }
	int pData;
	ComplexListNode* pNext;
	ComplexListNode* pSibling;
};

//第一步复制链表的节点，并连接在当前节点之后
void CloneNode(ComplexListNode* pHead)
{
	ComplexListNode* pNode = pHead;
	while(pNode != NULL)
	{
		ComplexListNode* pCloneNode = new ComplexListNode();
		pCloneNode->pData = pNode->pData;
		pCloneNode->pNext = pNode->pNext;
		pCloneNode->pSibling = NULL;
		pNode->pNext = pCloneNode;

		pNode = pCloneNode->pNext;
	}
}

//第二步，设置复制出来的节点的pSibling
void ConnectCloneNode(ComplexListNode* pHead)
{
	ComplexListNode* pNode = pHead;
	while (pNode != NULL)
	{
		ComplexListNode* pClone = pNode->pNext;
		if(pNode->pSibling != NULL)
		{
			pClone->pSibling = pNode->pSibling->pNext;
		}
		pNode = pClone->pNext;
	}
}

//拆分长链表，奇数位置的节点用pNext连接起来构成原始链表，偶数位置的节点用pNext连接起来构成复制出来的链表。
ComplexListNode* ReconnectNodes(ComplexListNode* pHead)
{
	ComplexListNode* pNode = pHead;
	ComplexListNode* pClonedHead = NULL;
	ComplexListNode* pClonedNode = NULL;
	if(pNode != NULL)
	{
		pClonedHead = pClonedNode = pNode->pNext;
		pNode->pNext = pClonedNode->pNext;
		pNode = pNode->pNext;
	}

	while (pNode != NULL)
	{
		pClonedNode->pNext = pNode->pNext;
		pClonedNode = pClonedNode->pNext;
		pNode->pNext = pClonedNode->pNext;
		pNode = pNode->pNext;
	}

	return pClonedHead;
}

ComplexListNode* Clone(ComplexListNode* pHead)
{
	CloneNode(pHead);
	ConnectCloneNode(pHead);
	return ReconnectNodes(pHead);
}

int main()
{
	ComplexListNode List1(1);
	ComplexListNode List2(2);
	ComplexListNode List3(3);
	ComplexListNode List4(4);
	ComplexListNode List5(5);

	List1.pNext = &List2;
	List2.pNext = &List3;
	List3.pNext = &List4;
	List4.pNext = &List5;

	List1.pSibling = &List3;
	List2.pSibling = &List5;
	List4.pSibling = &List2;

	ComplexListNode* NewHead = Clone(&List1);
	system("pause");
	return 0;
}
