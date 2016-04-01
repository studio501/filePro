#ifndef __HASHTABLE__HH__
#define __HASHTABLE__HH__
#include <malloc.h>
#include <process.h>

#include <iostream>
#include <fstream>
#include <functional>
#include "commonFunc.h"

using namespace std;

int hashsize[]={11,19,29,37};
int m=0;

template<class HD>
struct HashTable
{
	HD *elem;
	int count;
	int sizeindex;
};

#define SUCCESS 1
#define UNSUCCESS 0
#define DUPLICATE -1

#define HASHTABLE HashTable<HD>

template<class HD>
void initHashTable(HASHTABLE &H)
{
	int i;
	H.count=0;
	H.sizeindex=0;
	m=hashsize[0];
	H.elem=(HD*)malloc(m*sizeof(HD));
	if(!H.elem) exit(OVERFLOW);
	for(i=0;i<m;++i)
		H.elem[i].key=NULL_KEY;
}

template<class HD>
void destroyHashTable(HASHTABLE &H)
{
	free(H.elem);
	H.elem=NULL;
	H.count=0;
	H.sizeindex=0;
}

unsigned Hash(keyType k)
{
	return k%m;
}

void collision(int &p,int d)
{
	p=(p+d)%m;
}

template<class HD>
bool searchHash(HASHTABLE H,keyType k,int &p,int &c)
{
	p=Hash(k);
	while(H.elem[p].key!=NULL_KEY&&!EQ(k,H.elem[p].key))
	{
		++c;
		if(c<m)
			collision(p,c);
		else
			break;
	}
	if EQ(k,H.elem[p].key)
		return SUCCESS;
	else return UNSUCCESS;
}

template<class HD>
bool insertHash(HASHTABLE &H,HD e);

template<class HD>
void recreateHashTable(HASHTABLE &H)
{
	int i,count=H.count;
	HD *p,*elem=(HD*)malloc(sizeof(HD)*count);
	p=elem;
	printf("重建哈希表\n");
	for(i=0;i<m;++i)
		if((H.elem+i)->key!=NULL_KEY)
			*p++=*(H.elem+i);
	H.count=0;
	++H.sizeindex;
	m=hashsize[H.sizeindex];
	p=(HD*)realloc(H.elem,m*sizeof(HD));
	if(!p) exit(OVERFLOW);
	H.elem=p;
	for(i=0;i<m;++i)
		H.elem[i].key=NULL_KEY;
	for(p=elem;p<elem+count;++p)
		insertHash(H,*p);
}


template<class HD>
bool insertHash(HASHTABLE &H,HD e)
{
	int c,p;
	c=0;
	if(searchHash(H,e.key,p,c))
		return DUPLICATE;
	else if(c<hashsize[H.sizeindex]/2)
	{
		H.elem[p]=e;
		++H.count;
		return true;
	}
	else
	{
		recreateHashTable(H);
		return UNSUCCESS;
	}
}

template<class HD>
void traverseHash(HASHTABLE H,const std::function<void(int ,const HD &)> &Vi)
{
	printf("哈希地址0～%d\n",m-1);
	for(int i=0;i<m;++i)
		if(H.elem[i].key!=NULL_KEY)
			Vi(i,H.elem[i]);
}

template<class HD>
bool find(HASHTABLE H,keyType k,int &p)
{
	int c=0;
	p=Hash(k);
	while(H.elem[p].key!=NULL_KEY&&!EQ(k,H.elem[p].key))
	{
		++c;
		if(c<m)
			collision(p,c);
		else
			return UNSUCCESS;
	}
	if EQ(k,H.elem[p].key)
		return SUCCESS;
	else 
		return UNSUCCESS;
}

#endif // !__HASHTABLE__HH__
