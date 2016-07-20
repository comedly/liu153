#include<iostream>
#include<set>
#include<vector>
#include<assert.h>
using namespace std;

//输入一个数组，输出最小的k个数

//方法一：基于快排的方法,使位于左边的k个数字就是最小的k个数字

//实现一次快排
int Partation(int number[],int length,int left,int right)
{
	if(number == NULL || length <= 0 || left < 0 || right >= length)
		return 0;
	int key = number[right];
	int begin = left;
	int end = right - 1;
	while (begin < end)
	{
		while (begin < end && number[begin] < key)
		{
			begin++;
		}
		while (begin < end && number[end] > key)
		{
			end--;
		}
		if(begin < end)
		{
			swap(number[begin],number[end]);
		}
	}
	if(number[begin] > number[right])
	{
		swap(number[begin],number[right]);
		return begin;
	}
	else
	{
		return right;
	}
	return begin;
}

//求出数组左边的k个数字(左边的k个数不一定是排序的)，并打印
void GetLeastNumbers1(int number[],int length,int k)
{
	if(number == NULL || k > length || length <= 0 || k <= 0)
		return ;
	int start = 0;
	int end = length - 1;
	int index = Partation(number,length,start,end);
	while (index != k-1)
	{
		if(index > k-1)
		{
			end = index - 1;
			index = Partation(number,length,start,end);
		}
		else
		{
			start = index + 1;
			index = Partation(number,length,start,end);
		}
	}
	for(int i = 0;i < k;i++)
	{
		cout<<number[i]<<" ";
	}
	cout<<endl;
}


//方法二:适合于处理海量数据
//建立一个容器可以存储k个数字，如果此容器中的数字没有k个，向其中插入，如果已满，则在插入之前需要查找容器中最大的一个数，将待插入的数与该数进行比较，如果容器中最大的数字大于将插入的数字，则替换，否则不进行插入操作。

//基于STL中的multiset实现
template<class K>
struct greater
{
	bool operator()(const K& l,const K& r)
	{
		return l > r;
	}
};

typedef multiset<int,greater<int> > intSet;
typedef multiset<int,greater<int> >::iterator setIterator;

void GetLeastNumbers2(const vector<int>& data,intSet& leastNumbers,int k)
{
	leastNumbers.clear();
	if(data.size() < k || k < 1)
	{
		return;
	}
	vector<int>::const_iterator iter = data.begin();
	for(;iter != data.end();++iter)
	{
		if(leastNumbers.size() < k)//不足k个元素继续插入
			leastNumbers.insert(*iter);
		else
		{
			setIterator iterGreatest = leastNumbers.begin();
			if(*iter < *(leastNumbers.begin()))//待插入的比leastNumbers中的第一个元素小，则销毁第一个元素，插入待插入的元素
			{
				leastNumbers.erase(iterGreatest);
				leastNumbers.insert(*iter);
			}
		}
	}
	setIterator it = leastNumbers.begin();//打印
	for(;it != leastNumbers.end();it++)
	{
		cout<<*it<<" ";
	}
	cout<<endl;
}

//方法三：适用于海量数据
//利用堆原理，建立一个大堆，因为根节点值最大，将待插入的节点与该节点进行比较，大于根节点，不用插入，小于根节点，则人堆，根节点pass掉
void _AdjustUp(int child, int a[])
{
	assert(a);
	greater<int> Great;
	int parent = (child - 1)/2;

	while (child > 0)//child为0，则为根节点
	{
		if(Great(a[child],a[parent]))
		{
			swap(a[child],a[parent]);
			child = parent;
			parent = (child-1)/2;
		}
		else
		{
			break;
		}
	}
}

void _AdjustDown(int parent,int size,int arr[])//向下调整
	{
		//指向左孩子
		int child = parent*2 + 1; 
		while (child < size)
		{
			greater<int> com;
			//选出左右子节点大的那一个
			if(child+1<size && com(arr[child+1],arr[child]))
			{
				child++;
			}
			//如果子>父，则交换，并继续往下调整
			if(com(arr[child],arr[parent]))
			{
				swap(arr[child],arr[parent]);
				parent = child;
				child = parent*2+1;
			}
			else
			{
				break;
			}
		}
	}

void GetLeastNumbers3(int* number,int N,int K)
{
	assert(number);
	assert(K > 0);
	//开辟一块新的空间来保存这K个数
	int* arr = new int[K];
	for(int i = 0;i < K;i++)
	{
		arr[i] = number[i];
		//_AdjustUp(i,arr);
	}
	
	//建堆
	for(int i = (K-2)/2;i>=0;i--)
	{
		_AdjustDown(i,K,arr);
	}

	//对剩余的N-K个数据进行比较
	for(int i = K;i < N;i++)
	{
		if(arr[0] > number[i])
		{
			arr[0] = number[i];
			_AdjustDown(0,K,arr);
		}
	}
	//打印最小的k个数字
	for(int i = 0; i < K;i++)
	{
		cout<<arr[i]<<" ";
	}
	cout<<endl;
}

int main()
{
	vector<int> vec;
	intSet least;

	int a[] = {6,10,7,11,5,8,9};

	GetLeastNumbers1(a,sizeof(a)/sizeof(a[0]),4);//法1

	for(int i = 0;i < sizeof(a)/sizeof(a[0]);i++)
	{
		vec.push_back(a[i]);
	}
	for(int j = 0;j < 4;j++)
	{
		least.insert(a[j]);
	}
	GetLeastNumbers2(vec,least,4);//法2

	GetLeastNumbers3(a,sizeof(a)/sizeof(a[0]),4);//法3
	system("pause");
	return 0;
}