#pragma once
#include<iostream>
#include<vector>
#include<string>
using namespace std;

namespace First
{
	//����̽����ػ�������Դ����Զ������͵�����
	enum State
	{
		EMPTY,//��λ��δ����Ԫ��
		DELETE,//��λ�õ�Ԫ���ѱ�ɾ��
		EXIST,//��λ�õ�Ԫ�ش���
	};

	//������ֵ �º���
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
		HashTable(size_t capacity = 10)//���캯��
			:_table(new K[capacity])
			,_state(new State[capacity])
			,_size(0)
			,_capacity(capacity)
		{
			//memset(_state,EMPTY,sizeof(State)*capacity);��������⣬��Ϊmemset�����ֽڳ�ʼ���ġ�
			for(size_t i = 0;i < _capacity;i++)
			{
				_state[i] = EMPTY;//ÿһ��λ���ÿ�
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
				if(ht._state[i] == EXIST)
				{
					Insert(ht._state[i]);
				}
			}
		}

		HashTable& operator=(const HashTable<K>& ht)//��ֵ����
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

		//����̽������Ԫ�صĴ��λ�ã����費��ϣ��ͻ��
		int _HashFunc(const K& key)
		{
			__HashFunc<K> hf;
			return hf(key)%_capacity;
			//�����������operator()
			//return __hashFUN<K>(key)%_capacity;
		}

		bool Insert(const K& key)
		{
			//��̬��ϣ��
			if(_size == _capacity)
			{
				cout<<"hashTable is full"<<endl;
				return false;
			}
			//��̬��ϣ��
			//��Ч�Ĺ�ϣ����غ����Ӵ���ȶ���0.7-0.8
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
			//��λ�ô��ڣ�����Ԫ�ر�ɾ���ˣ���Ҫ���ҵ��п����ں�ߣ���Ҫ�����������ҡ�
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
				if(index == start)//����һȦ��û�ҵ���ֹͣ����ֹ��ѭ����
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
			for(size_t i = 0;i < _capacity;i++)
			{
				if(_state[i] == EXIST)
				{
					cout<<i<<"(EXIST)"<<_table[i]<<endl;
				}
				//��DELETE״̬�µ�Ԫ��Ҳ��ӡ���������ڹ۲�
				//��Insert����ʱ��DELETE״̬�µ�λ��Ҳ���Բ����µ�Ԫ��
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

		void Swap(HashTable<K> temp)//����
		{
			swap(_size,temp._size);
			swap(_capacity,temp._capacity);
			swap(_state,temp._state);
			swap(_table,temp._table);
		}

	protected:
		void _CheckCapacity()//����
		{
			HashTable<K> temp(2*_capacity);
			for(size_t i = 0;i < _capacity;i++)
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

