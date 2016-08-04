/***************************************************************************
	>file name:String.h
	>author:Comedly 
	>create time:2016-8-3
***************************************************************************/

#pragma once
#include<assert.h>

//递归实现
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

//计数法
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

//指针法
size_t my_strlen3(const char* str)
{
	const char* p = str;
	while(*str != '\0')
	{
		str++;
	}
	return str - p;
}

//实现字符串的拷贝
char* my_strcpy(char* dest,const char* src)
{
	assert(dest);
	assert(src);
	char* ret = dest;
	while(*dest++ = *src++)
	{
		;
	}
	return ret;//返回第一个参数的一份拷贝，和一个指向目标字符串的指针
}

//连接字符串
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
	*dest = '\0';//结束标志
	return ret;//返回第一个参数的一份拷贝，即一个指向目标字符串的指针
}

//字符串的比较，如果str1小于str2，则返回一个小于0的值，大于的话，返回一个大于0的值，等于返回0
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

//长度受限的字符串函数

//拷贝长度为len的字符串
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

//连接长度为len的字符串
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

//比较两个字符串，但是最多比较len个字符，如果两个字符串再第len个字符之前存在不相等的字符，则就像strcmp一样的返回值，如果前len个字符都相等，则返回0
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

//字符串的查找
//该函数在字符串str中查找ch第一次出现的位置，若找到，返回一个指向改位置的指针，反之，返回NULL

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

//第一次只出现一次的字符
//利用哈希表实现
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

//该函数与strchr函数的基本功能一样，只是它返回的是一个指向该字符在字符串中最后一次出现的位置（右边的那个）

char* my_strrchr(char* str,int ch)
{
	register char* current = NULL;
	register char* last = NULL;

	if(ch != '\0')//只有ch不等与'\0'时才进行查找
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

//该函数返回一个指向str中第一个匹配group中任何一个字符的字符位置，若没找到，返回NULL
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

//再str1中查找整个str2第一次出现的起始位置，并返回一个指向改位置的指针
char* my_strstr1(char* str1,char* str2)//查找字符串
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

//在字符串s1中查找字符串s2整个最后一次出现的位置，返回一个指向该位置的指针。
char* my_strrstr(char* s1,char* s2)
{
	register char* current = NULL;
	register char* last = NULL;

	//将指针初始化为我们已经找到的前一次匹配的位置。
	//只在第二个字符串不为空时才进行查找，
	if(*s2 != '\0')
	{
		current = my_strstr1(s1,s2);
		//我们每次找到字符串时，让指针指向它的起始位置，然后查找该字符串的下一个匹配位置。
		while(current != NULL)
		{
			last = current;
			current = my_strstr1(last+1,s2);
		}
	}
	//返回指向我们找到的最后一次匹配的起始位置的指针。
	return last;
}

//内存拷贝函数
//从src的起始位置复制count个字节到dest的起始位置
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

//必须考虑内存是否有重叠
void* my_memmove(void* buf1,void* buf2,int count)
{
	char* dest = (char*)buf1;
	char* src = (char*)buf2;
	assert(buf1);
	assert(buf2);

	if((dest > src) && (dest < (src + count)))//有重叠则从后向前拷贝
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