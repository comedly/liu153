#include"HashTable.h"
#include"BitMap.h"
#include"BloomFilter.h"

void TestHash1()
{
	First::HashTable<int> ht1;
	
	ht1.Insert(28);
	ht1.Insert(11);
	ht1.Insert(49);
	ht1.Insert(57);
	ht1.Insert(39);
	ht1.Print();
	cout<<endl;
	First::HashTable<int> ht2(ht1);
	First::HashTable<int> ht3 = ht1;
	ht2.Print();
	cout<<endl;
	ht3.Print();
}

void TestHash2()
{
	First::HashTable<int> ht1;
	
	ht1.Insert(28);
	ht1.Insert(11);
	ht1.Insert(49);
	ht1.Insert(57);
	ht1.Insert(39);
	ht1.Print();
	cout<<ht1.Find(57)<<endl;
	ht1.Remove(57);
	ht1.Print();
}

void TestDict()
{ 
	using namespace Second;
	HashTable<string,string> dict;
	dict.Insert("dict","×Öµä");
	dict.Insert("hash","¹şÏ£");
	dict.Insert("function","º¯Êı");
	dict.Insert("abcd","º¯Êı");
	dict.Print();
	cout<<endl;
	int ret = dict.Find("hash");
	if(ret != -1)
	{
		cout<<"hashµÄÖĞÎÄ£º";
		dict.FindKeyPrintToValue(ret);
	}

	dict.Remove("abcd");
	dict.Print();
}

void TestHashTableBucket1()
{
	HashTableBucket::HashTableBucket<int,string> ht1;
	ht1.Insert(51,"¿ª·â");
	ht1.Insert(105,"¼òÌå");
	ht1.Insert(52,"²âÊÔ");
	ht1.Insert(3,"¹şÏ£");
	ht1.Insert(55,"¿ª·â");
	ht1.Insert(2,"×Öµä");
	ht1.Insert(106,"seek");
	ht1.Insert(53,"liu");
	ht1.Insert(0,"ipad");
	ht1.PrintHashTable();

	ht1.Find(2);
	ht1.Remove(2);
	ht1.PrintHashTable();

	cout<<endl;
	HashTableBucket::HashTableBucket<int,string> ht2(ht1);
	ht2.PrintHashTable();
}

void TestHashTableBucket2()
{
	HashTableBucket::HashTableBucket<int,string> ht1;
	ht1.Insert(51,"¿ª·â");
	ht1.Insert(105,"¼òÌå");
	ht1.Insert(52,"²âÊÔ");
	ht1.Insert(3,"¹şÏ£");
	ht1.Insert(55,"¿ª·â");
	ht1.Insert(2,"×Öµä");
	ht1.Insert(106,"seek");
	ht1.Insert(53,"liu");
	ht1.Insert(0,"ipad");
	ht1.PrintHashTable();
	cout<<endl;

	HashTableBucket::HashTableBucket<int,string> ht2(ht1);
	ht2.PrintHashTable();
	cout<<endl;

	HashTableBucket::HashTableBucket<int,string> ht3 = ht1;
	ht3.PrintHashTable();
}

int main()
{
	//TestHash1();
	//TestHash2();
	//TestDict();
	//TestHashTableBucket1();
	//TestHashTableBucket2();
	//TestBitMap();
	TestBloomFilter();
	system("pause");
	return 0;
}