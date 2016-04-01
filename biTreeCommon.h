#ifndef __BITREECOMMON__HH__
#define __BITREECOMMON__HH__

#include <functional>

template<class T>
struct BiTNode
{
	T data;
#if HAS_BF
	int bf;
#endif
	BiTNode<T> *lchild,*rchild;
};

template<class T>
void initBiTree(BiTNode<T> * &Tr)
{
	Tr=NULL;
}

template<class T>
void destroyBiTree(BiTNode<T> * Tr)
{
	if(Tr)
	{
		if(Tr->lchild) destroyBiTree(Tr->lchild);
		if(Tr->rchild) destroyBiTree(Tr->rchild);
		free(Tr);
		Tr=NULL;
	}
}

template<class T>
void inorderTraverse(BiTNode<T> *Tr,const std::function<void(const T &)> &visit)
{
	if(Tr)
	{
		inorderTraverse(Tr->lchild,visit);
		visit(Tr->data);
		inorderTraverse(Tr->rchild,visit);
	}
}

template<class T>
BiTNode<T> * searchBST1(BiTNode<T> * Tr,keyType key_)
{
	if(!Tr||EQ(key_,Tr->data.key)) return Tr;
	else if LT(key_,Tr->data.key) return searchBST1(Tr->lchild,key_);
	else searchBST1(Tr->rchild,key_);
}
#endif