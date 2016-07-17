#include<iostream>
using namespace std;

//��������ڵ�Ľṹ������һ��ָ����һ���ڵ��ָ���⣬������һ��ָ������ڵ��ָ��
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

//��һ����������Ľڵ㣬�������ڵ�ǰ�ڵ�֮��
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

//�ڶ��������ø��Ƴ����Ľڵ��pSibling
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

//��ֳ���������λ�õĽڵ���pNext������������ԭʼ����ż��λ�õĽڵ���pNext�����������ɸ��Ƴ���������
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
