#include<iostream>
#include<assert.h>
#include<list>
#include<vector>
using namespace std;

//1����������������ڵ�Ĺ������Ƚڵ�

//�������Ľڵ�ṹ
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

//������һ�Ŷ������������� 4 �� 6 �Ĺ������Ƚڵ�1���ȵõ���
//һ��·��1->2->4(����ǰ���������������ѹ��1 2 3 ����Ϊ3��
//����4�����Ҷ�Ϊ�գ���3������ѹ��4,)������һ��·��1->5->6
//(��������һ��·��)������������·���Ĺ����ڵ㼸λ������
//��Ĺ������Ƚڵ㡣

//��ȡĳһ���ڵ����ڵ�·��
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

//�������·������󹫹��ڵ�
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

//2���������ľ���,ʱ�临�Ӷ�ΪO(N)
//1)�����ڵ㣬�������ĸ߶�+�������ĸ߶�
//2)�������ڵ�

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

//3����һ������������ת��Ϊһ��˫������Ҫ���ܴ����µĽ��
//ֻ�ܵ�������ָ���ָ��

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

	//pLastNodeInListָ��˫�������β���
	//������Ҫ����ͷ�ڵ�
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

	cout<<"n3��n4�Ĺ������Ƚڵ�Ϊ:"<<GetLastCommonParent(n1,n3,n4)->data<<endl;

	MaxLen(n1);
	cout<<"�˶������ľ���Ϊ:"<<maxlen<<endl<<endl;

	cout<<"������ת��Ϊ˫������"<<endl;
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