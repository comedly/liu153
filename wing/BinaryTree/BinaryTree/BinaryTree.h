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

	void PosOrder()//���������ӡ������
	{
		cout<<"�������(�ݹ�)��";
		_PosOrder(_root);
		cout<<endl;
		_NonPosOrder(_root);
	}

	void LevelOrder()//��α���
	{
		cout<<"��α�����";
		_LevelOrder(_root);
		cout<<endl;
	}

	size_t Size()//����ĸ���
	{
		return _Size(_root);
	}

	size_t Depth()//���������
	{
		return _Depth(_root);
	}

	size_t LeafSize()//Ҷ�ӽڵ����
	{
		return _LeafSize(_root);
	}

	bool HasSubTree(Node* root)//�ж�root�Ƿ���_root������
	{
		bool result = false;
		if(_root != NULL && root != NULL)
		{
			if(_root->_data == root->_data)
			{
				result = DoseTree1HaveTree2(_root,root);
			}
			if(!result)
			{
				result = HasSubTree(_root->_left,root);
			}
			if(!result)
			{
				result = HasSubTree(_root->_right,root);
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
		return _Find(_root ,x);
	}

	size_t GetKLevel1(size_t k)//��k����ĸ���
	{
		return _GetKLevel1(_root,k);
	}

	size_t GetKLevel2(size_t k)//��k����ĸ���
	{
		size_t size = 0;
		size_t level = 1;
		_GetKLevel2(_root,level,k,size);
		return size;
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

	void _PosOrder(Node* root)//���������ӡ������
	{
		if(root == NULL)
		{
			return;
		}
		_PosOrder(root->_left);
		_PosOrder(root->_right);
		cout<<root->_data<<" ";
	}

	void _NonPosOrder(Node* root)//�ǵݹ�ʵ�ֺ����ӡ������
	{
		Node* cur = root;
		Node* prev = NULL;
		stack<Node*> s;
		if(root == NULL)
			return;
		cout<<"�ݹ�ʵ�ֶ�������";
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
		cout<<endl;
	}

	void _LevelOrder(Node* root)//��α���
	{
		queue<Node*> q;
		if(root == NULL)
		{
			return;
		}
		q.push(root);
		while (!q.empty())
		{
			if(q.front()->_left != NULL)
			{
				q.push(q.front()->_left);
			}
			if(q.front()->_right != NULL)
			{
				q.push(q.front()->_right);
			}
			cout<<q.front()->_data<<" ";
			q.pop();
		}
	}

	size_t _Size(Node* root)//����ĸ���
	{
		if(root == NULL)
			return 0;
		return _Size(root->_left) + _Size(root->_right) + 1;
	}

	size_t _Depth(Node* root)//���������
	{
		if(root == NULL)
			return 0;
		size_t leftsize = _Depth(root->_left);
		size_t rightsize = _Depth(root->_right);
		return leftsize > rightsize?(leftsize+1):(rightsize+1);
	}

	size_t _LeafSize(Node* root)//Ҷ�ӽڵ����
	{
		if(root == NULL)
			return 0;
		if(root->_left == NULL && root->_right == NULL)
			return 1;
		return _LeafSize(root->_left) + _LeafSize(root->_right);
	}

	bool DoseTree1HaveTree2(Node* root)//�ж���tree1���Ƿ�����tree2Ϊ���ڵ����������
	{
		if(root == NULL)
			return true;
		if(_root == NULL)
			return false;
		if(_root->_data != root->_data)
		{
			return false;
		}
		return DoseTree1HaveTree2(_root->_left,root->_left) && DoseTree1HaveTree2(_root->_right,root->_right);
	}

	void _MirrorRecursively(Node* root)//�������ľ���
	{
		//�жϸ��ڵ㼰���������Ƿ�Ϊ��
		if(root == NULL || (root->_left == NULL && root->_right == NULL))
			return;
		Node* temp = root->_left;
		root->_left = root->_right;
		root->_right = temp;
		if(root->_left != NULL)
			_MirrorRecursively(root->_left);
		if(root->_right != NULL)
			_MirrorRecursively(root->_right);
	}

	Node* _Find(Node* root,const T& x)//����
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

	size_t _GetKLevel1(Node* root,size_t k)
	{
		if(root == NULL)
			return 0;
		if(k == 1)
			return 1;
		return _GetKLevel1(root->_left,k-1) + _GetKLevel1(root->_right,k-1);
	}

	void _GetKLevel2(Node* root,size_t level,size_t k,size_t& size)
	{
		if(root == NULL)
			return ;
		if(k == level)
		{
			++size;
			return;
		}
		_GetKLevel2(root->_left,level+1,k,size);
		_GetKLevel2(root->_right,level+1,k,size);
	}

protected:
	Node* _root;//���ڵ�
};