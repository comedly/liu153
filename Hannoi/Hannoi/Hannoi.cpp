#include<fstream>
#include<iostream>
using namespace std;

//递归实现汉诺塔问题，假设有10层

ofstream fout("out.txt");

void Move(int n,char i,char j)
{
	fout<<"把"<<n<<"号从"<<i<<"移动到"<<j<<endl;
}

void Hannoi_R(int n,char a,char b,char c)
{
	if(n == 1)
	{
		Move(1,a,c);
	}
	else
	{
		Hannoi_R(n-1,a,c,b);
		Move(n,a,c);
		Hannoi_R(n-1,b,a,c);
	}
}

//int main()
//{
//	fout<<"以下是10层汉诺塔的解法："<<endl;
//	Hannoi_R(10,'a','b','c');
//	fout.close();
//	cout<<"输出结果完毕！"<<endl;
//	return 0;
//}

//非递归实现汉诺塔
const int Max = 10;

struct  st
{
	int s[Max];
	int top;//栈顶，用来存储最上边的圆盘
	char name;//柱子的名称，可以是A,B,C

	int Top()//取栈顶元素
	{
		return s[top];
	}

	int Pop()//出栈
	{
		return s[top--];
	}

	void Push(int x)//入栈
	{
		s[++top] = x;
	}
};

long Pow(int x,int y)
{
	long sum = 1;
	for(int i = 0;i < y;i++)
	{
		sum *= x;
	}
	return sum;
}

void Creat(st ta[],int n)
{
	ta[0].name = 'A';
	ta[0].top = n-1;
	for(int i = 0;i < n;i++)
	{
		ta[0].s[i] = n - i;
		ta[1].top = ta[2].top = 0;
	}

	for(int i = 0;i < n;i++)
	{
		ta[i].top = ta[2].s[i] = 0;
	}

	if(n%2 == 0)//如果n为偶数，按顺时针方向依次摆放A B C
	{
		ta[1].name = 'B';
		ta[2].name = 'C';
	}
	else
	{
		ta[1].name = 'C';
		ta[2].name = 'B';
	}
}

void Hannoi(st ta[],long max)
{
	int k = 0;
	int i = 0;
	int ch;
	while (k < max)
	{
		ch = ta[i%3].Pop();
		ta[(i+1)%3].Push(ch);
		cout<<++k<<": "<<"Move disk"<<ch<<"from"<<ta[i%3].name<<"to"<<ta[(i+1)%3].name<<endl;
		i++;
		if(k < max)
		{
			if(ta[(i+1)%3].Top() == 0 || ta[(i-1)%3].Top() > 0 && ta[(i+1)%3].Top()>ta[(i-1)%3].Top())
			{
				ch = ta[(i-1)%3].Pop();
				ta[(i+1)%3].Push(ch);
				cout<<++k<<": "<<"Move disk"<<ch<<"from"<<ta[(i-1)%3].name<<"to"<<ta[(i+1)%3].name<<endl;
			}
			else
			{
				ch = ta[(i+1)%3].Pop();
				ta[(i-1)%3].Push(ch);
				cout<<++k<<": "<<"Move disk"<<ch<<"from"<<ta[(i+1)%
3].name<<"to"<<ta[(i-1)%3].name<<endl;
			}
		}
	}
}

int main()
{
	int n;
	cin>>n;//输如圆盘的个数
	st ta[3];//3根柱子的信息用结构数组存储
	Creat(ta,n);//给结构数组设置初值
	long max = Pow(2,n)-1;//移动的次数应该等于2^n - 1
	Hannoi(ta,max);
	system("pause");
	return 0;
}



