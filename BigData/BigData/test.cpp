#include"BigData.h"

void Test1()
{
	//char* cstr;
	//string str("Please split this phrase into tokens");
	//cstr = new char [str.size()+1];
	//strcpy (cstr, str.c_str());
	//cout<<cstr<<endl;
	//cout<<str.c_str()<<endl;
	//cout<<str.size()<<endl;
	//cout<<'7'-'0'<<endl;
	/*cout<<atoi("        ")<<endl;
	cout<<atoi("+1233311")<<endl;
	cout<<atoi("000001234567890")<<endl;
	cout<<atoi("1234jhsd67890")<<endl;
	cout<<atoi("123456abcd")<<endl;
	cout<<atoi("-1234567890")<<endl;
	cout<<atoi("abcdef1234567890")<<endl;*/
	//BigData bigd("0");

}

void Test2()
{
	//BigData bigD1(-1212121332445740);
	//BigData bigD2("-002343004356783400234543678564234567890");
	//BigData bigD3(bigD1+bigD2);

	//BigData bigD4("1000000000000000000000000000000000000000000");
	//BigData bigD5("999999999999999999999999999999999999999999");
	//BigData bigD6(bigD4 - bigD5);

	BigData bigD4("123450");
	BigData bigD5("12345678907");
	BigData bigD6(bigD4*bigD5);
	cout<<bigD6<<endl;
	//BigData bigdata1("11111111111111111111111111111111111111111");
	//BigData bigdata2("9999999999999999999999999999999999999999999999999999999");
	//BigData bigdata3(bigdata1-bigdata2);
	//BigData bigdata1("123456123234341234213313142435243");
	//BigData bigdata2("-1231231122654464413545323123");
	//BigData bigdata3(bigdata1 * bigdata2);
	//BigData bigdata1("-128");
	//BigData bigdata2("2");
	//BigData bigdata3(bigdata1/bigdata2);
	//cout<<bigdata3<<endl;
}

int main()
{
	//Test1();
	Test2();
	system("pause");
	return 0;
}