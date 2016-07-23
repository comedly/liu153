#include<iostream>
using namespace std;

//求一个数组中所有的数组合在一起，打印出组合数中值最小的那个
const int g_MaxNumberLength = 10;

char* g_StrCombine1 = new char[g_MaxNumberLength * 2 + 1];//组合数1
char* g_StrCombine2 = new char[g_MaxNumberLength * 2 + 1];//组合数2

int compare(const void* strNumber1,const void* strNumber2)//自定义两个数拼接后的大小
{
	strcpy(g_StrCombine1,*(const char**)strNumber1);
	strcat(g_StrCombine1,*(const char**)strNumber2);//strNumber1"+"strNumber2

	strcpy(g_StrCombine2,*(const char**)strNumber2);
	strcat(g_StrCombine2,*(const char**)strNumber1);//strNumber2"+"strNumber1

	return strcmp(g_StrCombine1,g_StrCombine2);
}

void PrintMinNumber(int* number,int length)//打印组合数中最小的那个组合
{
	if(number == NULL || length <= 0)
		return ;

	char** strNumber = (char**)(new int[length]);//开辟一个二维数组，每一行存储一个数
	for(int i = 0;i < length;++i)
	{
		strNumber[i] = new char[g_MaxNumberLength + 1];//多开辟一个空间存储'\0'
		sprintf(strNumber[i],"%d",number[i]);//将数组中的每一个数存储在二维数组中的每一行
	}

	qsort(strNumber,length,sizeof(char*),compare);

	for(int i = 0;i < length;++i)//打印最小的数
		printf("%s",strNumber[i]);
	printf("\n");

	for(int i = 0;i < length;++i)//释放二维数组空间
		delete[] strNumber[i];
	delete[] strNumber;
}

int main()
{
	int arr[] = {3,32,321};
	PrintMinNumber(arr,sizeof(arr)/sizeof(arr[0]));
	system("pause");
	return 0;
}