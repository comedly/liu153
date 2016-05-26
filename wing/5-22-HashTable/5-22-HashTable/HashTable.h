#pragma once
#include<iostream>
#include<string>
using namespace std;

namespace First
{
	//����̽����ػ�������Դ����Զ������͵�����
	enum State
	{
		EMPTY,//��λ��δ���Ԫ��
		DELETE,//��λ�õ�Ԫ���ѱ�ɾ��
		EXITS,//��λ�ô���Ԫ��
	};

	//������ֵ  �º���
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
		//key��ʽ������̽��
	public:
		HashTable(size_t capacity = 10)
			:_table(new K[capacity])
			,_state(new State[capacity])
			,_size(0)
			,_capacity(capacity)
		{
			//memset(_state,EMPTY,sizeof(State)*capacity);������⣬��Ϊmemset�����ֽڳ�ʼ����
			for(size_t i = 0;i < _capacity;i++)
			{
				_state[i] = EMPTY;//ÿ��λ���ÿ�
			}
		}

		HashTable(const HashTable<K>& ht)//�������캯��
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

		HashTable& operator=(const HashTable<K>& ht)//��ֵ����
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

		//����̽������Ԫ�صĴ��λ�ã����費��ϣ��ͻ��
		int _HashFunc(const K& key)
		{
			__HashFunc<K> hf;
			return hf(key)%_capacity;
			//�����������operator()
			//return __HashFun<K>()(key)%_capacity;
		}

		bool Insert(const K& key)
		{
			//��̬��ϣ��
			if(_size == _capacity)
			{
				cout<<"HashTable is full!"<<endl;
				return false;
			}
			//��̬��ϣ��
			//��Ч�Ĺ�ϣ����غ����Ӵ���ȶ���0.7-0.8
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
			//��λ�ô��ڣ�����λ�ñ�ɾ���ˣ���Ҫ���ҵ��п����ں�ߣ���Ҫ������������
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
				if(index == start)//����һȦ��û���ҵ���ֹͣ����ֹ��ѭ��
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

		void Print()//��ӡ
		{
			for(int i = 0;i < _capacity;i++)
			{
				if(_state[i] == EXITS)
				{
					cout<<i<<"(EXITS)"<<_table[i]<<endl;
				}
				//��DELETE״̬�µ�Ԫ��Ҳ��ӡ���������ڹ۲�
				//��Insert����ʱ��DELETE״̬�µ�λ�ÿ��Բ����µ�Ԫ��
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

		void Swap(HashTable<K> temp) //����
		{
			swap(_size,temp._size);
			swap(_capacity,temp._capacity);
			swap(_state,temp._state);
			swap(_table,temp._table);
		}

	protected:
		void _CheckCapacity() //����
		{
			HashTable<K> temp(2*_capacity);
			for(int i = 0;i < _capacity;i++)
			{
				temp.Insert(_table[i]);
			}
			Swap(temp);
		}
		
	private:
		K* _table;//��ϣ��
		State* _state;//״̬��
		size_t _size;
		size_t _capacity;
	};
}

namespace Second
{
	//����̽����ػ�������Դ����Զ������͵�����
	enum State
	{
		EMPTY,//��λ��δ���Ԫ��
		DELETE,//��λ�õ�Ԫ���ѱ�ɾ��
		EXITS,//��λ�ô���Ԫ��
	};

	template<class K,class V>
	struct HashTableNode
	{
		K _key;
		V _value;
	};

	//�����������
	template<class K>
	struct __HashFunc//Ĭ�ϵķ��ع�ϣ��ֵhey�� �º���
	{
		size_t operator()(const K& key)
		{
			return key;
		}
	};

	//�ػ�string��__HashFunc �º���
	//�����Զ�������
	template<>
	struct __HashFunc<string>
	{
		//�±�����ȱ�㣬�����ظ���key���硰abcd���롰bcad��
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

	//ʵ�ֹ�ϣ���key/value��ʽ�Ķ���̽��
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
			//memset(_state,EMPTY,sizeof(State)*capacity);������⣬��Ϊmemset�����ֽڳ�ʼ����
			for(size_t i = 0;i < capacity;i++)
			{
				_state[i] = EMPTY;//ÿ��λ���ÿ�
			}
		}

		HashTable(const HashTable<K,V,HashFuncer>& ht)//�������캯��
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

		HashTable& operator=(const HashTable<K,V,HashFuncer>& ht)//��ֵ����
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

		//����̽������Ԫ�صĴ��λ�ã����費��ϣ��ͻ��
		int _HashFunc(const K& key)
		{
			HashFuncer hf;
			return hf(key)%_capacity;
			//�����������operator()
			//return __HashFun<K>()(key)%_capacity;
		}

		bool Insert(const K& key,const V& value)
		{
			//��̬��ϣ��
			//if(_size == _capacity)
			//{
			//	cout<<"HashTable is full!"<<endl;
			//	return false;
			//}

			//��̬��ϣ��
			//��Ч�Ĺ�ϣ����غ����Ӵ���ȶ���0.7-0.8
			if(_size*10/_capacity >= 7)
			{
				_CheckCapacity();
			}
			
			size_t hashKeyStart = _HashFunc(key);
			size_t add_more = 1;
			int index = hashKeyStart;
			//����̽��
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
			//��λ�ô��ڣ�����λ�ñ�ɾ���ˣ���Ҫ���ҵ��п����ں�ߣ���Ҫ������������
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
				if(index == start)//����һȦ��û���ҵ���ֹͣ����ֹ��ѭ��
				{
					return -1;
				}
			}
			return -1;
		}

		void FindKeyPrintToValue(int& ret)//����key��ֵ������value��ֵ����ӡ
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

		void Print()//��ӡ
		{
			for(int i = 0;i < _capacity;i++)
			{
				if(_state[i] == EXITS)
				{
					cout<<i<<"(EXITS)"<<_table[i]._key<<"--"<<_table[i]._value<<endl;
				}
				//��DELETE״̬�µ�Ԫ��Ҳ��ӡ���������ڹ۲�
				//��Insert����ʱ��DELETE״̬�µ�λ�ÿ��Բ����µ�Ԫ��
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

		void Swap(HashTable<K,V,HashFuncer> temp) //����
		{
			swap(_size,temp._size);
			swap(_capacity,temp._capacity);
			swap(_state,temp._state);
			swap(_table,temp._table);
		}

	protected:
		void _CheckCapacity() //����
		{
			HashTable<K,V,HashFuncer> temp(2*_capacity);
			for(int i = 0;i < _capacity;i++)
			{
				temp.Insert(_table[i]._key,_table[i]._value);
			}
			Swap(temp);
		}
		
	private:
		Node* _table;//��ϣ��
		State* _state;//״̬��
		size_t _size;//��ϣ����Ԫ�صĸ���
		size_t _capacity;//��ϣ�������
	};
}

namespace HashTableBucket
{
	template<class K,class V>
	struct HashTableNode
	{
		K _key;
		V _value;
		HashTableNode* _next;//����ϣ��ͻ,�������һ��λ�õ�����
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

		HashTableBucket(const HashTableBucket<K,V,HashFunc>& ht)//��������
		{
			//����ϣ��ht������this
			this->_table.resize(ht._table.size());//����һ��͹�ϣͰ��Сһ���Ŀռ�
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

		//��ֵ�����ִ�д��
		HashTableBucket<K,V> operator=(HashTableBucket<K,V> ht)//�˴��Ͳ�����const
		{
			if(this != &ht)
			{
				swap(_table,ht._table);
				swap(_size,ht._size);
			}
			return *this;
		}

		~HashTableBucket()//��������
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
			//�������
			_CheckExpand();

			size_t index = _HashFunc(key);
			Node* cur = _table[index];
			//��ֹ����
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

		Node* Find(const K& key)//����
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

		bool Remove(const K& key)//ɾ��
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
			//_table.size()��ʾ��ϣͰ�Ŀռ��С��vector����Ĵ�С
			return HashFunc()(key) % _table.size();
		}

		size_t _GetNextPrime() // �õ���һ�����ݵ�����
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

		void _CheckExpand()//���ݣ�������������
		{
			if(_size == _table.size())
			{
				size_t newSize = _GetNextPrime();
				vector<Node*> newTables;
				newTables.resize(newSize);

				//��ÿ���������ϵ�Ԫ��ժ���� �ҵ�������
				for(size_t i = 0;i < _table.size();i++)
				{
					Node* cur = _table[i];
					while (cur)
					{
						//ժ���
						Node* temp = cur;
						cur = cur->_next;
						//�ҽ��
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
		size_t _size;//���ݸ���
	};
}