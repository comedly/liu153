#include<iostream>
using namespace std;

int func(int n)
{
	int count = 0;
	while(n)
	{
		count++;
		n = n&(n-1);
	}
	return count;
}

void func2()
{
	int m,w=2,x=2,y=3,z=4;
	m=(w<x)?w:x;
	m=(m<y)?m:y;
	m=(m<2)?m:z;
	cout<<"m="<<m<<endl;
}

int main()
{
	//int ret = func(9999);
	//int ret = func(13599);
	func2();
	//cout<<ret<<endl;
	system("pause");
	return 0;
}