#pragma once
#include<iostream>
#include<vector>
#include<string>
using namespace std;

namespace First
{
	//线性探测的特化处理可以处理自定义类型的数据
	enum State
	{
		EMPTY,//该位置未放置元素
		DELETE,//该位置的元素已被删除
		EXIST,//该位置的元素存在
	};

	//产生键值 仿函数
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
		HashTable(size_t capacity = 10)//构造函数
			:_table(new K[capacity])
			,_state(new State[capacity])
			,_size(0)
			,_capacity(capacity)
		{
			//memset(_state,EMPTY,sizeof(State)*capacity);会出现问题，因为memset是以字节初始化的。
			for(size_t i = 0;i < _capacity;i++)
			{
				_state[i] = EMPTY;//每一个位置置空
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
				if(ht._state[i] == EXIST)
				{
					Insert(ht._state[i]);
				}
			}
		}

		HashTable& operator=(const HashTable<K>& ht)//赋值函数
		{
			if(ht._table != _table && ht._state != _state)
			{
				HashTable<K> temp(ht);
				swap(temp);
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
			//return __hashFUN<K>(key)%_capacity;
		}

		bool Insert(const K& key)
		{
			//静态哈希表
			if(_size == _capacity)
			{
				cout<<"hashTable is full"<<endl;
				return false;
			}
			//动态哈希表
			//高效的哈希表的载荷因子大概稳定在0.7-0.8
			if(_size*10/_capacity >= 7)
			{
				_CheckCapacity();
			}

			int index = _HashFunc(key);
			while (_state[index] == EXIST)
			{
				index++;
				if(index == _capacity)
				{
					index = 0;
				}
			}
			_table[index] = key;
			_state[index] = EXIST;
			_size++;
			return true;
		}

		int Find(const K& key)
		{
			size_t index = _HashFunc(key);
			size_t start = index;
			//该位置存在，若该元素被删除了，需要查找的有可能在后边，需要跳过继续查找。
			while (EMPTY != _state[index])
			{
				if(_table[index] == key)
				{
					if(_state[index] == EXIST)
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
				if(index == start)//查找一圈后，没找到就停止，防止死循环。
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
			for(size_t i = 0;i < _capacity;i++)
			{
				if(_state[i] == EXIST)
				{
					cout<<i<<"(EXIST)"<<_table[i]<<endl;
				}
				//将DELETE状态下的元素也打印出来，便于观察
				//而Insert处理时，DELETE状态下的位置也可以插入新的元素
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

		void Swap(HashTable<K> temp)//交换
		{
			swap(_size,temp._size);
			swap(_capacity,temp._capacity);
			swap(_state,temp._state);
			swap(_table,temp._table);
		}

	protected:
		void _CheckCapacity()//扩容
		{
			HashTable<K> temp(2*_capacity);
			for(size_t i = 0;i < _capacity;i++)
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

