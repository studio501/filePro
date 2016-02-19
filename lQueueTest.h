#ifndef __LQUEUETEST__HH__
#define __LQUEUETEST__HH__

#include <malloc.h>
#include <process.h>

#include <iostream>
using namespace std;


#define MAX_LQSIZE 15
#define QUEUE_INCREMENT 5

template<class T>
struct SqQueue
{
	T *base;
	int front,rear,queueSize;
};

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
void initQueue(SqQueue<T> &Q)
{
	Q.base=(T *)malloc(sizeof(T)*MAX_LQSIZE);
	if(!Q.base) exit(OVERFLOW);
	Q.front=Q.rear=0;
	Q.queueSize=MAX_LQSIZE;
}

//销毁队列Q
template<class T>
void destroyQueue(SqQueue<T> &Q)
{
	if(Q.base) free(Q.base);
	Q.base=NULL;
	Q.front=Q.rear=0;
	Q.queueSize=0;
}

//清空队列
template<class T>
void clearQueue(SqQueue<T> &Q)
{
	Q.front=Q.rear=0;
	Q.queueSize=0;
}

//判断队列是否为空
template<class T>
bool isQueueEmpty(SqQueue<T> Q)
{
	if(Q.front==Q.rear) return true;
	else return false;
}

//求队列长度
template<class T>
int queueLength(SqQueue<T> Q)
{
	return (Q.rear-Q.front+Q.queueSize)%Q.queueSize;
}

//返回队列的头元素
template<class T>
bool getQueueHead(SqQueue<T> Q,T &e)
{
	if(Q.front==Q.rear) return false;
	e=Q.base[Q.front];
	return true;
}

//插入元素e为Q的新队尾元素
template<class T>
bool enQueue(SqQueue<T> &Q,T e)
{
	if((Q.rear+1)%Q.queueSize==Q.front)
	{
		Q.base=(T*)realloc(Q.base,(Q.queueSize+QUEUE_INCREMENT)*sizeof(T));
		if(!Q.base) exit(0);
		if(Q.front>Q.rear)
		{
			for(int i=Q.queueSize-1;i>=Q.front;--i) Q.base[i+QUEUE_INCREMENT]=Q.base[i];
			Q.front+=QUEUE_INCREMENT;
		}
		Q.queueSize+=QUEUE_INCREMENT;
	}
	Q.base[Q.rear]=e;
	Q.rear=++Q.rear%Q.queueSize;
}

//出队列
template<class T>
bool deQueue(SqQueue<T> &Q,T &e)
{
	if(Q.front==Q.rear) return false;
	e=Q.base[Q.front];
	Q.front=(Q.front+1)%Q.queueSize;
	return true;
}

//遍历队列
template<class T>
void queueTraverse(SqQueue<T> Q)
{
	int i=Q.front;
	while(i!=Q.rear)
	{
		cout<<Q.base[i]<<" ";
		i=(i+1)%Q.queueSize;
	}
	printf("\n");
}

#endif