#include<iostream>
#include<set>
#include<vector>
#include<assert.h>
using namespace std;

//����һ�����飬�����С��k����

//����һ�����ڿ��ŵķ���,ʹλ����ߵ�k�����־�����С��k������

//ʵ��һ�ο���
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

//���������ߵ�k������(��ߵ�k������һ���������)������ӡ
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


//������:�ʺ��ڴ���������
//����һ���������Դ洢k�����֣�����������е�����û��k���������в��룬������������ڲ���֮ǰ��Ҫ��������������һ�������������������������бȽϣ�����������������ִ��ڽ���������֣����滻�����򲻽��в��������

//����STL�е�multisetʵ��
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
		if(leastNumbers.size() < k)//����k��Ԫ�ؼ�������
			leastNumbers.insert(*iter);
		else
		{
			setIterator iterGreatest = leastNumbers.begin();
			if(*iter < *(leastNumbers.begin()))//������ı�leastNumbers�еĵ�һ��Ԫ��С�������ٵ�һ��Ԫ�أ�����������Ԫ��
			{
				leastNumbers.erase(iterGreatest);
				leastNumbers.insert(*iter);
			}
		}
	}
	setIterator it = leastNumbers.begin();//��ӡ
	for(;it != leastNumbers.end();it++)
	{
		cout<<*it<<" ";
	}
	cout<<endl;
}

//�������������ں�������
//���ö�ԭ������һ����ѣ���Ϊ���ڵ�ֵ��󣬽�������Ľڵ���ýڵ���бȽϣ����ڸ��ڵ㣬���ò��룬С�ڸ��ڵ㣬���˶ѣ����ڵ�pass��
void _AdjustUp(int child, int a[])
{
	assert(a);
	greater<int> Great;
	int parent = (child - 1)/2;

	while (child > 0)//childΪ0����Ϊ���ڵ�
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

void _AdjustDown(int parent,int size,int arr[])//���µ���
	{
		//ָ������
		int child = parent*2 + 1; 
		while (child < size)
		{
			greater<int> com;
			//ѡ�������ӽڵ�����һ��
			if(child+1<size && com(arr[child+1],arr[child]))
			{
				child++;
			}
			//�����>�����򽻻������������µ���
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
	//����һ���µĿռ���������K����
	int* arr = new int[K];
	for(int i = 0;i < K;i++)
	{
		arr[i] = number[i];
		//_AdjustUp(i,arr);
	}
	
	//����
	for(int i = (K-2)/2;i>=0;i--)
	{
		_AdjustDown(i,K,arr);
	}

	//��ʣ���N-K�����ݽ��бȽ�
	for(int i = K;i < N;i++)
	{
		if(arr[0] > number[i])
		{
			arr[0] = number[i];
			_AdjustDown(0,K,arr);
		}
	}
	//��ӡ��С��k������
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

	GetLeastNumbers1(a,sizeof(a)/sizeof(a[0]),4);//��1

	for(int i = 0;i < sizeof(a)/sizeof(a[0]);i++)
	{
		vec.push_back(a[i]);
	}
	for(int j = 0;j < 4;j++)
	{
		least.insert(a[j]);
	}
	GetLeastNumbers2(vec,least,4);//��2

	GetLeastNumbers3(a,sizeof(a)/sizeof(a[0]),4);//��3
	system("pause");
	return 0;
}