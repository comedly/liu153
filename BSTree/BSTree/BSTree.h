#pragma once

//�������������ṹ
template<class K,class V>
struct BSTreeNode
{
	BSTreeNode<K,V>* _left;
	BSTreeNode<K,V>* _right;

	K _key;
	V _value;

	BSTreeNode(const K& key,const V& value)
		:_key(key)
		,_value(value)
		,_left(NULL)
		,_right(NULL)
	{ }
};

template<class K,class V>
class BSTree
{
	typedef BSTreeNode<K,V> Node;
public:
	BSTree()
		:_root(NULL)
	{	}

	bool Insert(const K& key,const V& value)//����
	{
		if(_root == NULL)//���ڵ�Ϊ��
		{
			_root = new Node(key,value);
			return true;
		}

		Node* parent = NULL;
		Node* cur = _root;
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
		if(parent->_key < key)//������Ľ��Ĺؼ�ֵ���ڵ�ǰ�ڵ��ֵ�����뵱ǰ�ڵ����ӽڵ�
		{
			parent->_right = new Node(key,value);
		}
		else
		{
			//������Ľ��Ĺؼ�ֵС�ڵ�ǰ�ڵ��ֵ�����뵱ǰ�ڵ�����ӽڵ�
			parent->_left = new Node(key,value);
		}
		return true;
	}

	void InOrder()//�������
	{
		cout<<"����������:";
		_InOrder(_root);
		cout<<endl;
	}

	Node* Find(const K& key)//����
	{
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

	bool Remove(const K& key)
	{
		Node* parent = NULL;
		Node* cur = _root;
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
				break;
			}
		}
		if(cur == NULL)
			return false;
		Node* del = NULL;
		if(cur->_left == NULL)
		{
			if(parent == NULL)//ɾ���Ľ���Ǹ��ڵ�
			{
				_root = cur->_right;
			}
			else
			{
				del = cur;
				if(parent->_left == cur)
				{
					parent->_left = cur->_right;
				}
				else
				{
					parent->_right = cur->_left;
				}
			}
		}
		else if(cur->_right == NULL)
		{
			del = cur;
			if(parent == NULL)
			{
				_root = cur->_left;
			}
			else
			{
				if(parent->_left == cur)
				{
					parent->_left = cur->_left;
				}
				else
				{
					parent->_right = cur->_left;
				}
			}
		}
		else
		{
			parent = cur;
			Node* firstLeft = cur->_right;
			while (firstLeft->_left)
			{
				parent = firstLeft;
				firstLeft = firstLeft->_left;
			}
			del = firstLeft;
			cur->_key = firstLeft->_key;
			cur->_value = firstLeft->_value;
			if(parent->_left == firstLeft)
				parent->_left = firstLeft->_right;
			else
				parent->_right = firstLeft->_right;
		}
		delete del;
		return true;
	}

	bool RemoveR(const K& key)
	{
		return _RemoveR(_root,key);
	}
	
	//���������ڵ������������Ƚڵ�
	Node* FindTwoLeastAncestor(const K& key1,const K& key2)
	{
		return _FindTwoLeastAncestor(_root,key1,key2);
	}
	
	Node* Convert()
	{
		return _Convert(_root);
	}

	~BSTree()
	{
		/*_Destory(_root);
		_root = NULL;*/
	}

protected:

	Node* _FindTwoLeastAncestor(Node*& root,const K& key1,const K& key2)
	{
		if(root == NULL)
			return NULL;
		if((key1 < root->_key) && (key2 > root->_key))
		{
			cout<<root->_key<<endl;
			return root;
		}
		if((key1 < root->_key) && (key2 < root->_key))
		{
			return _FindTwoLeastAncestor(root->_left,key1,key2);
		}
		if((key1 > root->_key)&&(key2 > root->_key))
		{
			return _FindTwoLeastAncestor(root->_right,key1,key2);
		}
		return NULL;
	}

	Node* _Convert(Node* root)
	{
		Node* pLastNodeInList = NULL;//ָ��˫�������β�ڵ�
		ConvertNode(root,&pLastNodeInList);
		Node* pHeadOfList = pLastNodeInList;//ָ������˫�������β�ڵ�
		//��Ҫ��ǰ��˷��ָ��ͷ�ڵ㣬����ͷ�ڵ�
		while (pHeadOfList != NULL && pHeadOfList->_left != NULL)
		{
			pHeadOfList = pHeadOfList->_left;
		}

		return pHeadOfList;
	}

	void ConvertNode(Node* pNode,Node** pLastNodeInList)
	{
		if(pNode == NULL)
			return;
		Node* pCurrent = pNode;
		if(pCurrent->_left != NULL)
			ConvertNode(pCurrent->_left,pLastNodeInList);
		pCurrent->_left = *pLastNodeInList;
		if(*pLastNodeInList != NULL)
			(*pLastNodeInList)->_right = pCurrent;

		*pLastNodeInList = pCurrent;
		if(pCurrent->_right != NULL)
			ConvertNode(pCurrent->_right,pLastNodeInList);
	}

	/*void _Destory(Node* root)
	{
		if(root == NULL)
			return ;
		_Destory(root->_left);
		_Destory(root->_right);
		delete root;
	}*/

	void _InOrder(Node* root)
	{
		if(root == NULL)
			return ;
		_InOrder(root->_left);
		cout<<root->_key<<" ";
		_InOrder(root->_right);
	}

	bool _RemoveR(Node*& root,const K& key)
	{
		if(root == NULL)
			return false;
		if(root->_key > key)
		{
			return _RemoveR(root->_left,key);
		}
		else if(root->_key < key)
		{
			return _RemoveR(root->_right,key);
		}
		else
		{
			Node* del = root;
			if(root->_left == NULL)
			{
				root = root->_right;
			}
			else if(root->_right == NULL)
			{
				root = root->_left;
			}
			else
			{
				Node* firstLeft = root->_right;
				while (firstLeft->_left)
				{
					firstLeft = firstLeft->_left;
				}
				swap(root->_key,firstLeft->_key);
				swap(root->_value,firstLeft->_value);
				return _RemoveR(root->_right,key);
			}
			delete del;
		}
		return true;
	}

protected:
	Node* _root;
};

void TESTBSTree()
{
	int a[] = {5,3,4,1,7,8,2,6,0,9};
	BSTree<int,int> tree;
	for(int i = 0;i < sizeof(a)/sizeof(a[0]);++i)
	{
		tree.Insert(a[i],i);
	}
	tree.InOrder();

	BSTreeNode<int,int>* ret = tree.Find(7);
	//cout<<ret->_key<<":"<<ret->_value;
	tree.Remove(7);
	tree.InOrder();
	tree.Remove(5);
	tree.InOrder();

	tree.Remove(3);
	tree.InOrder();
	tree.Remove(2);
	tree.Remove(1);
	tree.Remove(0);
	tree.Remove(9);
	tree.Remove(8);
	tree.Remove(6);
	tree.Remove(4);
	tree.InOrder();
}

void TESTBSTreeR()
{
	int a[] = {5,3,4,1,7,8,2,6,0,9};
	BSTree<int,int> tree;
	for(int i = 0;i < sizeof(a)/sizeof(a[0]);++i)
	{
		tree.Insert(a[i],i);
	}
	//BSTreeNode<int,int>* NewNode = tree.Convert();
	//tree.RemoveR(7);
	//tree.InOrder();

	tree.FindTwoLeastAncestor(6,9);

	/*tree.RemoveR(5);
	tree.RemoveR(1);
	tree.RemoveR(9);
	tree.RemoveR(2);
	tree.RemoveR(4);
	tree.RemoveR(6);
	tree.RemoveR(8);
	tree.RemoveR(3);
	tree.RemoveR(0);
	tree.InOrder();*/
}
