#pragma once

//ʹ������ҵ�ƽ������

//���ʣ�
//    1�����ڵ���������������
//    2��ÿ���Ǹ��ڵ���[[M/2],M]������
//    3��ÿ���Ǹ��ڵ���[[M/2],M-1]���ؼ��֣���������������
//    4��key[i]��key[i+1]֮��ĺ��ӽڵ��ֵ����key[i]��key[i+1]֮��
//    5�����е�Ҷ�ӽڵ㶼��ͬһ��

template<class K,int M>//B��һ���ڵ�Ľṹ
struct BTreeNode
{
	K _key[M];//�ؼ��ֵĸ���ΪM-1������һ��λ�ÿ��Ը��ӷ������ȡ��λ��
	BTreeNode<K,M>* _subs[M+1];//�������ʱ���ѣ�������������ΪM�����ؼ��ֱ�����һ��
	BTreeNode<K,M>* _parent;//ָ���׽ڵ�
	size_t _size;//�����д�ŵ���Ч�ؼ��ֵĸ���
	
	BTreeNode()
		:_parent(NULL)
		,_size(0)
	{
		for(int i = 0;i < M+1;++i)
		{
			_subs[i] = NULL;
		}
	}
};

template<class K,class V>//��Ҫ��������������ʹ�ýṹ��
struct Pair
{
	K _first;
	V _second;

	Pair(const K& key = K(),const V& value = V())//ȱʡ�����������Ĭ�Ϲ��캯��
		:_first(key)
		,_second(value)
	{ }
};

template<class K,int M>
class BTree
{
	typedef BTreeNode<K,M> Node;
public:
	BTree()
		:_root(NULL)
	{ }

	Pair<Node*,int> Find(const K& key)//����
	{
		if(_root == NULL)
			return Pair<Node*,int>(NULL,-1);
		Node* parent = NULL;
		Node* cur = _root;
		while (cur)
		{
			int index = 0;
			while (index < cur->_size)
			{
				if(key == cur->_key[index])
				{
					return Pair<Node*,int>(cur,index);
				}
				else if(key < cur->_key[index])
				{
					break;
				}
				else
				{
					index++;
				}
			}
			parent = cur;
			cur = cur->_subs[index];
		}
		return Pair<Node* ,int>(parent,-1);
		//����Ҳû�ҵ���Ϊ��ʹ�ø�����·������ڵ㣬��˷���panrent������ڵ������parent��
	}

	bool Insert(const K& key)//����
	{
		//��ǰ�޽ڵ�
		if(_root == NULL)
		{
			_root = new Node;//����һ���µĽڵ�
			_root->_key[0] = key;
			_root->_subs[0] = NULL;
			_root->_parent = NULL;
			_root->_size++;
			return true;
		}

		Pair<Node*,int> cur = Find(key);
		if(cur._second != -1)//�ҵ����򷵻�false���������ظ��ؼ���
		{
			return false;
		}
		//�ڽڵ�cur�в���key��sub
		Node* str = cur._first;
		K newKey = key;
		Node* sub = NULL;
		while (1)
		{
			_InsertKey(str,newKey,sub);
			if(str->_size < M)//�ؼ��ֵ�����С��M������ȷ��ֱ�ӷ���
				return true;

			//�������ݺ󣬸ýڵ�Ĺؼ��ֵĸ������ڹ涨����������Ҫ���������з���
			int mid = (str->_size - 1)/2;
			int index = 0;
			Node* temp = new Node;

			//�ȿ����±�Ϊmid��Ĺؼ���
			for(size_t i = mid + 1;i < str->_size;i++)
			{
				temp->_key[index++] = str->_key[i];
				temp->_size++;
				str->_key[i] = 0;
			}

			//���ſ����±�Ϊmid�Ĺؼ��ֵ�sub
			index = 0;
			for(size_t i = mid + 1;i <= str->_size;i++)
			{
				temp->_subs[index++] = str->_subs[i];
				if(str->_subs[i] != NULL)
					str->_subs[i]->_parent = temp;
			}
			
			//����str�Ĵ�С
			str->_size = (str->_size - 1)/2;
			if(str->_parent == NULL)
			{
				_root = new Node;
				_root->_key[0] = str->_key[mid];
				str->_key[mid] = 0;
				_root->_subs[0] = str;
				_root->_subs[1] = temp;
				_root->_size = 1;
				str->_parent = _root;
				temp->_parent = _root;
				return true;
			}
			else
			{
				newKey = str->_key[mid];
				str->_key[mid] = 0;
				sub = temp;
				str = str->_parent;
			}
		}
	}

	void InOrder()
	{
		_InOrder(_root);
		cout<<endl;
	}


protected:
	void _InsertKey(Node* cur,const K& key,Node* sub)
	{
		int index = cur->_size - 1;
		while (index >= 0 && cur->_key[index] > key)//������Ľڵ�ȸ�λ�õ�ֵС������Ҫ��λ
		{
			cur->_key[index+1] = cur->_key[index];
			cur->_subs[index+2] = cur->_subs[index+1];
			--index;
		}
		//����ֱ�Ӳ���
		cur->_key[index + 1] = key;
		cur->_subs[index+2] = sub;
		if(sub != NULL)
			sub->_parent = cur;
		cur->_size++;
	}

	void _InOrder(Node* root)
	{
		if(root == NULL)
			return;
		for(int i = 0;i < root->_size;i++)
		{
			_InOrder(root->_subs[i]);
			cout<<root->_key[i]<<" ";
		}
		_InOrder(root->_subs[root->_size]);
	}

protected:
	Node* _root;
};

void BTreeTest()
{
	BTree<int,3> tree;
	int a[] = {53,75,139,49,145,36,101};
	for(int i = 0;i < sizeof(a)/sizeof(a[i]);i++)
	{
		tree.Insert(a[i]);
	}
	tree.InOrder();
}