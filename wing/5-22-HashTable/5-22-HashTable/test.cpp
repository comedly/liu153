#include"HashTable.h"

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
	dict.Insert("dict","字典");
	dict.Insert("hash","哈希");
	dict.Insert("function","函数");
	dict.Insert("abcd","函数");
	dict.Print();
	cout<<endl;
	int ret = dict.Find("hash");
	if(ret != -1)
	{
		cout<<"hash的中文：";
		dict.FindKeyPrintToValue(ret);
	}

	dict.Remove("abcd");
	dict.Print();
}

int main()
{
	//TestHash1();
	//TestHash2();
	TestDict();
	system("pause");
	return 0;
}