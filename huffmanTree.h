#ifndef __HUFFMANTREE__HH__
#define __HUFFMANTREE__HH__
#include <malloc.h>
#include <process.h>

#include <iostream>
#include <fstream>
#include <stdarg.h>
#include "commonFunc.h"
using namespace std;

#define MAX_LINE_SIZE 100
typedef struct 
{
	unsigned int weight;
	unsigned int parent,lchild,rchild;
}HTNode,*HuffmanTree;
typedef char **HuffmanCode;

//����i�������Ȩֵ��С�����ĸ�������
int min(HuffmanTree t,int i);

//��i�������ѡ��2��Ȩֵ��С�����ĸ�������,s1Ϊ�������С���Ǹ�
void select(HuffmanTree t,int i,int &s1,int &s2);

//����huffman��
void huffmanCoding(HuffmanTree &HT,HuffmanCode &HC,int *w,int n);

//��ȡ����ֵ
void getWeightArr(int * &w,int &len,int nLine=1,const char * hfile = "huffman.txt");
//����huffman��
void huffmanCoding1(HuffmanTree &HT,HuffmanCode &HC,int *w,int n);
#endif




