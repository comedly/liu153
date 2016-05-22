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
		K* _table;//��ϣ��
		State* _state;//״̬��
		size_t _size;//��ϣ����Ԫ�صĸ���
		size_t _capacity;//��ϣ�������
	};
}