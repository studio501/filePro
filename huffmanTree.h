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

//返回i个结点中权值最小的树的根结点序号
int min(HuffmanTree t,int i);

//在i个结点中选择2个权值最小的树的根结点序号,s1为其中序号小的那个
void select(HuffmanTree t,int i,int &s1,int &s2);

//构造huffman树
void huffmanCoding(HuffmanTree &HT,HuffmanCode &HC,int *w,int n);

//获取树数值
void getWeightArr(int * &w,int &len,int nLine=1,const char * hfile = "huffman.txt");
//构造huffman树
void huffmanCoding1(HuffmanTree &HT,HuffmanCode &HC,int *w,int n);
#endif




