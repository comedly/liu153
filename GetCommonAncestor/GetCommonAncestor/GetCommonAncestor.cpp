#include<iostream>
#include<assert.h>
#include<list>
#include<vector>
using namespace std;

//1、求二叉树中两个节点的公共祖先节点

//二叉树的节点结构
struct TreeNode
{
	TreeNode* _left;
	TreeNode* _right;
	
	int data;
	TreeNode(int x)
		:_left(NULL)
		,_right(NULL)
		,data(x)
	{ }
};

//      1
//   2      5
// 3   4  6    

//如上是一颗二叉树，若查找 4 和 6 的公共祖先节点1，先得到有
//一条路劲1->2->4(利用前序遍历，向容器中压人1 2 3 ，因为3不
//等于4且左右都为空，则将3弹出，压入4,)，另外一条路劲1->5->6
//(类似于上一条路劲)。最后求得两条路劲的公共节点几位两个节
//点的公共祖先节点。

//获取某一个节点所在的路劲
bool GetNodePath(TreeNode* root,TreeNode* pNode,list<TreeNode*>& paths)
{
	assert(pNode);
	if(root == NULL)
		return false;

	if(root == pNode)
		return true;

	paths.push_back(root);
	
	if(GetNodePath(root->_left,pNode,paths))
		return true;
	if(GetNodePath(root->_right,pNode,paths))
		return true;

	paths.pop_back();
	return false;
}

//求得两条路劲的最后公共节点
TreeNode* GetCommonNode(const list<TreeNode*>& path1,const list<TreeNode*>& path2)
{
	list<TreeNode*>::const_iterator it1 = path1.begin();
	list<TreeNode*>::const_iterator it2 = path2.begin();

	TreeNode* last = NULL;

	while ((it1 != path1.end()) && (it2 != path2.end()))
	{
		if(*it1 == *it2)
		{
			last = *it1;
		}
		it1++;
		it2++;
	}
	return last;
}

TreeNode* GetLastCommonParent(TreeNode* root,TreeNode* pNode1,TreeNode* pNode2)
{
	if(root == NULL || pNode1 == NULL || pNode2 == NULL)
		return NULL;

	list<TreeNode*> path1;
	GetNodePath(root,pNode1,path1);

	list<TreeNode*> path2;
	GetNodePath(root,pNode2,path2);

	return GetCommonNode(path1,path2);
}

//2、二叉树的距离,时间复杂度为O(N)
//1)过根节点，左子树的高度+右子树的高度
//2)不过根节点

int maxlen = 0;
int MaxLen(TreeNode* root)
{
	if(root == NULL)
		return 0;

	int leftH = MaxLen(root->_left);
	int rightH = MaxLen(root->_right);

	if(leftH + rightH > maxlen)
		maxlen = leftH + rightH;

	return leftH > rightH ? leftH+1:rightH+1;
}

//3、将一个二叉搜索树转换为一个双向链表，要求不能创建新的结点
//只能调整树中指针的指向

void ConvertNode(TreeNode* pNode,TreeNode** pLastNodeInList)
{
	if(pNode == NULL)
		return;

	TreeNode *pCurrent = pNode;
	if(pCurrent->_left != NULL)
		ConvertNode(pCurrent->_left,pLastNodeInList);

	pCurrent->_left = *pLastNodeInList;
	if( *pLastNodeInList != NULL)
		(*pLastNodeInList)->_right = pCurrent;

	*pLastNodeInList = pCurrent;

	if(pCurrent->_right != NULL)
		ConvertNode(pCurrent->_right,pLastNodeInList);
}

TreeNode* Convert(TreeNode* root)
{
	TreeNode* pLastNodeInList = NULL;
	ConvertNode(root,&pLastNodeInList);

	//pLastNodeInList指向双向链表的尾结点
	//我们需要返回头节点
	TreeNode* pHeadOfList = pLastNodeInList;
	while (pHeadOfList != NULL && pHeadOfList->_left != NULL)
	{
		pHeadOfList = pHeadOfList->_left;
	}

	return pHeadOfList;
}


int main()
{
	TreeNode* n1 = new TreeNode(1);
	TreeNode* n2 = new TreeNode(2);
	TreeNode* n3 = new TreeNode(3);
	TreeNode* n4 = new TreeNode(4);
	TreeNode* n5 = new TreeNode(5);
	TreeNode* n6 = new TreeNode(6);

	n1->_left = n2;
	n1->_right = n5;
	n2->_left = n3;
	n2->_right = n4;
	n5->_left = n6;

	cout<<"n3和n4的公共祖先节点为:"<<GetLastCommonParent(n1,n3,n4)->data<<endl;

	MaxLen(n1);
	cout<<"此二叉树的距离为:"<<maxlen<<endl<<endl;

	cout<<"二叉树转换为双向链表："<<endl;
	TreeNode* head = Convert(n1);
	while (head != NULL)
	{
		cout<<head->data<<" ";
		head = head->_right;
	}
	cout<<endl;
	system("pause");
	return 0;
}