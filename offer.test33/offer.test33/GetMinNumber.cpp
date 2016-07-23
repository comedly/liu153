#include<iostream>
using namespace std;

//��һ�����������е��������һ�𣬴�ӡ���������ֵ��С���Ǹ�
const int g_MaxNumberLength = 10;

char* g_StrCombine1 = new char[g_MaxNumberLength * 2 + 1];//�����1
char* g_StrCombine2 = new char[g_MaxNumberLength * 2 + 1];//�����2

int compare(const void* strNumber1,const void* strNumber2)//�Զ���������ƴ�Ӻ�Ĵ�С
{
	strcpy(g_StrCombine1,*(const char**)strNumber1);
	strcat(g_StrCombine1,*(const char**)strNumber2);//strNumber1"+"strNumber2

	strcpy(g_StrCombine2,*(const char**)strNumber2);
	strcat(g_StrCombine2,*(const char**)strNumber1);//strNumber2"+"strNumber1

	return strcmp(g_StrCombine1,g_StrCombine2);
}

void PrintMinNumber(int* number,int length)//��ӡ���������С���Ǹ����
{
	if(number == NULL || length <= 0)
		return ;

	char** strNumber = (char**)(new int[length]);//����һ����ά���飬ÿһ�д洢һ����
	for(int i = 0;i < length;++i)
	{
		strNumber[i] = new char[g_MaxNumberLength + 1];//�࿪��һ���ռ�洢'\0'
		sprintf(strNumber[i],"%d",number[i]);//�������е�ÿһ�����洢�ڶ�ά�����е�ÿһ��
	}

	qsort(strNumber,length,sizeof(char*),compare);

	for(int i = 0;i < length;++i)//��ӡ��С����
		printf("%s",strNumber[i]);
	printf("\n");

	for(int i = 0;i < length;++i)//�ͷŶ�ά����ռ�
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