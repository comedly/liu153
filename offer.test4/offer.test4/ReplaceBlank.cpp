#include<iostream>
using namespace std;


//lengthΪ�ַ�����String��������
void ReplaceBlank(char String[],int length)
{
	if(String == NULL || length <= 0)
		return;
	int OriginalLength = 0;//��¼String��ʵ�ʳ���
	int NumberOfBlank = 0;//��¼�ַ����еĿո���
	int i = 0;
	while(String[i] != '\0')//�����ַ���ͳ�ƿո�ĸ���
	{
		++OriginalLength;
		if(String[i] == ' ')
			++NumberOfBlank;
		++i;
	}
	//NewLength��¼�ѿո񻻳�%20���ַ����ĳ���
	int NewLength = OriginalLength + 2*NumberOfBlank;
	if(NewLength > length)
		return;
	int indexOfOriginal = OriginalLength;//��¼ԭʼ�ַ������±�
	int indexOfNew = NewLength;//��¼�滻����ַ������±�
	while (indexOfOriginal >= 0 && indexOfNew > indexOfOriginal)//�Ӻ���ǰ���ƣ������ո�ת��Ϊ%20
	{
		if(String[indexOfOriginal] == ' ')
		{
			String[indexOfNew--] = '0';
			String[indexOfNew--] = '2';
			String[indexOfNew--] = '%';
		}
		else
		{
			String[indexOfNew--] = String[indexOfOriginal];
		}
		--indexOfOriginal;
	}
}

int main()
{
	char Array[50] = "we are happy.";
	ReplaceBlank(Array,50);
	cout<<Array<<endl;
	system("pause");
	return 0;
}
