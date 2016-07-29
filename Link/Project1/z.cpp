#define _CRT_SECURE_NO_WARNINGS 1
#include"lianbiao.h"

//void test()
//{
//	pLinkNode myLink;
//	pLinkNode pos=NULL;
//	InitLinkList(&myLink);
//	PushFront(&myLink,1);
//	PushFront(&myLink,2);
//	PushFront(&myLink,3);
//	PushFront(&myLink,4);
//	PushFront(&myLink,5);
//	/*PrintList(myLink);
//	RemoveAll(&myLink,3);*/
//	/*pos=FindMidNode(myLink);
//	printf("%d\n",pos->data);*/
//	DelNode(myLink,2);
//	PrintList(myLink);
//}

//void test1()
//{
//	int i=0;
//	pList l1;
//	InitLinkList(&l1);
//	for(i=1;i<=41;i++)
//	{
//		PushBack(&l1,i);
//	}
//	pLinkNode pos=Find(l1,41);
//	pos->next=l1;
//	pos=JosephCycle(&l1,3);
//	printf("%d\n",pos->data);
//}

//void test2()
//{
//	int i=0;
//	pList l1;
//	InitLinkList(&l1);
//	for(i=1;i<=6;i++)
//	{
//		PushBack(&l1,i);
//	}
//	pLinkNode end=Find(l1,6);
//	pLinkNode pos=Find(l1,3);
//	end->next=pos;
//	pos=CheckCycle(l1);
//	printf("%d\n",pos->data);
//	printf("%d\n",GetCycleLength(pos));
//	pos=GetCycleEnterNode(l1,pos);
//	printf("enter=%d ",pos->data);
//}

void test3()
{
	pLinkNode l1,l2;
	pLinkNode pos=NULL;
	InitLinkList(&l1);
	InitLinkList(&l2);
	PushBack(&l1,1);
	PushBack(&l1,3);
	PushBack(&l1,5);
	PushBack(&l2,2);
	PushBack(&l2,4);
	PushBack(&l2,6);
	pos=_Merge(l1,l2);
	PrintList(pos);
}


int main()
{
	test3();
	system("pause");
	return 0;
}