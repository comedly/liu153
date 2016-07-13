#include<iostream>
#include<stack>
using namespace std;

//����min������ջ
//�ڸ�������ʵ��һ���ܹ��õ�ջ����СԪ�ص�min�������ڸú����е���min��push��pop����ʱ�临�Ӷ�ΪO(1)
template<class T>
class StackWithMin
{
public:
	void Push(const T& value)//����
	{
		//��������ջ�в������ݣ�Ȼ���жϸ���ջ�����ø�Ԫ�رȽϸ���ջ��ջ��Ԫ�أ���С��ջ��Ԫ�أ������Ԫ�أ��������ջ��Ԫ��
		m_data.push(value);
		if(m_min.size() == 0 || value < m_min.top())
			m_min.push(value);
		else
			m_min.push(m_min.top());
	}

	void Pop()//����
	{
		if(m_data.size() > 0 && m_min.size() > 0)//������ջ�͸���ջ����Ϊ��ʱ������ջ��Ԫ��
		{
			m_data.pop();
			m_min.pop();
		}
	}

	T& Min()//��ȡ����ջ����С��ֵ
	{
		if(m_data.size() > 0 && m_min.size() > 0)//������ջ�͸���ջ����Ϊ��ʱ�����ظ���ջ��ջ��Ԫ��
			return m_min.top();
	}
protected:
	stack<T> m_data;//����ջ
	stack<T> m_min;//����ջ�����浱ǰջ�еĵ���Сֵ��ÿ�Ƚ�һ�Σ�����һ�ε�ǰջ����С��Ԫ��
};

int main()
{
	StackWithMin<int> stack;
	stack.Push(3);
	stack.Push(4);
	stack.Push(1);
	stack.Push(5);
	stack.Push(2);
	stack.Pop();
	stack.Pop();
	stack.Pop();
	cout<<"��ǰջ����Сֵ:"<<stack.Min()<<endl;
	system("pause");
	return 0;
}

