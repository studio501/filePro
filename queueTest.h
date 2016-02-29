#ifndef __QUEUETEST__HH__
#define __QUEUETEST__HH__

#include <malloc.h>
#include <process.h>
#include <iostream>

using namespace std;


template<class T>
struct QNode
{
	T data;
	QNode *next;
};


template<class T>
struct LinkQueue
{
	QNode<T> * front,*rear;
};

//构造一个空队列
template<class T>
void initQueue(LinkQueue<T> &Q)
{
	if(!(Q.front=Q.rear=(QNode<T>*)malloc(sizeof(QNode<T>)))) exit(0);
	Q.front->next=NULL;
}

//销毁队列Q
template<class T>
void destroyQueue(LinkQueue<T> &Q)
{
	while(Q.front)
	{
		Q.rear=Q.front->next;
		free(Q.front);
		Q.front=Q.rear;
	}
}

//清空队列
template<class T>
void clearQueue(LinkQueue<T> &Q)
{
	QNode<T> *p,*q;
	Q.rear=Q.front;
	p=Q.front->next;
	Q.front->next=NULL;
	while(p)
	{
		q=p;
		p=p->next;
		free(q);
	}
}

//判断队列是否为空
template<class T>
bool isQueueEmpty(LinkQueue<T> Q)
{
	if(Q.front->next==NULL) return true;
	else  return false;
}

//求队列长度
template<class T>
int queueLength(LinkQueue<T> Q)
{
	int i=0;
	QNode<T> *p=Q.front;
	while(p!=Q.rear) 
	{
		++i;
		p=p->next;
	}
	return i;
}

//返回队列的头元素
template<class T>
bool getQueueHead(LinkQueue<T> Q,T &e)
{
	if (Q.front==Q.rear) return false;
	QNode<T> *p=Q.front->next;
	e=p->data;
	return true;
}

//插入元素e为Q的新队尾元素
template<class T>
void enQueue(LinkQueue<T> &Q,T e)
{
	QNode<T> *p;
	if(!(p=(QNode<T>*)malloc(sizeof(QNode<T>)))) exit(OVERFLOW);
	p->data=e;
	p->next=NULL;
	Q.rear->next=p;
	Q.rear=p;
}

//出队列
template<class T>
bool deQueue(LinkQueue<T> &Q,T &e)
{
	QNode<T> *p;
	if(Q.front==Q.rear) return false;
	p=Q.front->next;
	e=p->data;
	Q.front->next=p->next;
	if(Q.rear==p) Q.rear=Q.front;
	free(p);
	return true;
}

//遍历队列
template<class T>
void queueTraverse(LinkQueue<T> Q)
{
	QNode<T> *p=Q.front->next;
	while(p)
	{
		cout<<p->data<<" ";
		p=p->next;
	}
	printf("\n");
}

#endif