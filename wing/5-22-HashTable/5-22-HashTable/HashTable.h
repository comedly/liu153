#pragma once
#include<iostream>
#include<string>
using namespace std;

namespace First
{
	//线性探测的特化处理可以处理自定义类型的数据
	enum State
	{
		EMPTY,//该位置未存放元素
		DELETE,//该位置的元素已被删除
		EXITS,//该位置存在元素
	};

	//产生键值  仿函数
	template<class K>
	struct __HashFunc
	{
		size_t operator()(const K& key)
		{
			return key;
		}
	};

	template<class K>
	class HashTable
	{
		//key形式的线性探测
	public:
		HashTable(size_t capacity = 10)
			:_table(new K[capacity])
			,_state(new State[capacity])
			,_size(0)
			,_capacity(capacity)
		{
			//memset(_state,EMPTY,sizeof(State)*capacity);会出问题，因为memset是以字节初始化的
			for(size_t i = 0;i < _capacity;i++)
			{
				_state[i] = EMPTY;//每个位置置空
			}
		}

		HashTable(const HashTable<K>& ht)//拷贝构造函数
			:_table(new K[ht._capacity])
			,_state(new State[ht._capacity])
			,_size(0)
			,_capacity(ht._capacity)
		{
			for(size_t i = 0;i < ht._capacity;i++)
			{
				if(ht._state[i] == EXITS)
				{
					Insert(ht._table[i]);
				}
			}
		}

		HashTable& operator=(const HashTable<K>& ht)//赋值函数
		{
			if(ht._table != _table && ht._state != _state)
			{
				HashTable<K> tem(ht);
				Swap(tmp);
			}
			return *this;
		}

		~HashTable()
		{
			if(_table != NULL)
			{
				delete[] _table;
			}
			if(_state != NULL)
			{
				delete[] _state;
			}
		}

		//线性探测计算出元素的存放位置（假设不哈希冲突）
		int _HashFunc(const K& key)
		{
			__HashFunc<K> hf;
			return hf(key)%_capacity;
			//匿名对象调用operator()
			//return __HashFun<K>()(key)%_capacity;
		}

		bool Insert(const K& key)
		{
			//静态哈希表
			if(_size == _capacity)
			{
				cout<<"HashTable is full!"<<endl;
				return false;
			}
			//动态哈希表
			//高效的哈希表的载荷因子大概稳定在0.7-0.8
			if(_size*10/_capacity >= 7)
			{
				_CheckCapacity();
			}
			int index = _HashFunc(key);
			while (_state[index] == EXITS)
			{
				index++;
				if(index == _capacity)
				{
					index = 0;
				}
			}
			_table[index] = key;
			_state[index] = EXITS;
			_size++;
			return true;
		}

		int Find(const K& key)
		{
			size_t index = _HashFunc(key);
			size_t start = index;
			//该位置存在；若该位置被删除了，需要查找的有可能在后边，需要跳过继续查找
			while(EMPTY != _state[index])
			{
				if(_table[index] == key)
				{
					if(_state[index] == EXITS)
					{
						return index;
					}
					else
					{
						return -1;
					}
				}
				index++;
				if(index == _capacity)
				{
					index = 0;
				}
				if(index == start)//查找一圈，没有找到就停止，防止死循环
				{
					return -1;
				}
			}
			return -1;
		}

		bool Remove(const K& key)
		{
			int index = Find(key);
			if(index != -1)
			{
				_state[index] = DELETE;
				_size--;
				return true;
			}
			return false;
		}

		void Print()//打印
		{
			for(int i = 0;i < _capacity;i++)
			{
				if(_state[i] == EXITS)
				{
					cout<<i<<"(EXITS)"<<_table[i]<<endl;
				}
				//将DELETE状态下的元素也打印出来，便于观察
				//而Insert处理时，DELETE状态下的位置可以插上新的元素
				else if(_state[i] == DELETE)
				{
					cout<<i<<"(DELETE)"<<_table[i]<<endl;
				}
				else
				{
					cout<<i<<"(EMPTY)"<<_table[i]<<endl;
				}
			}
		}

		void Swap(HashTable<K> temp) //交换
		{
			swap(_size,temp._size);
			swap(_capacity,temp._capacity);
			swap(_state,temp._state);
			swap(_table,temp._table);
		}

	protected:
		void _CheckCapacity() //扩容
		{
			HashTable<K> temp(2*_capacity);
			for(int i = 0;i < _capacity;i++)
			{
				temp.Insert(_table[i]);
			}
			Swap(temp);
		}
		
	private:
		K* _table;//哈希表
		State* _state;//状态表
		size_t _size;
		size_t _capacity;
	};
}

namespace Second
{
	//线性探测的特化处理可以处理自定义类型的数据
	enum State
	{
		EMPTY,//该位置未存放元素
		DELETE,//该位置的元素已被删除
		EXITS,//该位置存在元素
	};

	template<class K,class V>
	struct HashTableNode
	{
		K _key;
		V _value;
	};

	//处理基本类型
	template<class K>
	struct __HashFunc//默认的返回哈希键值hey的 仿函数
	{
		size_t operator()(const K& key)
		{
			return key;
		}
	};

	//特化string的__HashFunc 仿函数
	//处理自定义类型
	template<>
	struct __HashFunc<string>
	{
		//下边这种缺点，产生重复的key，如“abcd”与“bcad”
		size_t operator()(const string& str)
		{
			size_t key = 0;
			for(int i = 0;i < str.size();i++)
			{
				key += str[i];
			}
			return key;
		}
	};

	//实现哈希表的key/value形式的二次探测
	template<class K,class V,class HashFuncer = __HashFunc<K>>
	class HashTable
	{
		typedef HashTableNode<K,V> Node;
	public:
		HashTable(size_t capacity = 10)
			:_table(new Node[capacity])
			,_state(new State[capacity])
			,_size(0)
			,_capacity(capacity)
		{
			//memset(_state,EMPTY,sizeof(State)*capacity);会出问题，因为memset是以字节初始化的
			for(size_t i = 0;i < capacity;i++)
			{
				_state[i] = EMPTY;//每个位置置空
			}
		}

		HashTable(const HashTable<K,V,HashFuncer>& ht)//拷贝构造函数
			:_table(new Node[ht._capacity])
			,_state(new State[ht._capacity])
			,_size(0)
			,_capacity(ht._capacity)
		{
			for(size_t i = 0;i < ht._capacity;i++)
			{
				if(ht._state[i] == EXITS)
				{
					Insert(ht._table[i]._key,ht._table[i]._value);
				}
			}
		}

		HashTable& operator=(const HashTable<K,V,HashFuncer>& ht)//赋值函数
		{
			if(ht._table != _table && ht._state != _state)
			{
				HashTable<K,V,HashFuncer> tem(ht);
				Swap(tmp);
			}
			return *this;
		}

		~HashTable()
		{
			if(_table != NULL)
			{
				delete[] _table;
			}
			if(_state != NULL)
			{
				delete[] _state;
			}
		}

		//线性探测计算出元素的存放位置（假设不哈希冲突）
		int _HashFunc(const K& key)
		{
			HashFuncer hf;
			return hf(key)%_capacity;
			//匿名对象调用operator()
			//return __HashFun<K>()(key)%_capacity;
		}

		bool Insert(const K& key,const V& value)
		{
			//静态哈希表
			//if(_size == _capacity)
			//{
			//	cout<<"HashTable is full!"<<endl;
			//	return false;
			//}

			//动态哈希表
			//高效的哈希表的载荷因子大概稳定在0.7-0.8
			if(_size*10/_capacity >= 7)
			{
				_CheckCapacity();
			}
			
			size_t hashKeyStart = _HashFunc(key);
			size_t add_more = 1;
			int index = hashKeyStart;
			//二次探测
			//Hash(key)+0 Hash(key)+1^2 Hash(key)+2^2 ...
			while (_state[index] == EXITS)
			{
				index = hashKeyStart + add_more*add_more;
				add_more++;
				if(index == _capacity)
				{
					index = index%_capacity;
				}
			}
			_table[index]._key = key;
			_table[index]._value = value;
			_state[index] = EXITS;
			_size++;
			return true;
		}

		int Find(const K& key)
		{
			size_t index = _HashFunc(key);
			size_t start = index;
			//该位置存在；若该位置被删除了，需要查找的有可能在后边，需要跳过继续查找
			while(EMPTY != _state[index])
			{
				if(_table[index]._key == key)
				{
					if(_state[index] == EXITS)
					{
						return index;
					}
					else
					{
						return -1;
					}
				}
				index++;
				if(index == _capacity)
				{
					index = 0;
				}
				if(index == start)//查找一圈，没有找到就停止，防止死循环
				{
					return -1;
				}
			}
			return -1;
		}

		void FindKeyPrintToValue(int& ret)//根据key的值，查找value的值并打印
		{
			if(ret != -1)
			{
				cout<<_table[ret]._value<<endl;
			}
			else
			{
				return;
			}
		}

		bool Remove(const K& key)
		{
			int index = Find(key);
			if(index != -1)
			{
				_state[index] = DELETE;
				_size--;
				return true;
			}
			return false;
		}

		void Print()//打印
		{
			for(int i = 0;i < _capacity;i++)
			{
				if(_state[i] == EXITS)
				{
					cout<<i<<"(EXITS)"<<_table[i]._key<<"--"<<_table[i]._value<<endl;
				}
				//将DELETE状态下的元素也打印出来，便于观察
				//而Insert处理时，DELETE状态下的位置可以插上新的元素
				else if(_state[i] == DELETE)
				{
					cout<<i<<"(DELETE)"<<_table[i]._key<<"--"<<_table[i]._value<<endl;
				}
				else
				{
					cout<<i<<"(EMPTY)"<<_table[i]._key<<"--"<<_table[i]._value<<endl;
				}
			}
		}

		void Swap(HashTable<K,V,HashFuncer> temp) //交换
		{
			swap(_size,temp._size);
			swap(_capacity,temp._capacity);
			swap(_state,temp._state);
			swap(_table,temp._table);
		}

	protected:
		void _CheckCapacity() //扩容
		{
			HashTable<K,V,HashFuncer> temp(2*_capacity);
			for(int i = 0;i < _capacity;i++)
			{
				temp.Insert(_table[i]._key,_table[i]._value);
			}
			Swap(temp);
		}
		
	private:
		Node* _table;//哈希表
		State* _state;//状态表
		size_t _size;//哈希表中元素的个数
		size_t _capacity;//哈希表的容量
	};
}

namespace HashTableBucket
{
	template<class K,class V>
	struct HashTableNode
	{
		K _key;
		V _value;
		HashTableNode* _next;//若哈希冲突,则挂在上一个位置的下面
		HashTableNode()
			:_next(NULL)
		{ } 

		HashTableNode(const K& key,const V& value)
			:_key(key)
			,_value(value)
			,_next(NULL)
		{ }
	};

	template<class K>
	struct DefaultHashFunc
	{
		size_t operator()(const K& key)
		{
			return key;
		}
	};

	template<>
	struct DefaultHashFunc<string>
	{
		size_t operator()(const string& str)
		{
			size_t key = 0;
			for(size_t i = 0;i < str.size();i++)
			{
				key += str[i];
			}
			return key;
		}
	};

	template<class K,class V,class HashFunc = DefaultHashFunc<K>>
	class HashTableBucket
	{
		typedef HashTableNode<K,V> Node;
	public:
		HashTableBucket()
			:_table(NULL)
			,_size(0)
		{ }

		HashTableBucket(const HashTableBucket<K,V,HashFunc>& ht)//拷贝构造
		{
			//将哈希表ht拷贝给this
			this->_table.resize(ht._table.size());//开辟一块和哈希桶大小一样的空间
			for(int i = 0;i < ht._table.size();i++)
			{
				Node* cur = ht._table[i];
				while (cur)
				{
					Node* temp = new Node(cur->_key,cur->_value);
					temp->_next = _table[i];
					_table[i] = temp;
					this->_size++;
					cur = cur->_next;
				}
			}
		}

		//赋值语句的现代写法
		HashTableBucket<K,V> operator=(HashTableBucket<K,V> ht)//此处就不能用const
		{
			if(this != &ht)
			{
				swap(_table,ht._table);
				swap(_size,ht._size);
			}
			return *this;
		}

		~HashTableBucket()//析构函数
		{
			if(this->_table.size() != 0)
			{
				for(int i = 0;i < this->_table.size();i++)
				{
					Node* cur = _table[i];
					while (cur != NULL)
					{
						Node* del = cur;
						cur = cur->_next;
						delete del;
						del = NULL;
					}
				}
			}
			_size = 0;
		}

		bool Insert(const K& key,const V& value)
		{
			//检查容量
			_CheckExpand();

			size_t index = _HashFunc(key);
			Node* cur = _table[index];
			//防止冗余
			while (cur)
			{
				if(key == cur->_key)
				{
					return false;
				}
				cur = cur->_next;
			}
			Node* NewNode = new Node(key,value);
			NewNode->_next = _table[index];
			_table[index] = NewNode;
			_size++;
			return true;
		}

		Node* Find(const K& key)//查找
		{
			size_t index = _HashFunc(key);
			Node* cur = _table[index];
			while (cur)
			{
				if(key == cur->_key)
				{
					return cur;
				}
				cur = cur->_next;
			}
			return NULL;
		}

		bool Remove(const K& key)//删除
		{
			size_t index = _HashFunc(key);
			Node* cur = _table[index];
			Node* prev = NULL;
			while (cur)
			{
				if(cur->_key == key)
					break;
				prev = cur;
				cur = cur->_next;
			}
			if(cur)
			{
				if(cur == _table[index])
				{
					_table[index] = cur->_next;
				}
				else
				{
					Node* next = cur->_next;
					prev->_next = next;
				}
				delete cur;
				cur = NULL;
				--_size;
				return true;
			}
			return false;
		}

		void PrintHashTable()
		{
			for(size_t i = 0;i < _table.size();i++)
			{
				Node* cur = _table[i];
				while (cur)
				{
					cout<<i<<":{"<<cur->_key<<"->"<<cur->_value<<"}"<<endl;
					cur = cur->_next;
				}
			}
			cout<<endl;
		}

	protected:
		size_t _HashFunc(const K& key)
		{
			//_table.size()表示哈希桶的空间大小，vector数组的大小
			return HashFunc()(key) % _table.size();
		}

		size_t _GetNextPrime() // 得到下一个扩容的素数
		{
			static const size_t _PrimeSize = 28;
			static const unsigned long _PrimeList [_PrimeSize] =
			{
				53ul,         97ul,         193ul,       389ul,       769ul,
				1543ul,       3079ul,       6151ul,      12289ul,     24593ul,
				49157ul,      98317ul,      196613ul,    393241ul,    786433ul,
				1572869ul,    3145739ul,    6291469ul,   12582917ul,  25165843ul,
				50331653ul,   100663319ul,  201326611ul, 402653189ul, 805306457ul,
				1610612741ul, 3221225473ul, 4294967291ul
			};
			for (size_t i = 0; i < _PrimeSize; i++)
			{
				if (_PrimeList[i] > _size)
				{
					return _PrimeList[i];
				}
			}
			return _PrimeList[_PrimeSize - 1];
		}

		void _CheckExpand()//扩容，容量都是素数
		{
			if(_size == _table.size())
			{
				size_t newSize = _GetNextPrime();
				vector<Node*> newTables;
				newTables.resize(newSize);

				//将每个单链表上的元素摘下来 挂到新链上
				for(size_t i = 0;i < _table.size();i++)
				{
					Node* cur = _table[i];
					while (cur)
					{
						//摘结点
						Node* temp = cur;
						cur = cur->_next;
						//挂结点
						size_t index = _HashFunc(temp->_key);
						temp->_next = newTables[index];
						newTables[index] = temp;
					}
					_table[i] = NULL;
				}
				swap(_table,newTables);
			}
		}

	protected:
		vector<Node*> _table;
		size_t _size;//数据个数
	};
}