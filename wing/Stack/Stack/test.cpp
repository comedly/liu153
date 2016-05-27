#include"Stack.h"

void Test()
{
	Stack<int> st;
	st.Push(1);
	st.Push(2);
	st.Push(3);
	st.Push(4);

}

void TestcQueue()
{
	Cqueue<int> qu;
	qu.AppendTail(1);
	qu.AppendTail(2);
	qu.AppendTail(3);
	qu.AppendTail(4);
	qu.AppendTail(5);
	qu.DeleteHead();
	qu.AppendTail(8);
	cout<<endl;
	qu.DeleteHead();
}

int main()
{
	Test();
	TestcQueue();
	system("pause");
	return 0;
}