#pragma once

template<class K,class V>
struct AVLTreeNode
{
	AVLTreeNode<K,V>* _left;
	AVLTreeNode<K,V>* _right;
	AVLTreeNode<K,V>* _parent;

	K _key;
	V _value;

	int _bf;//ƽ������
	AVLTreeNode(const K& key,const V& value)
		:_bf(0)
		,_left(NULL)
		,_right(NULL)
		,_parent(NULL)
		,_key(key)
		,_value(value)
	{ }
};

template<class K,class V>
class AVLTree
{
public:
	typedef AVLTreeNode<K,V> Node;
	AVLTree()
		:_root(NULL)
	{ }

	bool Insert(const K& key,V& value)
	{
		if(_root == NULL)
		{
			_root = new Node(key,value);
			return true;
		}

		Node* cur = _root;
		Node* parent = NULL;

		while (cur)
		{
			if(cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if(cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return false;
			}
		}

		cur = new Node(key,value);
		if(parent->_key < key)
		{
			parent->_right = cur;
			cur->_parent = parent;
		}
		else
		{
			parent->_left = cur;
			cur->_parent = parent;
		}

		//������Ƿ�ƽ��
		//����ƽ�����ӣ�����������ʱ��������ת
		while (parent)
		{
			if(cur == parent->_left)
				parent->_bf--;
			else
				parent->_bf++;
			if(parent->_bf == 0)
				break;
			else if(parent->_bf == -1 || parent->_bf == 1)//��˷
			{
				cur = parent;
				parent = cur->_parent;
			}
			else//ƽ������Ϊ2��-2
			{
				if(cur->_bf == 1)
				{
					if(parent->_bf == 2)
						RotateL(parent);
					else//-2
						RotateLR(parent);
				}
				else
				{
					if(parent->_bf == -2)
						RotateR(parent);
					else
						RotateRL(parent);
				}
				break;
			}
		}
		return true;
	}

	Node* Find(const K& key)
	{
		if(_root == NULL)
			return NULL;
		Node* cur = _root;
		while (cur)
		{
			if(cur->_key < key)
			{
				cur = cur->_right;
			}
			else if(cur->_key > key)
			{
				cur = cur->_left;
			}
			else
			{
				return cur;
			}
		}
		return NULL;
	}

	void InOrder()
	{
		_InOrder(_root);
		cout<<endl;
	}

	bool IsBlance()
	{
		return _IsBlance(_root);
	}


	~AVLTree()
	{
		_Destroy(_root);
		_root = NULL;
	}

protected:
	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		parent->_right = subRL;
		if(subRL)
			subRL->_parent = parent;

		subR->_left = parent;

		Node* ppNode = parent->_parent;
		parent->_parent = subR;
		subR->_parent = ppNode;
		if(ppNode == NULL)
		{
			_root = subR;
		}
		else
		{
			if(ppNode->_left == parent)
				ppNode->_left = subR;
			else
				ppNode->_right = subR;
		}
		parent->_bf = subR->_bf = 0;
	}

	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		parent->_left = subLR;
		if(subLR)
			subLR->_parent = parent;
		subL->_right = parent;
		Node* ppNode = parent->_parent;
		parent->_parent = subL;
		subL->_parent = ppNode;

		if(ppNode == NULL)
		{
			_root = subL;
		}
		else
		{
			if(ppNode->_left == parent)
				ppNode->_left = subL;
			else 
				ppNode->_right = subL;
		}
		parent->_bf = subL->_bf = 0;
	}

	void RotateLR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR =subL->_right;
		int bf = subLR->_bf;

		RotateL(parent->_left);
		RotateR(parent);

		//����subL��ƽ���������������ڵ��ƽ������
		if(bf == -1)
		{
			subL->_bf = 0;
			parent->_bf = 1;
		}
		else if(bf == 1)
		{
			subL->_bf = -1;
			parent->_bf = 0;
		}
		else
		{
			subL->_bf = parent->_bf = 0;
		}
	}

	void RotateRL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		int bf = subRL->_bf;
		RotateR(parent->_right);
		RotateL(parent);

		//����subRL��ƽ���������������ڵ��ƽ������
		if(bf == 1)
		{
			subR->_bf = 0;
			parent->_bf = -1;
		}
		else if(bf == -1)
		{
			subR->_bf = 1;
			parent->_bf = 0;
		}
		else
		{
			parent->_bf = subR->_bf = 0;
		}
	}

	void _Destroy(Node* root)
	{
		if(root == NULL)
			return;
		_Destroy(root->_left);
		_Destroy(root->_right);
		delete root;
	}

	void _InOrder(Node* root)
	{
		if(root == NULL)
			return;
		_InOrder(root->_left);
		cout<<root->_key<<" ";
		_InOrder(root->_right);
	}

	int _Height(Node* root)
	{
		if(root == NULL)
			return 0;
		int Left = _Height(root->_left);
		int Right = _Height(root->_right);
		return (Left > Right) ? (Left + 1) : (Right + 1);
	}

	bool _IsBlance(Node* root)
	{
		if(root == NULL)
			return true;
		int left = _Height(root->_left);
		int right = _Height(root->_right);
		if((right - left) != root->_bf || abs(right - left) > 1)
		{
			cout<<"�ýڵ��ƽ�������쳣:";
			cout<<root->_key<<" "<<endl;
			return false;
		}
		return _IsBlance(root->_left) && _IsBlance(root->_right);
	}

protected:
	Node* _root;
};

void AVLTreeTest()
{
	int a[] = {16, 3, 7, 11, 9, 26, 18, 14, 15};
	AVLTree<int,int> tree;
	for(int i = 0;i < 9;i++)
	{
		tree.Insert(a[i],i);
	}
	tree.InOrder();
	tree.Find(16);
	tree.IsBlance();
	
}

void TestTree_SP()
{
	int a[] = {4, 2, 6, 1, 3, 5, 15, 7, 16, 14};
	AVLTree<int, int> t;

	for (int i = 0; i < sizeof(a)/sizeof(a[0]); ++i)
	{
		t.Insert(a[i], i);
	}
	t.InOrder();
	t.IsBlance();
}