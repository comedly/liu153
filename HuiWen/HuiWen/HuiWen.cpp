#include <iostream>
using namespace std;

//�ַ����ǻ��ģ�����true���񣬷���false

bool Huiwen(char*s)
{
	char *p=s,*q=s;
	char *L=0; //ָ��������ŵ�ǰһ��λ��
	int len=0; //��¼�ִ������ַ�����
	while (*(p+1) != '\0')
	{
		p++;
		len++;
	}
	L=p;//Lָ��������ŵ�ǰһ��λ��
	while (*q==' ') //��ͷ�Ŀո�����ȥ
	{
		q++; //ÿ�ƶ�һ����len�ĳ��ȼ�1
		len--;
	}
	while ((*q==*L || abs(*q-*L)==32) && len>=0 ) //��ǰ�������ַ���Ȼ���һ���Ǵ�дһ����Сд����δ������ʱ�����ű���
	{  
		q++;
		len--;
		L--;
		len--;
		while(*q==' ')
		{
			q++;
			len--;
		}
		while (*L==' ')
		{
			L--;
			len--;
		}
	}
	if (len<0) //����ַ����������ˣ�˵���ǻ���
		return true;
	else
		return false;
}

int main(){
	char a[]="A man a plan a canal panama";
	if (Huiwen(a))
		cout<<"this is huiwen\n";
	else
		cout<<"this is not huiwen\n";
	system("pause");
	return 0;
}