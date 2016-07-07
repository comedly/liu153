#pragma once

#include<iostream>
#include<string>
#include<windows.h>
using namespace std;
#include"HuffmanTree.h"

typedef unsigned long LongType;

struct CharInfo
{
	unsigned char _ch;//�ַ�����
	LongType _count;//�ַ����ֵĸ���
	string _code;//�ַ���Ӧ�Ĺ���������

	CharInfo(const LongType count = 0)
		:_count(count)
	{ }

	CharInfo(const char ch)
		:_ch(ch)
	{ }

	bool operator!=(const CharInfo& c)const
	{
		return _count != c._count;
	}

	CharInfo operator+(const CharInfo& c)const
	{
		return CharInfo(_count + c._count);
	}

	bool operator<(const CharInfo& c)const
	{
		return _count < c._count;
	}
};

class FileCompress
{
public:
	FileCompress()
	{
		for(size_t i = 0;i < 256;i++)
		{
			_Info[i]._ch = i;
			_Info[i]._count = 0;
		}
	}

	void Compress(const char* filename)
	{
		FILE* fOut = fopen(filename,"rb");
		if(fOut == NULL)
		{
			cout<<"���ļ�ʧ��!"<<endl;
			return;
		}

		//1��ͳ���ļ����ַ����ֵĴ���
		char ch = fgetc(fOut);//fgetc()�������ļ�ָ��fOutָ����ļ��ж�ȡһ���ַ�����ȡ������Ƶ���һ���ַ�
		while (ch != EOF)
		{
			_Info[(unsigned char)ch]._count++;
			ch = fgetc(fOut);
		}

		//������������
		CharInfo invalid;
		HuffmanTree<CharInfo> tree(_Info,256,invalid);

		//����huffman����
		string code;
		GenerateHuffmanCode(tree.GetRootNode(),code);

		//ѹ��
		string compressFilename = filename;
		compressFilename += ".compress";
		FILE* fIn = fopen(compressFilename.c_str(),"wb");
		assert(fIn);

		fseek(fOut,0,SEEK_SET);//���¶����ļ�λ��ָ�룬��ʾ�ļ���ͷ��ƫ����Ϊ0
		ch = fgetc(fOut);
		unsigned char value = 0;//
		int size = 0;
		//while (ch != EOF)
		while (!feof(fOut))
		{
			const string& code = _Info[(unsigned char)ch]._code;
			for(size_t i =0;i < code.size();++i)
			{
				if(code[i] == '1')
				{
					value |= 1;
				}

				++size;

				if(size == 8)
				{
					fputc(value,fIn);
					value = 0;
					size = 0;
				}
				else
				{
				value <<= 1;
				}
			}
			ch = fgetc(fOut);
		}
		//��λ
		if(size > 0)
		{
			value <<= (7 - size);
			fputc(value,fIn);
		}
		//д�����ļ�
		string configFile = filename;
		configFile += ".config";
		FILE* fConfig = fopen(configFile.c_str(),"wb");

		string line;
		char buffer[128];
		for(size_t i = 0;i < 256;++i)
		{
			if(_Info[i]._count > 0)
			{
				line += _Info[i]._ch;
				line += ",";

				itoa(_Info[i]._count,buffer,10);
				line += buffer;
				line += '\n';
				fputs(line.c_str(),fConfig);
			}
			line.clear();
		}
		fclose(fOut);
		fclose(fConfig);
		fclose(fIn);
	}

	bool ReadLine(FILE* fOut,string& line)
	{
		char ch = fgetc(fOut);
		if (feof(fOut))
		{
			return false;
		}
		while(!feof(fOut) && ch != '\n')
		{
			line += ch;
			ch = fgetc(fOut);
		}
		return true;
	}

	void UnCompress(const char* filename)
	{
		//��ȡ�����ļ������ַ����ִ���
		string configFile = filename;
		configFile += ".config";
		FILE* fConfig = fopen(configFile.c_str(),"rb");//�Զ����ƶ�ȡ
		assert(fConfig);

		string line;
		while(ReadLine(fConfig,line))
		{
			if(line.empty())
			{
				line += '\n';
			}
			else
			{
				_Info[(unsigned char)line[0]]._count = atoi(line.substr(2).c_str());
				line.clear();
			}
		}
		//����HuffmanTree
		CharInfo invalid;
		HuffmanTree<CharInfo> tree(_Info,256,invalid);
		
		//��ȡѹ���ļ������л�ԭ
		string compressFile = filename;
		compressFile += ".compress";
		FILE* fOut = fopen(compressFile.c_str(), "rb");
		assert(fOut);

		HuffmanNode<CharInfo>* root = tree.GetRootNode();
		HuffmanNode<CharInfo>* cur = root;

		string uncompressFilename = filename;
		uncompressFilename += ".uncompress";
		FILE* fIn = fopen(uncompressFilename.c_str(),"wb");
		assert(fIn);

		LongType SumCount = tree.GetRootNode()->_weight._count;//

		char ch = fgetc(fOut);//ȡ�ļ���ÿһλ
		int pos = 7;
		while (!feof(fOut)) //feof �����ж��ļ��Ƿ�ִ�н��������������򷵻ط���ֵ
		{
			if(ch & (1<<pos))
			{
				cur = cur->_right;
			}
			else
			{
				cur = cur->_left;
			}
			if(cur->_left == NULL && cur->_right == NULL)
			{
				fputc((cur->_weight)._ch,fIn);
				if(--SumCount == 0)
				{
					break;
				}
				cur = root;
			}
			if(pos-- == 0)
			{
				ch = fgetc(fOut);
				pos = 7;
			}
		}
		fclose(fOut);
		fclose(fConfig);
		fclose(fIn);
	}

protected:
	//�õ�Huffman���룬���������Huffmantree��
	void GenerateHuffmanCode(HuffmanNode<CharInfo>* root,string code)
	{
		if(root == NULL)
			return;
		if(root->_left == NULL && root->_right == NULL)
		{
			_Info[root->_weight._ch]._code = code;
		}
		GenerateHuffmanCode(root->_left,code + '0');
		GenerateHuffmanCode(root->_right,code + '1');
	}

private:
	CharInfo _Info[256];
};

void TestFileCompress()
{
	FileCompress fc;
	int begin = GetTickCount();
	//fc.Compress("F:/GIT/liu153/HuffmanTree/Input");
	fc.Compress("F:/GIT/liu153/HuffmanTree/Input.BIG");	
	int end = GetTickCount();
	cout<<"�ļ�ѹ����ʱ��"<<end-begin<<endl;

	begin = GetTickCount();
	fc.UnCompress("F:/GIT/liu153/HuffmanTree/Input.BIG");
	end = GetTickCount();
	cout<<"��ѹ���ļ���ʱ��"<<end-begin<<endl;
}

//��Ŀ����
// 1��ѹ�����ļ�(��ȷ��)
// 2��ѹ������
// 3����Ŀ����
// 4����д��Ŀʱ����������