#ifndef __QUEUETEST__HH__
#define __QUEUETEST__HH__

template<class T>
struct QNode
{
	T data;
	QNode *next;
};


#endif