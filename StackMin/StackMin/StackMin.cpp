#include<iostream>
#include<stack>
using namespace std;

//包含min函数的栈
//在该类型中实现一个能够得到栈的最小元素的min函数，在该函数中调用min、push、pop，其时间复杂度为O(1)
template<class T>
class StackWithMin
{
public:
	void Push(const T& value)//插入
	{
		//先向数据栈中插入数据，然后判断辅助栈或者让该元素比较辅助栈的栈顶元素，若小于栈顶元素，插入该元素，否则插入栈顶元素
		m_data.push(value);
		if(m_min.size() == 0 || value < m_min.top())
			m_min.push(value);
		else
			m_min.push(m_min.top());
	}

	void Pop()//弹出
	{
		if(m_data.size() > 0 && m_min.size() > 0)//当数据栈和辅助栈都不为空时，弹出栈顶元素
		{
			m_data.pop();
			m_min.pop();
		}
	}

	T& Min()//获取当期栈中最小的值
	{
		if(m_data.size() > 0 && m_min.size() > 0)//当数据栈和辅助栈都不为空时，返回辅助栈的栈顶元素
			return m_min.top();
	}
protected:
	stack<T> m_data;//数据栈
	stack<T> m_min;//辅助栈，保存当前栈中的的最小值，每比较一次，插入一次当前栈中最小的元素
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
	cout<<"当前栈的最小值:"<<stack.Min()<<endl;
	system("pause");
	return 0;
}

