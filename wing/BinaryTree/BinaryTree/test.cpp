#include"BinaryTree.h"

void Test1()
{
	int a1[10] = {1,2,3,'#','#',4,'#','#',5,6};
	int a2[15] = {1,2,'#',3,'#','#',4,5,'#',6,'#',7,'#','#',8,};
	int a3[5] = {2,3,'#','#',4};

	BinaryTree<int> t1(a1,10,'#');
	BinaryTree<int> t2(a1,15,'#');
	BinaryTree<int> t3(a1,5,'#');

	cout<<"t1遍历二叉树（前序、中序、后序、层次）:"<<endl;
	t1.PrevOrder();
	t1.InOrder();
	t1.PosOrder();
	t1.LevelOrder();
}

void Test2()
{
	int a1[10] = {1,2,3,'#','#',4,'#','#',5,6};
	int a2[15] = {1,2,'#',3,'#','#',4,5,'#',6,'#',7,'#','#',8,};
	int a3[5] = {2,3,'#','#',4};

	BinaryTree<int> t1(a1,10,'#');
	BinaryTree<int> t2(a1,15,'#');
	BinaryTree<int> t3(a1,5,'#');

	cout<<t1.Size()<<endl;
	cout<<t1.Depth()<<endl;
	cout<<t1.LeafSize()<<endl;
	t1.MirrorRecursively();
	t1.PrevOrder();
	cout<<t1.GetKLevel1(3)<<endl;
	cout<<t1.GetKLevel2(3)<<endl;
}

void Test3()
{
	int prev[] = {1,2,3,4,5,6};
	int in[] = {3,2,4,1,6,5};
	BinaryTreeNode<int>* root = Construct(prev,in,6);
	PrintTree(root);
	cout<<endl;
}

int main()
{
	//Test1();
	//Test2();
	Test3();
	system("pause");
	return 0;
}