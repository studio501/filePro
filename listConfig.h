
#ifndef __LIST_CONFIG__HHHH__
#define __LIST_CONFIG__HHHH__

#include "commonFunc.h"
typedef int ElemType;


#define mymax(a,b)    (((a) > (b)) ? (a) : (b))
#define mymin(a,b)    (((a) < (b)) ? (a) : (b))

typedef bool(*compare_func)(ElemType,ElemType);
typedef void(*vi_func)(ElemType&);
#endif