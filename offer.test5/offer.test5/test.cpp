#include"Link.h"

void Test1()
{
	pLinkList mylist;
	InitLinkList(&mylist);
	PushBack(&mylist,1);
	PushBack(&mylist,2);
	PushBack(&mylist,3);
	PushBack(&mylist,4);
	HeadToTailPrintList(&mylist);
	TailToHeadPrintList1(mylist);
	TailToHeadPrintList2(mylist);
	printf("%d\n",FindKToTail(mylist,1)->data);
	PopBack(&mylist);
	HeadToTailPrintList(&mylist);
	PushFront(&mylist,5);
	PushFront(&mylist,6);
	HeadToTailPrintList(&mylist);
	PopFront(&mylist);
	HeadToTailPrintList(&mylist);
}

void Test2()
{
	pLinkList mylist;
	InitLinkList(&mylist);
	PushBack(&mylist,1);
	PushBack(&mylist,2);
	PushBack(&mylist,3);
	PushBack(&mylist,4);
	PushBack(&mylist,5);
	HeadToTailPrintList(&mylist);
	printf("%d\n",FindMidNode(&mylist)->data);
	ReverseList(&mylist);
	HeadToTailPrintList(&mylist);
}

void Test3()
{
	pLinkList mylist;
	pLinkNode pos = NULL;
	int i = 0;
	InitLinkList(&mylist);
	for(i = 1;i <= 41;i++)//¹¹½¨»·
	{
		PushBack(&mylist,i);
	}
	pos = Find(&mylist,41);
	pos->next = mylist;
	pos = JosephCycle(&mylist,3);
	printf("%d\n",pos->data);
}

int main()
{
	//Test1();
	//Test2();
	Test3();
	system("pause");
	return 0;
}