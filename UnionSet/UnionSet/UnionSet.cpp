#include<iostream>
#include<assert.h>
using namespace std;

//�����⣺n��������m�����ѣ����ѵ����ѵ�����......��һ������Ȧ������n�������м�������Ȧ��
//���ò��鼯
//����n��Ԫ�ص����飬ÿ������Ԫ�ص�λ����-1����������û���ཻ��Ȼ�������Ŀ�и��������ѹ�ϵ�������ڵ�Ԫ�ض�Ӧ��λ�ü�1��������ڵ��Ǻ��ѵ�Ԫ�ض�Ӧ��λ�ø���Ϊ���ڵ�Ԫ�أ����Ƶģ������еĹ�ϵ��Ӧ��������������и����ĸ�����Ϊ����Ȧ�ĸ�����

class UnionFindSet
{
public:
	UnionFindSet(size_t n)//���캯��
		:_set(new int[n])
		,_N(n)
	{
		for(size_t i = 0;i < n;i++)//�����ٵ������ÿһλ����Ϊ-1
		{
			_set[i] = -1;
		}
	}

	void Union(int x1,int x2)//����������ڵ�
	{
		int root1 = FindRoot(x1);
		int root2 = FindRoot(x2);
		if(root1 != root2)
		{
			_set[root1] += _set[root2];
			_set[root2] = root1;
		}
	}

	int FindRoot(int x)//����һ���ڵ�ĸ��ڵ�
	{
		while(_set[x] >= 0)
		{
			x = _set[x];
		}
		return x;
	}

	int count()//����
	{
		int count = 0;
		for(size_t i = 0;i < _N;++i)
		{
			if(_set[i] < 0)
			{
				count++;
			}
		}
		return count;
	}
protected:
	int* _set;
	size_t _N;
};

int Friends(int n,int m,int r[][2])//������Ȧ�ĸ���
{
	assert(r);
	UnionFindSet ufs(n+1);//��Ϊ�ļ����Ǵ�1��ʼ�ģ�û��0λ��
	for(size_t i = 0;i < m;++i)
	{
		int r1 = r[i][0];
		int r2 = r[i][1];
		ufs.Union(r1,r2);
	}
	return ufs.count()-1;
}

int main()
{
	int r[][2] = {{1,2},{1,3},{1,5},{4,5}};
	int ret = Friends(5,4,r);
	cout<<"����Ȧ�ĸ�����"<<ret<<endl;
	system("pause");
	return 0;
}