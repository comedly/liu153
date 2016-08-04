/***************************************************************************
	>file name:String.h
	>author:Comedly 
	>create time:2016-8-3
***************************************************************************/

#pragma once
#include<assert.h>

//�ݹ�ʵ��
size_t my_strlen1(char* str)
{
	if(*str != '\0')
	{
		return 1+my_strlen1(str+1);
	}
	else
	{
		return 0;
	}
}

//������
size_t my_strlen2(char* str)
{
	size_t count = 0;
	while(*str != '\0')
	{
		count++;
		str++;
	}
	return count;
}

//ָ�뷨
size_t my_strlen3(const char* str)
{
	const char* p = str;
	while(*str != '\0')
	{
		str++;
	}
	return str - p;
}

//ʵ���ַ����Ŀ���
char* my_strcpy(char* dest,const char* src)
{
	assert(dest);
	assert(src);
	char* ret = dest;
	while(*dest++ = *src++)
	{
		;
	}
	return ret;//���ص�һ��������һ�ݿ�������һ��ָ��Ŀ���ַ�����ָ��
}

//�����ַ���
char* my_strcat(char* dest,const char* src)
{
	char* ret = dest;
	assert(dest);
	assert(src);
	while(*dest)
	{
		dest++;
	}
	while(*src)
	{
		*dest++ = *src++;
	}
	*dest = '\0';//������־
	return ret;//���ص�һ��������һ�ݿ�������һ��ָ��Ŀ���ַ�����ָ��
}

//�ַ����ıȽϣ����str1С��str2���򷵻�һ��С��0��ֵ�����ڵĻ�������һ������0��ֵ�����ڷ���0
int my_strcmp(const char* str1,const char* str2)
{
	while(*str1 == *str2)
	{
		if(*str1 == '\0')
			return 0;
		str1++;
		str2++;
	}
	return 0;
}

//�������޵��ַ�������

//��������Ϊlen���ַ���
char* my_strncpy(char* dest,const char* src,size_t len)
{
	char* ret = dest;
	assert(dest);
	assert(src);

	while(len--)
	{
		*dest++ = *src++;
	}
	*dest = '\0';
	return ret;
}

//���ӳ���Ϊlen���ַ���
char* my_strncat(char* dest,const char* src,size_t len)
{
	char* ret = dest;
	assert(dest);
	assert(src);

	while(*dest != '\0')
	{
		dest++;
	}

	while((len > 0) && ((*dest++ = *src++) != '\0'))
	{
		len--;
	}
	*dest = '\0';
	return ret;
}

//�Ƚ������ַ������������Ƚ�len���ַ�����������ַ����ٵ�len���ַ�֮ǰ���ڲ���ȵ��ַ��������strcmpһ���ķ���ֵ�����ǰlen���ַ�����ȣ��򷵻�0
//
int my_strncmp(const char* str1,const char* str2,size_t len)
{
	assert(str1);
	assert(str2);

	while(((len--)>0) && (*str1 != '\0') && (*str2 != '\0'))
	{
		if(*str1 == *str2)
		{
			str1++;
			str2++;
		}
		else
		{
			return *str1 - *str2 - '\0';
		}
	}
	return *str1 - *str2 - '\0';
}

//�ַ����Ĳ���
//�ú������ַ���str�в���ch��һ�γ��ֵ�λ�ã����ҵ�������һ��ָ���λ�õ�ָ�룬��֮������NULL

char* my_strchr(char* str,int ch)
{
	char* ret = str;
	assert(str);
	while(*ret != '\0')
	{
		if(*ret == ch)
			return ret;
		ret++;
	}
	return NULL;
}

//��һ��ֻ����һ�ε��ַ�
//���ù�ϣ��ʵ��
char FirstNotRepeatChar(char* str)
{
	if(str == NULL)
	{
		return '\0';
	}
	const int HashSize = 256;
	unsigned int HashTable[HashSize];
	for(unsigned int i = 0;i < 256;i++)
	{
		HashTable[i] = 0;
	}

	char* ptr = str;
	while(*ptr != '\0')
	{
		HashTable[*ptr]++;
		ptr++;
	}

	ptr = str;
	while(*ptr != '\0')
	{
		if(HashTable[*ptr] == 1)
			return *ptr;
		ptr++;
	}
	return '\0';
}

//�ú�����strchr�����Ļ�������һ����ֻ�������ص���һ��ָ����ַ����ַ��������һ�γ��ֵ�λ�ã��ұߵ��Ǹ���

char* my_strrchr(char* str,int ch)
{
	register char* current = NULL;
	register char* last = NULL;

	if(ch != '\0')//ֻ��ch������'\0'ʱ�Ž��в���
	{
		current = my_strchr(str,ch);
		while(current != NULL)
		{
			last = current;
			current = my_strchr(last+1,ch);
		}
	}
	return last;
}

//�ú�������һ��ָ��str�е�һ��ƥ��group���κ�һ���ַ����ַ�λ�ã���û�ҵ�������NULL
char* my_strpbrk(char* str,char* group)
{
	register char* s1 = str;
	register char* s2 = group;
	assert(str);
	assert(group);

	while(*s1 != '\0')
	{
		while(*s2 != '\0')
		{
			if(*s1 == *s2)
			{
				return s1;
			}
			else
			{
				s2++;
			}
		}
		s2 = group;
		s1++;
	}
	return NULL;
}

//��str1�в�������str2��һ�γ��ֵ���ʼλ�ã�������һ��ָ���λ�õ�ָ��
char* my_strstr1(char* str1,char* str2)//�����ַ���
{
	char* ptr = str1;
	char* p1 = NULL;
	char* p2 = NULL;

	while(*ptr != '\0')
	{
		p1 = ptr;
		p2 = str2;
		while(*p1 == *p2)
		{
			++p1;
			++p2;
			if(*p2 == '\0')
			{
				return ptr;
			}
		}
		ptr++;
	}
	return NULL;
}

//���ַ���s1�в����ַ���s2�������һ�γ��ֵ�λ�ã�����һ��ָ���λ�õ�ָ�롣
char* my_strrstr(char* s1,char* s2)
{
	register char* current = NULL;
	register char* last = NULL;

	//��ָ���ʼ��Ϊ�����Ѿ��ҵ���ǰһ��ƥ���λ�á�
	//ֻ�ڵڶ����ַ�����Ϊ��ʱ�Ž��в��ң�
	if(*s2 != '\0')
	{
		current = my_strstr1(s1,s2);
		//����ÿ���ҵ��ַ���ʱ����ָ��ָ��������ʼλ�ã�Ȼ����Ҹ��ַ�������һ��ƥ��λ�á�
		while(current != NULL)
		{
			last = current;
			current = my_strstr1(last+1,s2);
		}
	}
	//����ָ�������ҵ������һ��ƥ�����ʼλ�õ�ָ�롣
	return last;
}

//�ڴ濽������
//��src����ʼλ�ø���count���ֽڵ�dest����ʼλ��
void* my_memcpy(void* dest,void* src,int count)
{
	char* buf1 = (char*)dest;
	char* buf2 = (char*)src;
	assert(dest);
	assert(src);
	while(count--)
	{
		*buf1++ = *buf2++;
	}
	return dest;
}

//���뿼���ڴ��Ƿ����ص�
void* my_memmove(void* buf1,void* buf2,int count)
{
	char* dest = (char*)buf1;
	char* src = (char*)buf2;
	assert(buf1);
	assert(buf2);

	if((dest > src) && (dest < (src + count)))//���ص���Ӻ���ǰ����
	{
		while(count--)
		{
			*(dest + count) = *(src + count);
		}
	}
	else
	{
		while(count--)
		{
			*dest++ = *src++;
		}
	}
	return buf1;
}