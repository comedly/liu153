#include<iostream>
#include<assert.h>
using namespace std;

//面试题：n个人中有m对朋友，朋友的朋友的朋友......算一个朋友圈，则这n个人中有几个朋友圈？
//利用并查集
//设有n个元素的数组，每个数组元素的位置置-1，即先让其没有相交，然后根据题目中给出的朋友关系，将根节点元素对应的位置减1，将与根节点是好友的元素对应的位置更改为根节点元素，类似的，将所有的关系对应起来，最后数组中负数的个数即为朋友圈的个数。

class UnionFindSet
{
public:
	UnionFindSet(size_t n)//构造函数
		:_set(new int[n])
		,_N(n)
	{
		for(size_t i = 0;i < n;i++)//将开辟的数组的每一位都置为-1
		{
			_set[i] = -1;
		}
	}

	void Union(int root1,int root2)//结合两个根节点
	{
		assert(_set[root1] < 0);
		assert(_set[root2] < 0);
		_set[root1] += _set[root2];
		_set[root2] = root1;
	}

	int FindRoot(int x)//查找一个节点的根节点
	{
		while(_set[x] >= 0)
		{
			x = _set[x];
		}
		return x;
	}

	int count()//计数
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

int Friends(int n,int m,int r[][2])//求朋友圈的个数
{
	assert(r);
	UnionFindSet ufs(n+1);//因为的计数是从1开始的，没有0位置
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
	int r[][2] = {{1,2},{1,3},{4,5}};
	int ret = Friends(5,3,r);
	cout<<"朋友圈的个数："<<ret<<endl;
	system("pause");
	return 0;
}