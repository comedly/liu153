#pragma once
#include<iostream>
#include<queue>
#include<stack>
using namespace std;

//�������н��Ľṹ
template<class T>
struct BinaryTreeNode
{
	BinaryTreeNode(const T& x)
		:_data(x)
		,_left(NULL)
		,_right(NULL)
	{ }
	T _data;//����ֵ
	BinaryTreeNode<T>* _left;//ָ���������Ľ��
	BinaryTreeNode<T>* _right;//ָ���������Ľ��
};

template<class T>
class BinaryTree
{
	typedef BinaryTreeNode<T> Node;//������
public:
	BinaryTree()
		:_root(NULL)
	{ }

	BinaryTree(const T* a,size_t size,const T& invalid)
		:_root(NULL)
	{
		size_t index = 0;
		_root = _CreateTree(a,size,invalid,index);//����������
	}

	BinaryTree(const BinaryTree<T>& t)//�������캯��
		:_root(NULL)
	{
		_Copy(t._root);
	}

	BinaryTree<T>& operator=(const BinaryTree<T>& t)//��ֵ����
	{
		if(this != &t)
		{
			_Destory(t._root);
			_Copy(t._root);
		}
		return *this;
	}

	~BinaryTree()//��������
	{
		if(_root != NULL)
		{
			_Destroy(_root);
		}
	}

	void PrevOrder()//ǰ�������ӡ������
	{
		cout<<"ǰ�����(�ݹ�)��";
		_PrevOrder(_root);
		cout<<endl;
		_NonPrevOrder(_root);
	}

	void InOrder()//���������ӡ������
	{
		cout<<"�������(�ݹ�)��";
		_InOrder(_root);
		cout<<endl;
		_NonInOrder(_root);
	}

protected:
	Node* _CreateTree(const T* a,size_t size,const T& invalid,size_t& index)//����������
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
		if(sroot == NULL)//�жϸ��ڵ�
		{
			return;
		}
		if(sroot->_left && sroot->_right)//�жϽ�����������
		{
			root = new Node(sroot->_data);
			return;
		}
		root->_left = _Copy(sroot->_left);//���ο���������
		root->_left = _Copy(sroot->_right);//���ο���������
	}

	void _Destory(Node* root)//���ٶ�����
	{
		if(root == NULL)//���ڵ�Ϊ��
		{
			return;
		}
		if((root->_left == NULL) && (root->_right == NULL))ֻ�и��ڵ㣬ֱ���ͷŸ��ڵ㣬����ڵ�Ϊ��
		{
			delete root;
			root = NULL;
			return;
		}
		_Destory(root->_left);//��������������
		_Destory(root->_right);//��������������
	}

	void _PrevOrder(Node* root)//�ݹ�ʵ��ǰ�������ӡ������
	{
		if(root == NULL)
			return;
		cout<<root->_data<<" ";
		_PrevOrder(root->_left);
		_PrevOrder(root->_right);
	}

	void _NonPrevOrder(Node* root)//�ǵݹ�ʵ��ǰ�������ӡ������
	{
		stack<Node*> s;//����ջ���ص�ʵ��
		if(root == NULL)
			return;
		s.push(root);
		cout<<"ǰ�����(�ǵݹ�)��";
		while (!s.empty())
		{
			root = s.top();
			cout<<root->_data<<" ";
			s.pop();
			if(root->_right != NULL)
			{
				s.push(root->_right);
			}
			if(root->_left != NULL)
			{
				s.push(root->_left);
			}
		}
		cout<<endl;
	}

	void _InOrder(Node* root)//�ݹ�ʵ�����������ӡ������
	{
		if(root == NULL)
			return;
		_InOrder(root->_left);
		cout<<root->_data<<" ";
		_InOrder(root->_right);
	}

	void _NonInOrder(Node* root)//�ǵݹ�ʵ�����������ӡ������
	{
		stack<Node*> s;
		Node* cur = root;
		cout<<"����������ǵݹ飩";
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

protected:
	Node* _root;//���ڵ�
};

void Test()
{
	int a1[10] = {1,2,3,'#','#',4,'#','#',5,6};
	int a2[15] = {1,2,'#',3,'#','#',4,5,'#',6,'#',7,'#','#',8,};
	int a3[5] = {2,3,'#','#',4};

	BinaryTree<int> t1(a1,10,'#');
	BinaryTree<int> t2(a1,15,'#');
	BinaryTree<int> t3(a1,5,'#');

	cout<<"t1������������ǰ�����򡢺���:"<<endl;
	t1.PrevOrder();
	t1.InOrder();
}