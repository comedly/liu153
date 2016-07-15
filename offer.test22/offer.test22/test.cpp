#include<iostream>
#include<stack>
using namespace std;

//判断一个序列是否为栈的弹出序列，借助一个辅助栈
bool IsStackPopOrder(const int* pPush,const int* pPop,int nLength)
{
	bool IsPossible = false;
	if(pPush != NULL && pPop != NULL && nLength > 0)
	{
		const int* pNextPush = pPush;//指向下一个压入的数据
		const int* pNextPop = pPop;//指向下一个弹出的数据

		stack<int> stackData;
		while(pNextPop - pPop < nLength)
		{
			//当辅助栈为空或者栈顶元素不等于下一次要弹出的元素，此时需要压入元素，
			while(stackData.empty() || stackData.top() != *pNextPop)
			{
				if(pNextPush - pPush == nLength)//压入序列已压完，则直接结束
					break;
				stackData.push(*pNextPush);
				pNextPush++;
			}
			if(stackData.top() != *pNextPop)
				break;
			stackData.pop();
			pNextPop++;
		}
		if(stackData.empty() && pNextPop - pPop == nLength)//栈为空或弹出序列已经判断完了
			cout<<stackData.empty()<<endl;
			IsPossible = true;
	}
	return IsPossible;
}

int main()
{
	int a[] = {1,2,3,4,5};
	int b[] = {4,5,3,2,1};
	bool result = IsStackPopOrder(a,b,sizeof(a)/sizeof(a[0]));
	cout<<"序列b是否为序列a的弹出序列？"<<result<<endl;
	system("pause");
	return 0;
}