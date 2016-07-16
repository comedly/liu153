#include<iostream>
using namespace std;

//判断一个序列是否为二叉搜索树的后序遍历序列
bool verifySequenceOfBST(int sequence[],int length)
{
	if(sequence == NULL || length <= 0)
		return false;
	int root = sequence[length - 1];//最后一个元素为根节点
	int i = 0;
	for(i = 0;i < length - 1;i++)
	{
		//小于根节点的值为左子树
		if(sequence[i] > root)
			break;
	}
	int j = i;
	for(;j < length - 1;j++)
	{
		//右子树应该都大于根节点
		if(sequence[j] < root)
			return false;
	}

	bool left = true;//递归实现左子树
	if(i > 0)
	{
		left = verifySequenceOfBST(sequence,i);
	}
	bool right = true;//递归实现右子树
	if(j < length - 1)
	{
		right = verifySequenceOfBST(sequence + i,length - i - 1);
	}
	return left && right;
}

//判断一个序列是否为二叉搜索树的后序遍历序列
bool PrevSequenceOfBST(int sequence[] ,int length)
{
	if(sequence == NULL || length <= 0)
		return false;
	int root = sequence[0];//第一个节点为根节点
	int i = 1;
	for(;i < length;i++)//比root小的都为左子树
	{
		if(sequence[i] > root)
			break;
	}
	int j = i;
	for(;j < length;j++)//比root大的是右子树
	{
		if(sequence[j] < root)
			return false;
	}

	bool left = true;//递归遍历左子树
	if(i > 1)
	{
		left = PrevSequenceOfBST(sequence + 1,i);
	}
	bool right = true;//递归遍历右子树
	if(j < length)
	{
		right = PrevSequenceOfBST(sequence + i,length - i);
	}
	return (left && right);
}

int main()
{
	int a[] = {5,7,6,9,11,10,8};
	int b[] = {8,6,5,7,10,9,11};
	cout<<"序列a是否为搜索二叉树的后序遍历序列？"<<verifySequenceOfBST(a,sizeof(a)/sizeof(a[0]))<<endl;
	cout<<"序列b是否为搜索二叉树的前序遍历序列？"<<PrevSequenceOfBST(b,sizeof(b)/sizeof(b[0]))<<endl;
	system("pause");
	return 0;
}