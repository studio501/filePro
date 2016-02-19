
#include "stdafx.h"
#include "lQueueTest.h"


void lQueueTestMain()
{
	SqQueue<float> Q;
	initQueue(Q);
	for(int i=0;i<18;++i)
		enQueue(Q,3.14f*i);
	queueTraverse(Q);

	float a;
	for(int i=0;i<4;++i)
		deQueue(Q,a);
	queueTraverse(Q);

	cout<<queueLength(Q)<<endl;
	getQueueHead(Q,a);
	cout<<a<<endl;

	clearQueue(Q);
	destroyQueue(Q);
	int aa=100;
}