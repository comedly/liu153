#pragma once 
#include<iostream>
#include<queue>
#include<stack>
using namespace std;

//�������н��Ľṹ
template<class T>
struct BinaryTreeNode
{
	BinaryTreeNode(const T& x)  //���캯��
		:_data(x)
		,_left(NULL)
		,_right(NULL)
	{ }

	T _data;  //����ֵ
	BinaryTreeNode<T>* _left;  //ָ���������Ľ��
	BinaryTreeNode<T>* _right; //ָ���������Ľ��	
};

template<class T>
class BinaryTree
{
	typedef BinaryTreeNode<T> Node;//������
public:
	BinaryTree() //Ĭ�Ϲ��캯��
		:_root(NULL)
	{ }

	BinaryTree(const T* a,size_t size,const T& invalid) //���캯��
		:_root(NULL)
	{
		size_t index = 0;
		_root = _CreateTree(a,size,invalid,index); //����һ��������
	}

	BinaryTree(const BinaryTree<T>& t) //�������캯��
		:_root(NULL)
	{
		_Copy(t._root);
	}

	BinaryTree<T>& operator=(const BinaryTree<T>& t) //��ֵ����
	{
		if(this != &t)
		{
			_Destroy(t._root);
			_Copy(t._root);
		}
		return *this;
	}

	~BinaryTree() //��������
	{
		if(_root)
		{
			_Destroy(_root);
		}
	}

	void PrevOrder() //ǰ�������ӡ������
	{
		cout<<"ǰ�������";
		_PrevOrder(_root);
	}

	void InOrder()//���������ӡ������
	{
		cout<<"���������";
		_InOrder(_root);
	}

	void PosOrder()//�����������ӡ������
	{
		cout<<"���������";
		_PosOrder(_root);
		cout<<endl;
	}

	void LevelOrder() //��α���
	{
		cout<<"��α�����";
		_LevelOrder(_root);
		cout<<endl;
	}

	size_t Size() //����ĸ���
	{
		return _Size(_root);
	}

	size_t Depth()//�������
	{
		return _Depth(_root);
	}

	size_t LeafSize() //Ҷ�ӽڵ���� 
	{
		return _LeafSize(_root);
	}

	bool HasSubTree(Node* root)//�ж�root�Ƿ�Ϊ_root������
	{
		bool result = false;
		if(root != NULL && _root != NULL)
		{
			if(root->_data == _root->_data)
				result = DoseTree1HaveTree2(_root,root);
			if(!result)
			{
				_root = _root->_left;
				result = HasSubTree(root);
			}
			if(!result)
			{
				_root = _root->_right;
				result = HasSubTree(root);
			}
		}
		return result;
	}

	void MirrorRecursively()//�������ľ���
	{
		_MirrorRecursively(_root);
	}

	Node* Find(const T& x)//����
	{
		return _Find(_root,x);
	}

	//size_t GetKLevel(size_t k)//��k����ĸ���
	//{
	//	return _GetKLevel(_root,k);
	//}

	size_t GetKLevel(size_t k)//��k����ĸ���
	{
		size_t size = 0;
		size_t level = 1;
		_GetKLevel(_root,level,k,size);
		return size;
	}

protected:
	Node* _Find(Node* root,const T& x)
	{
		if(root == NULL)
			return NULL;
		if(root->_data == x)
			return root;
		Node* ret = _Find(root->_left,x);
		if(ret)
			return ret;
		return _Find(root->_right,x);
	}

	/*size_t _GetKLevel(Node* root,size_t k)
	{
		if(root == NULL)
			return 0;
		if(k == 1)
			return 1;
		return _GetKLevel(root->_left,k-1) + _GetKLevel(root->_right,k-1);
	}*/

	void _GetKLevel(Node* root,size_t level,size_t k,size_t& size)
	{
		if(root == NULL)
			return;
		if(k == level)
		{
			++size;
			return;
		}
		_GetKLevel(root->_left,level+1,k,size);
		_GetKLevel(root->_right,level+1,k,size);
	}

	Node* _CreateTree(const T* a,size_t size,const T& invalid,size_t& index) //����һ��������
	{
		Node* root = NULL;
		if(a[index] != invalid && index < size)
		{
			root = new Node(a[index]);
			root->_left = _CreateTree(a,size,invalid,++index);
			root->_right = _CreateTree(a,size,invalid,++index);
		}
		return root;
	}

	void _Copy(Node* sroot)//��������
	{
		Node* root = NULL;
		if(sroot == NULL) //�жϸ��ڵ�
			return;
		if(sroot->_left && sroot->_right) //�жϸ��ڵ����������
		{
			root = new Node(sroot->_data);
			return ;
		}
		root->_left = _Copy(sroot->_left);//���ο���������
		root->_right = _Copy(sroot->_right);//���ο���������
	}

	void _Destroy(Node* root)//���ٶ�����
	{
		if(root == NULL)
		{
			return;
		}
		if(root->_left && root->_right)
		{
			delete root;
			root = NULL;
			return;
		}
		_Destroy(root->_left);
		_Destroy(root->_right);
	}

	//void _PrevOrder(Node* root) //�ݹ�ʵ��ǰ�������ӡ������
	//{
	//	if(root == NULL)
	//		return ;
	//	cout<<root->_data<<" ";
	//	_PrevOrder(root->_left);
	//	_PrevOrder(root->_right);
	//}

	void _PrevOrder(Node* root)//�ǵݹ�ʵ��ǰ�����
	{
		stack<Node*> s;
		if(root == NULL)
			return;
		s.push(root);
		while (!s.empty())
		{
			root = s.top();
			cout<<root->_data<<" ";
			s.pop();
			if (root->_right)
			{
				s.push(root->_right);
			}
			if(root->_left)
			{
				s.push(root->_left);
			}
		}
		cout<<endl;
	}

	//void _InOrder(Node* root) //�ݹ�ʵ�����������ӡ������
	//{
	//	if(root == NULL)
	//		return;
	//	_InOrder(root->_left);
	//	cout<<root->_data<<" ";
	//	_InOrder(root->_right);
	//}

	void _InOrder(Node* root)//�ǵݹ�ʵ���������
	{
		stack<Node*> s;
		Node* cur = root;
		while (cur || !s.empty())
		{
			while (cur)
			{
				s.push(cur);
				cur = cur->_left;
			}
			Node* top = s.top();
			cout<<top->_data<<" ";
			s.pop();
			cur = top->_right;
		}
		cout<<endl;
	}

	//void _PosOrder(Node* root) //�ݹ�ʵ�ֺ��������ӡ������
	//{
	//	if(root == NULL)
	//		return;
	//	_PosOrder(root->_left);
	//	_PosOrder(root->_right);
	//	cout<<root->_data<<" ";
	//}

	void _PosOrder(Node* root)//�ǵݹ�ʵ�ֺ������ 
	{
		Node* cur = root;
		Node* prev = NULL;
		stack<Node*> s;
		if(root == NULL)
			return;
		while (cur || !s.empty())
		{
			while (cur)
			{
				s.push(cur);
				cur = cur->_left;
			}
			cur = s.top();
			if(cur->_right == NULL || cur->_right == prev)
			{
				cout<<cur->_data<<" ";
				s.pop();
				prev = cur;
				cur = NULL;
			}
			else
			{
				cur = cur->_right;
			}
		}
	}

	void _LevelOrder(Node* root) //��α���
	{
		queue<Node*> p;
		if(root == NULL)
		{
			return;
		}
		p.push(root);
		while (!p.empty())
		{
			if(p.front()->_left != NULL)
			{
				p.push(p.front()->_left);
			}
			if(p.front()->_right != NULL)
			{
				p.push(p.front()->_right);
			}
			cout<<p.front()->_data<<" ";
			p.pop();
		}
	}

	void _MirrorRecursively(Node* root)
	{
		if(root == NULL || (root->_left == NULL && root->_right == NULL))
			return;
		
		//���������ӽ��
		Node* temp = root->_left;
		root->_left = root->_right;
		root->_right = temp;

		if(root->_left)
			_MirrorRecursively(root->_left);
		if(root->_right)
			_MirrorRecursively(root->_right);
	}

	size_t _Size(Node* root) //����ĸ���
	{
		if(root == NULL)
			return 0;
		return _Size(root->_left) + _Size(root->_right) + 1;
	}

	size_t _Depth(Node* root) //�������
	{
		if(root == NULL)
			return 0;
		size_t leftdepth = _Depth(root->_left);
		size_t rightdepth = _Depth(root->_right);
		return leftdepth > rightdepth ? leftdepth + 1 : rightdepth + 1;
	}

	size_t _LeafSize(Node* root) // Ҷ�ӽڵ�ĸ���
	{
		if(root == NULL)
			return 0;
		if(root->_left == NULL && root->_right == NULL)
			return 1;
		return _LeafSize(root->_left) + _LeafSize(root->_right);
	}

	bool DoseTree1HaveTree2(Node* root1,Node* root2)//�ж���tree1���Ƿ�����tree2���ڵ�����������ṹ
	{
		if(root2 == NULL)
			return true;
		if(root1 == NULL)
			return false;
		if(root1->_data != root2->_data)
			return false;
		return DoseTree1HaveTree2(root1->_left,root2->_left) && DoseTree1HaveTree2(root1->_right,root2->_right);
	}

//protected:
public:
	Node* _root;//���ڵ�
};

void Test()
{
	int a1[10] = {1,2,3,'#','#',4,'#','#',5,6};
	int a2[15] = {1,2,'#',3,'#','#',4,5,'#',6,'#',7,'#','#',8,};
	int a3[5] = {2,3,'#','#',4};

	BinaryTree<int> t1(a1,10,'#');
	BinaryTree<int> t2(a2,15,'#');
	BinaryTree<int> t3(a3,5,'#');

	cout<<"t1������������ǰ�����򣬺���,��Σ�:"<<endl;
	t1.PrevOrder();
	t1.InOrder();
	t1.PosOrder();
	t1.LevelOrder();
	cout<<"���������ĸ�����"<<t1.Size()<<endl;
	cout<<"�����������:"<<t1.Depth()<<endl;
	cout<<"��������Ҷ�ӽڵ���:"<<t1.LeafSize()<<endl;
	cout<<"�������ľ���:"<<endl;
	t1.MirrorRecursively();
	t1.PrevOrder();
	cout<<t1.Find(2)->_data<<endl;
	cout<<t1.GetKLevel(1)<<endl;
	cout<<endl;

	cout<<"t2������������ǰ�����򣬺���,��Σ�:"<<endl;
	t2.PrevOrder();
	t2.InOrder();
	t2.PosOrder();
	t2.LevelOrder();
	cout<<"���������ĸ�����"<<t2.Size()<<endl;
	cout<<"�����������:"<<t2.Depth()<<endl;
	cout<<"��������Ҷ�ӽڵ���:"<<t2.LeafSize()<<endl;
	cout<<"�������ľ���:"<<endl;
	t2.MirrorRecursively();
	t2.PrevOrder();
	cout<<endl;
}

void HasSubTreeTest()
{
	int a1[10] = {1,2,3,'#','#',4,'#','#',5,6};
	int a2[15] = {1,2,'#',3,'#','#',4,5,'#',6,'#',7,'#','#',8,};
	int a3[5] = {2,3,'#','#',4};

	BinaryTree<int> t1(a1,10,'#');
	BinaryTree<int> t2(a2,15,'#');
	BinaryTree<int> t3(a3,5,'#');

	cout<<"t3�Ƿ�Ϊt1������:"<<t1.HasSubTree(t3._root)<<endl;
}