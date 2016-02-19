
#include "stdafx.h"
#include "queueTest.h"



template<class T>
void printQ(T i)
{
	cout<<i<<" ";
}

void queueTestMain()
{
	LinkQueue<int> q;
	initQueue(q);
	enQueue(q,-5);
	for(int i=0;i<14;++i)
		enQueue(q,i);
	queueTraverse(q);


	int a;
	getQueueHead(q,a);
	cout<<a<<endl;

	for(int i=0;i<5;++i) deQueue(q,a);
	queueTraverse(q);
	clearQueue(q);

	destroyQueue(q);

	int aa=100;
}