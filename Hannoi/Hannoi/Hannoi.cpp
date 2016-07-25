#include<fstream>
#include<iostream>
using namespace std;

//�ݹ�ʵ�ֺ�ŵ�����⣬������10��

ofstream fout("out.txt");

void Move(int n,char i,char j)
{
	fout<<"��"<<n<<"�Ŵ�"<<i<<"�ƶ���"<<j<<endl;
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
//	fout<<"������10�㺺ŵ���Ľⷨ��"<<endl;
//	Hannoi_R(10,'a','b','c');
//	fout.close();
//	cout<<"��������ϣ�"<<endl;
//	return 0;
//}

//�ǵݹ�ʵ�ֺ�ŵ��
const int Max = 10;

struct  st
{
	int s[Max];
	int top;//ջ���������洢���ϱߵ�Բ��
	char name;//���ӵ����ƣ�������A,B,C

	int Top()//ȡջ��Ԫ��
	{
		return s[top];
	}

	int Pop()//��ջ
	{
		return s[top--];
	}

	void Push(int x)//��ջ
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

	if(n%2 == 0)//���nΪż������˳ʱ�뷽�����ΰڷ�A B C
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
	cin>>n;//����Բ�̵ĸ���
	st ta[3];//3�����ӵ���Ϣ�ýṹ����洢
	Creat(ta,n);//���ṹ�������ó�ֵ
	long max = Pow(2,n)-1;//�ƶ��Ĵ���Ӧ�õ���2^n - 1
	Hannoi(ta,max);
	system("pause");
	return 0;
}



