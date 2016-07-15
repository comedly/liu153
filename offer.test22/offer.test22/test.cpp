#include<iostream>
#include<stack>
using namespace std;

//�ж�һ�������Ƿ�Ϊջ�ĵ������У�����һ������ջ
bool IsStackPopOrder(const int* pPush,const int* pPop,int nLength)
{
	bool IsPossible = false;
	if(pPush != NULL && pPop != NULL && nLength > 0)
	{
		const int* pNextPush = pPush;//ָ����һ��ѹ�������
		const int* pNextPop = pPop;//ָ����һ������������

		stack<int> stackData;
		while(pNextPop - pPop < nLength)
		{
			//������ջΪ�ջ���ջ��Ԫ�ز�������һ��Ҫ������Ԫ�أ���ʱ��Ҫѹ��Ԫ�أ�
			while(stackData.empty() || stackData.top() != *pNextPop)
			{
				if(pNextPush - pPush == nLength)//ѹ��������ѹ�꣬��ֱ�ӽ���
					break;
				stackData.push(*pNextPush);
				pNextPush++;
			}
			if(stackData.top() != *pNextPop)
				break;
			stackData.pop();
			pNextPop++;
		}
		if(stackData.empty() && pNextPop - pPop == nLength)//ջΪ�ջ򵯳������Ѿ��ж�����
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
	cout<<"����b�Ƿ�Ϊ����a�ĵ������У�"<<result<<endl;
	system("pause");
	return 0;
}