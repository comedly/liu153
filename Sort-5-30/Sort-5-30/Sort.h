#pragma once
#include<iostream>
#include<assert.h>
#include<stack>
using namespace std;


void Print(int* a,int size)//��ӡ
{
	for(int i = 0;i < size;i++)
	{
		cout<<a[i]<<" ";
	}
	cout<<endl;
}

void InsertSort(int* a,int size)//��������
{
	assert(a);
	for(int begin = 0;begin < size;begin++)
	{
		//ѡȡ��һ�����֣�������Ϊ�����������õڶ��������һ�����Ƚϣ�С�ڵ�һ�����򽻻�����֮�õ���������ǰ�������ź��������ĵڶ������Ƚϣ���С���򽻻������ø������һ�������бȽϣ����õ��ĸ�����ǰ�����ź��������Ӻ���ǰ�Ƚϣ��Դ�����
		int temp = a[begin];
		int end = begin - 1;
		while (end >= 0 && temp < a[end])
		{
			a[end + 1] = a[end];
			a[end] = temp;
			end--;
		}
	}
}

void TestInsertSort()
{
	int a[] = {2,5,1,4,9,8,0,3,6,7};
	int size = sizeof(a)/sizeof(a[0]);
	InsertSort(a,size);
	Print(a,size);
}

//ϣ������
void ShellSort(int* a,int size)
{
	assert(a);
	int gap = size;
	while (gap > 1)
	{
		gap = gap/3 + 1;
		for(int i = 0;i < size - gap;i++)
		{
			int end = i;
			int temp = a[end + gap];
			while (end >= 0 && temp < a[end])
			{
				a[end + gap] = a[end];
				a[end] = temp;
				end -= gap;
			}
		}

	}
}

void TestShellSort()
{
	int a[] = {2,5,1,4,9,8,0,3,6,7};
	int size = sizeof(a)/sizeof(a[0]);
	ShellSort(a,size);
	Print(a,size);
}

//ѡ������
void SelectSort(int* a,int size)
{
	assert(a);
	for (int i = 0; i < size; i++)
	{
		int minnum = i;//minnum��¼����һ��������С����λ�����±꣬
		for(int j = i + 1;j < size;j++)
		{
			if(a[minnum] > a[j])
			{
				minnum = j;
			}
		}
		if(i != minnum)//���i������minnum������Ҫ�����±�Ϊminnum��i��Ӧ��������С�������Ƶ�ǰ��ȥ
		{
			swap(a[i],a[minnum]);
		}
	}
}

void TestSelectSort()
{
	int a[] = {2,5,1,4,7,8,0,3,6,9};
	int size = sizeof(a)/sizeof(a[0]);
	SelectSort(a,size);
	Print(a,size);
}

//������
void AdjustDown(int parent,int* a,int size)//����
{
	int child = 2*parent + 1;
	while (child < size)
	{
		if(child + 1 <size && a[child + 1] > a[child])
			child++;
		if(a[child] > a[parent])
		{
			swap(a[child],a[parent]);
			parent = child;
			child = 2*parent +1;
		}
		else
		{
			break;
		}
	}
}

void HeapSort(int* a,int size)
{
	assert(a);
	for(int i = (size - 2)/2;i >= 0;i--)
	{
		AdjustDown(i,a,size);
	}
	for(int i = 0;i < size - 1;i++)//����дi<size,��ʱ���һ��i = size-1;size-i-1����0��a[0]��Ҫ��a[0]�ڽ���һ�Σ���д��i<size-1ʱ�ɼ���һ��ѭ�������Ч�� 
	{
		swap(a[0],a[size - i - 1]);
		AdjustDown(0,a,size - i - 1);
	}
}

void TestHeapSort()
{
	int a[] = {2,5,1,4,7,8,0,3,6,9};
	int size = sizeof(a)/sizeof(a[0]);
	HeapSort(a,size);
	Print(a,size);
}

//ð������
void BubbleSort(int* a,int size)
{
	assert(a);
	for(int i = 0;i < size;i++)
	{
		for(int j = 0;j < size - i - 1;j++)
		{
			if(a[j] > a[j+1])
			{
				swap(a[j],a[j+1]);
			}
		}
	}
}

void TestBubbleSort()
{
	int a[] = {2,5,1,4,7,8,0,3,6,9};
	int size = sizeof(a)/sizeof(a[0]);
	BubbleSort(a,size);
	Print(a,size);
}

//��������
//����1��
//ѡ��һ��keyֵ��һ��ѡͷԪ�أ�����βԪ�أ�����ѡ�����һ������������ָ��һ��ָ���һ������һ��ָ�����ڶ�������ǰ���ѡ��key��ģ��Ӻ���ǰѡ��keyС�ģ����н�����

int PartSort(int* a,int left,int right)
{
	assert(a);
	int key = a[right];//����keyֵΪ���һ��Ԫ��
	int begin = left;
	int end = right - 1;
	while (begin < end)
	{
		while (begin < end && a[begin] <= key)//���ұ�key���Ԫ��
		{
			++begin;
		}
		while (begin < end && a[end] >= key)//���ұ�keyС��Ԫ��
		{
			--end;
		}
		if(begin < end)
		{
			swap(a[begin],a[end]);
		}
	}
	if(a[begin] > a[right])//ֻ������Ԫ��
	{
		swap(a[begin],a[right]);
		return begin;
	}
	else
	{
		return right;
	}
	return begin;
}

//����2���ڿӷ�
//���ұߵ�Ԫ����key������������ʱ���һ��λ�����൱��һ���ӣ�����ָ���ҵ��ı�key������ݱ��浽֮ǰkey��λ���ϣ���ʱ��ָ��ָ���λ���൱��һ���ӣ��ٽ���ָ���ҵ��ı�keyС�����ݷŵ����У���ָ��ָ���λ���൱��һ���ӣ��Դ����ƣ�����ָ������ʱ����keyֵ�������У���ʱ��ߵ����ݶ�С��keyֵ���ұߵ����ݶ�����key��

//��ѡȡ��������������С��Ԫ����Ϊkeyֵ����ʱ�����������������������ȡ�з�������Ч�Ľ���������⣬ȡ������ͷԪ�ء�βԪ�ء����м�Ԫ�ص����м��С��������Ϊkeyֵ�����ܹ������������

int GetMidIndex(int* a,int left,int right)
{
	assert(a);
	int mid = (left + right)/2;
	if(a[left] < a[right])
	{
		if(a[mid] < a[left])
		{
			return left;
		}
		else if(a[mid] > a[right])
		{
			return right;
		}
		else
		{
			return mid;
		}
	}
	else
	{
		if(a[mid] < a[right])
		{
			return right;
		}
		else if(a[mid] > a[left])
		{
			return left;
		}
		else
		{
			return mid;
		}
	}
}

//�ڿӷ�
int PartSort1(int* a,int left,int right)
{
	int index = GetMidIndex(a,left,right);
	swap(a[index],a[right]);//���м�����������ұߵ����ݽ��н����������ұߵ����ݸ�ֵ��key��
	int key = a[right];
	int begin = left;
	int end = right;
	while (begin < end)
	{
		while (begin < end && a[begin] <= key)
		{
			++begin;
		}
		a[end] = a[begin];
		while (begin < end && a[end] >= key)
		{
			--end;
		}
		a[begin] = a[end];
	}
	if(begin == end)
	{
		a[end] = key;
		return begin;
	}
}

//����3��
//ѡ�����ұߵ�Ԫ��Ϊkey����curָ��ָ�������ͷԪ�أ�cur���ҽ�keyС��Ԫ�أ�prevָ��ָ��cur-1��λ�ã���cur�ҵ���С��Ԫ�أ��Ƚ���prev++������ʱcur==prev��cur�������ҽ�keyֵС��Ԫ�أ�ֱ��cur��=prev����a[prev]��a[cur],ֱ��curָ������ĵ����ڶ���Ԫ�أ���ʱ��key��a[++prev]������

int PartSort2(int* a,int left,int right)
{
	assert(a);
	int key = a[right];
	int cur = left;
	int prev = left - 1;
	while (cur < right)
	{
		if(a[cur] < key && ++prev != cur)
		{
			swap(a[cur],a[prev]);
		}
		++cur;
	}
	swap(a[right],a[++prev]);
	return prev;
}

void QuickSort1(int* a,int left,int right)
{
	assert(a);
	if(left >= right)
	{
		return ;
	}
	//int div = PartSort(a,left,right);
	//int div = PartSort1(a,left,right);
	int div = PartSort2(a,left,right);
	QuickSort1(a,left,div-1);
	QuickSort1(a,div+1,right);
}

//�Ż���
//������<13,���ò�������Ч�ʻ���ڿ��ţ��ܼ��ٳ���ѹջ�Ŀ���
void QuickSort2(int* a,int left,int right)
{
	assert(a);
	if(left > right)
		return;
	int gap = right - left + 1;
	if(gap < 13)
	{
		InsertSort(a,gap);
	}
	int ret = PartSort1(a,left,right);
	QuickSort2(a,left,ret - 1);
	QuickSort2(a,ret + 1,right);
}

//����ջʵ�ַǵݹ��������
void QuickSort_NonR(int* a,int left,int right)
{
	assert(a);
	stack<int> s;
	if(left < right)//��left < rightʱ֤����Ҫ��������ݸ�������1
	{
		s.push(left);
		s.push(right);
	}
	while (!s.empty())
	{
		int end = s.top();
		s.pop();
		int begin = s.top();
		s.pop();
		if(end - begin < 13)
		{
			InsertSort(a,begin - end + 1);
		}
		else
		{
			int div = PartSort1(a,begin,end);
			if(begin < div - 1)
			{
				s.push(begin);
				s.push(div - 1);	
			}
			if(div + 1 < end)
			{
				s.push(div + 1);
				s.push(end);
			}
		}
	}
}

void TestQuickSort()
{
	int a[] = {2,9,1,4,7,8,0,3,6,5,45,12,32,17};
	int size = sizeof(a)/sizeof(a[0]);
	//QuickSort1(a,0,9);
	//QuickSort2(a,0,9);
	QuickSort_NonR(a,0,size - 1);
	Print(a,size);
}

//�鲢����
//��Ҫ˼�룺��ϲ��������������㷨���ƣ���Ҫ����һ��O(N)�Ŀռ䣬��һ�������Ԫ�ط�Ϊ�����֣������������ֶ��ܹ����������úϲ���˼����кϲ����������õݹ顣

void _Merge(int* a,int* temp,int begin1,int end1,int begin2,int end2)
{
	int index = begin1;   //�������temp������±�
	while (begin1 <= end1 && begin2 <= end2)
		//���ж�begin1��begin2�Ĵ�С��Ȼ��С�����ݴ�begin��end������temp��
		//��ѭ��������begin1 >= end1 || begin2 >= end2
	{
		if(a[begin1] < a[begin2])
		{
			temp[index++] = a[begin1++];
		}
		else
		{
			temp[index++] = a[begin2++];
		}
	}
	//��ʣ�µ�begin1����begin2�ٽ��п���
	while (begin1 <= end1)
	{
		temp[index++] = a[begin1++];
	}
	while (begin2 <= end2)
	{
		temp[index++] = a[begin2++];
	}
}

void _MergeSort(int* a,int* temp,int left,int right)
{
	if(left < right)
	{
		int mid = (left + right)/2;
		_MergeSort(a,temp,left,mid);
		_MergeSort(a,temp,mid + 1,right);
		_Merge(a,temp,left,mid,mid + 1,right);//����temp��������
		for(int i = left;i <= right;++i)
		{
			a[i] = temp[i];
		}
	}
}

void MergeSort(int* a,int size) //�鲢��������
{
	assert(a);
	int* temp = new int[size];//����N���ռ�
	int left = 0;
	int right = size - 1;
	_MergeSort(a,temp,left,right);
	delete[] temp;
}

void TestMergeSort()
{
	int a[] = {2,9,1,4,7,8,0,3,6,5,45,12,32,17};
	int size = sizeof(a)/sizeof(a[0]);
	MergeSort(a,size);
	Print(a,size);
}

//��������
//��Ҫͳ�ƴ�����ʹ��ֱ�Ӷ�ַ����ͳ�����������С������������������
//�ռ��С�������ظ����ݣ���count��������ʱ�临�Ӷ�O��N + ��Χ������,
//�ռ临�Ӷ�O����Χ�����������������ʺ������ݽ�Ϊ�ܼ�������������ݼ�
//û���ظ������ݣ�����ֱ��ʹ��λͼ��

void CountSort(int* a,size_t size)
{
	assert(a);
	int max = a[0];
	int min = a[0];
	int count = 0;

	for(size_t i = 0;i < size;++i)//Ѱ�������е����������С��
	{
		if(a[i] < min)
		{
			min = a[i];
		}
		if(a[i] > max)
		{
			max = a[i];
		}
	}

	//���ٴ洢�ռ䣬����ʼ��
	int* temp = new int[max - min + 1];
	memset(temp,0,sizeof(int)*(max - min + 1));
	for(size_t i = 0;i < max - min + 1;++i)//ֱ��ѡַ��
	{
		int num = a[i] - min;
		temp[num]++;
	}

	for(size_t i = 0;i < size;)//������õ�˳��д��a������
	{
		for(size_t j = 0;j < max - min + 1;++j)
		{
			count = temp[j];
			while (count--)
			{
				a[i] = j + min;
				i++;
			}
		}
	}
	delete[] temp; 
}

void TestCountSort()
{
	int a[] = {2,9,1,4,7,8,0,3,6,5};
	int size = sizeof(a)/sizeof(a[0]);
	CountSort(a,size);
	Print(a,size);
}

//��������
//������������count��start��count����ͳ�Ƹ�λ�Ϸֱ�Ϊ0-9�����ݸ�����start����ͳ�����ݵĿ�ʼλ�ã���ʼλ��Ϊ0����һλ�����ݿ�ʼ��λ��=��һ�����ݵĿ�ʼλ��+��һλ�ܵ����ݸ����������size��С�Ŀռ����洢ÿ�����������ǵ�λ�������򣬴Ӹ�λ��ʼ����Ȼ������ʮλ��������λ��ֱ���ŵ�������ݵ����λ�����������

int GetMaxRadix(int* a,size_t size)//Ѱ���������λ��
{
	int index = 1;//������С��һλ
	int max = 10;
	for(size_t i = 0;i < size;++i)
	{
		while (a[i] >= max)//���ݴ���һλ
		{
			index++;
			max = max * 10;
		}
	}
	return index;
}

void LSDSort(int* a,size_t size)
{
	assert(a);
	int index = GetMaxRadix(a,size);//��������ݵ�λ��
	int count[10] = { 0 };//��¼���ݳ��ֵĴ���
	int start[10] = { 0 };//��¼���ݵ���ʼλ��
	int radex = 1;
	int* bucket = new int[size];

	for(int k = 1;k <= index;++k)//�Ӹ�λ�����λ��������
	{
		memset(count,0,sizeof(int)*10);//ÿ������ǰ��Ҫ��count��0
		//��������λ�ֱ�Ϊ0-9�����ݸ�����
		for(size_t i = 0;i < size;++i)
		{
			int num = (a[i] / radex) % 10;//ȡ��λ
			count[num]++;
		}

		//��¼���ݿ�ʼ��λ��
		start[0] = 0;
		int j = 1;
		while (j < 10)
		{
			start[j] = start[j - 1] + count[j - 1];
			j++;
		}
		for(size_t i = 0;i < size;++i)//�����ݰ�˳�����bucket��
		{
			int num = (a[i] / radex) % 10;
			bucket[start[num]++] = a[i];
		}
		radex *= 10;
		memcpy(a,bucket,sizeof(int)*size);
	}
	delete[] bucket;
}

void TestLSDSort()
{
	int a[] = {2,9,1,4,7,8,0,3,6,5};
	int size = sizeof(a)/sizeof(a[0]);
	LSDSort(a,size);
	Print(a,size);
}