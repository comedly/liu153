#pragma once

//使用外查找的平衡多叉树

//性质：
//    1、根节点至少有两个孩子
//    2、每个非根节点有[[M/2],M]个孩子
//    3、每个非根节点有[[M/2],M-1]个关键字，并且以升序排列
//    4、key[i]和key[i+1]之间的孩子节点的值介于key[i]和key[i+1]之间
//    5、所有的叶子节点都在同一层

template<class K,int M>//B数一个节点的结构
struct BTreeNode
{
	K _key[M];//关键字的个数为M-1，多留一个位置可以更加方便的求取中位数
	BTreeNode<K,M>* _subs[M+1];//方便插入时分裂，子树的最大个数为M个，关键字比他少一个
	BTreeNode<K,M>* _parent;//指向父亲节点
	size_t _size;//数组中存放的有效关键字的个数
	
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

template<class K,class V>//需要返回两个参数，使用结构体
struct Pair
{
	K _first;
	V _second;

	Pair(const K& key = K(),const V& value = V())//缺省参数，会调用默认构造函数
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

	Pair<Node*,int> Find(const K& key)//查找
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
		//找完也没找到，为了使得该情况下方便插入节点，因此返回panrent，插入节点插入在parent上
	}

	bool Insert(const K& key)//插入
	{
		//当前无节点
		if(_root == NULL)
		{
			_root = new Node;//开辟一个新的节点
			_root->_key[0] = key;
			_root->_subs[0] = NULL;
			_root->_parent = NULL;
			_root->_size++;
			return true;
		}

		Pair<Node*,int> cur = Find(key);
		if(cur._second != -1)//找到，则返回false，不插入重复关键字
		{
			return false;
		}
		//在节点cur中插入key和sub
		Node* str = cur._first;
		K newKey = key;
		Node* sub = NULL;
		while (1)
		{
			_InsertKey(str,newKey,sub);
			if(str->_size < M)//关键字的数量小于M，则正确，直接返回
				return true;

			//插入数据后，该节点的关键字的个数大于规定的数量，需要调整，进行分裂
			int mid = (str->_size - 1)/2;
			int index = 0;
			Node* temp = new Node;

			//先拷贝下标为mid后的关键字
			for(size_t i = mid + 1;i < str->_size;i++)
			{
				temp->_key[index++] = str->_key[i];
				temp->_size++;
				str->_key[i] = 0;
			}

			//接着拷贝下标为mid的关键字的sub
			index = 0;
			for(size_t i = mid + 1;i <= str->_size;i++)
			{
				temp->_subs[index++] = str->_subs[i];
				if(str->_subs[i] != NULL)
					str->_subs[i]->_parent = temp;
			}
			
			//更改str的大小
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
		while (index >= 0 && cur->_key[index] > key)//若插入的节点比改位置的值小，则需要移位
		{
			cur->_key[index+1] = cur->_key[index];
			cur->_subs[index+2] = cur->_subs[index+1];
			--index;
		}
		//否则，直接插入
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