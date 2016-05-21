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

int main()
{
	//Test1();
	Test2();
	system("pause");
	return 0;
}