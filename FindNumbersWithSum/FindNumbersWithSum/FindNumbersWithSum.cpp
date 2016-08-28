#include<iostream>
using namespace std;

bool FindNumbersWithSum(int data[],int length,int Sum,int* num1,int* num2)
{
	bool found = false;
	if(data == NULL || num1 == NULL || num2 == NULL)
		return found;

	int begin = 0;
	int end = length - 1;

	while (begin < end)
	{
		long long CurSum = data[begin] + data[end];

		if(CurSum == Sum)
		{
			*num1 = data[begin];
			*num2 = data[end];
			found = true;
			break;
		}
		else if(CurSum > Sum)
		{
			end--;
		}
		else
		{
			begin++;
		}
	}
	return found;
}

int main()
{
	int array[] = {1,2,4,7,11,15};
	int length = sizeof(array)/sizeof(array[0]);
	int num1,num2;
	if(FindNumbersWithSum(array,length,16,&num1,&num2))
		cout<<"num1:"<<num1<<" "<<"num2:"<<num2<<endl;
	else
	{
		cout<<"ц╩спур╣╫!"<<endl;
	}
	
	system("pause");
	return 0;
}