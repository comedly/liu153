#pragma once 
#include"BitMap.h"

//bloom filter��һ�ֿռ�Ч�ʺܸߵ���������ݽṹ���Ƕ�bitmap����չ��
//ԭ��
//��һ��Ԫ�ر����뼯��ʱ��ͨ��k����ϣ���������Ԫ��ӳ���һ��λ�����е�k���㣬��������1������ʱ��ֻ��Ҫ����Щ���ǲ��Ƕ���1�Ϳ��Բ鿴�ü������Ƿ������ˡ�
//�����Щ��������һ����0�����Ԫ���ƶ�������
//�������1�����Ԫ�ؿ��ܴ���

size_t _GetNextPrime(size_t size) // �õ���һ�����ݵ�����
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
		if (_PrimeList[i] > size)
		{
			return _PrimeList[i];
		}
	}
	return _PrimeList[_PrimeSize - 1];//���size���ڻ��ߵ��������������ݣ��ͷ��ر���������
}

//6���ַ�����ϣ�㷨
template<class T>
struct __HashFunc1
{
	size_t BKDHash(const char* str)
	{
		register size_t hash = 0;
		while (size_t ch = (size_t)*str++)
		{
			hash = hash * 131 + ch;//Ҳ���Գ���31��131��1313��131131��131313...
		}
	return hash;
	}
	size_t operator()(const T& key)
	{
		return BKDHash(key.c_str());
	}
};

template<class T>
struct __HashFunc2
{
	size_t SDBMHash(const char *str)
	{
		register size_t hash = 0;
		while (size_t ch = (size_t)*str++)
		{
			hash = 65599 * hash + ch;
		}
		return hash;
	}
	size_t operator()(const T& key)
	{
		return SDBMHash(key.c_str());
	}
};

template<class T>
struct __HashFunc3
{
	size_t RSHash(const char *str)
	{
		register size_t hash = 0;
		size_t magic = 63689;
		while (size_t ch = (size_t)*str++)
		{
			hash = magic * hash + ch;
			magic *= 378551;
		}
		return hash;
	}
	size_t operator()(const T& key)
	{
		return RSHash(key.c_str());
	}
};
template<class T>
struct __HashFunc4
{
	size_t JSHash(const char *str)
	{
		if(!*str)
			return 0;
		register size_t hash = 1315423911;
		while (size_t ch = (size_t)*str++)
		{
			hash ^= ((hash << 5) + ch + (hash >> 2));
		}
		return hash;
	}
	size_t operator()(const T& key)
	{
		return JSHash(key.c_str());
	}
};
template<class T>
struct __HashFunc5
{
	size_t DEKHash(const char *str)
	{
		if(!*str)
			return 0;
		register size_t hash = 1315423911;
		while (size_t ch = (size_t)*str++)
		{
			hash = ((hash << 5)^(hash >> 27))^ch;
		}
		return hash;
	}
	size_t operator()(const T& key)
	{
		return DEKHash(key.c_str());
	}
};

template<class T = string,
			class HashFunc1 = __HashFunc1<T>,
			class HashFunc2 = __HashFunc2<T>,
			class HashFunc3 = __HashFunc3<T>,
			class HashFunc4 = __HashFunc4<T>,
			class HashFunc5 = __HashFunc5<T>>
class BloomFilter
{
public:
	BloomFilter(size_t capacity = 0)
	{
		_capacity = _GetNextPrime(capacity);
		_bm.Resize(capacity);
	}

	void Set(const T& key)
	{
		size_t index1 = HashFunc1()(key);
		size_t index2 = HashFunc2()(key);
		size_t index3 = HashFunc3()(key);
		size_t index4 = HashFunc4()(key);
		size_t index5 = HashFunc5()(key);
		_bm.Set(index1 % _capacity);
		_bm.Set(index2 % _capacity);
		_bm.Set(index3 % _capacity);
		_bm.Set(index4 % _capacity);
		_bm.Set(index5 % _capacity);
	}

	bool Test(const T& key)
	{
		size_t index1 = HashFunc1()(key);
		if(!(_bm.Test(index1 % _capacity)))
		{
			return false;
		}

		size_t index2 = HashFunc2()(key);
		if(!(_bm.Test(index2 % _capacity)))
		{
			return false;
		}

		size_t index3 = HashFunc3()(key);
		if(!(_bm.Test(index3 % _capacity)))
		{
			return false;
		}

		size_t index4 = HashFunc4()(key);
		if(!(_bm.Test(index4 % _capacity)))
		{
			return false;
		}

		size_t index5 = HashFunc5()(key);
		if(!(_bm.Test(index5 % _capacity)))
		{
			return false;
		}
		return true;
	}

protected:
	BitMap _bm;
	size_t _capacity;//��¡������������
};

void TestBloomFilter()
{
	BloomFilter<> bf(50);
	bf.Set("seek");
	bf.Set("bloomfilter");
	bf.Set("http://172.16.0.88/srun_portal_pc_succeed.php");

	cout<<"Is exist ? : "<<bf.Test("liulong")<<endl;
	cout<<"Is exist ? : "<<bf.Test("seek")<<endl;
	cout<<"Is exist ? : "<<bf.Test("http://172.16.0.88/srun_portal_pc_succeed.php")<<endl;
	cout<<"Is exist ? : "<<bf.Test("bloomfilter")<<endl;
	cout<<"Is exist ? : "<<bf.Test("hanghagn")<<endl;
}