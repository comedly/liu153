#include"proccess.h"

void process()
{
	int i = 1;
	char str[_SIZE_];
	memset(str,'\0',sizeof(str));
	str[_SIZE_ - 1] = '\0';
	str[_SIZE_ - 2] = ']';
	str[0] = '[';

	char index[5] = "-\\|/\0";
	while(i <= 100)
	{
		str[i] = '#';
		printf("%s[%d%%%c]\r",str,i,index[i%4]);
		fflush(stdout);
		usleep(10000);
	}
	printf("\n");
}
