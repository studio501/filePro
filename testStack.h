#ifndef TEST_STACK_HH__
#define TEST_STACK_HH__

#define STACK_INIT_SIZE  80
#define STACK_INC_SIZE  20
typedef int SElemType ;  //for common test

//struct PosType
//{
//	int x;//行值
//	int y;//列值
//};
//struct SElemType
//{
//	int ord;//通道块在路径上的序列号
//	int di;//向下一个通道块走的方向 0~3:东南西北
//	PosType seat;//通道块在迷宫中的位置
//};


struct SqStack
{
	SElemType *top,*base;
	int stackSize;
};


//
typedef void (*visitstack_func)(SElemType);

//打印一个元素
void print_stack(SElemType e);

//输入到一个元素到文件
void writetofile_stack(SElemType e);

//输入一个换行符到文件
void writeBreakLine(const char *fileName="editLine.txt");

//创建一个空栈
void initStack(SqStack &S);

//销毁栈
void destroyStack(SqStack &S);

//清空栈
void clearStack(SqStack &S);

//是否是空栈
bool isStackEmpty(SqStack &S);

//当前栈的长度
int stackLength(SqStack &S);

//获取栈顶元素
bool getTop(SqStack &S,SElemType &e);

//压栈
void pushStack(SqStack &S,SElemType e);

//出栈
bool popStack(SqStack &S,SElemType &e);

//遍历栈
void stackTraverse(SqStack S,visitstack_func vFunc);

//===============================栈的相关应用
//转换进制 N<10
void conversion_unit(int n=123,int N=8);

//十进制转换为十六进制
void conversion_16(int n);

//检验括号匹配
void check_bracket(const char *fileName="bracket.txt",int line=1);

//行编辑程序
void lineEdit(const char *fileName="inputline.txt");

//#define MAXLENGTH 25
//typedef int MazeType[MAXLENGTH][MAXLENGTH];
//MazeType g_m;
//int g_x,g_y;
//PosType g_begin,g_end;//迷宫的入口坐标 出口坐标
//
////输出迷宫的解
//void print_m();



#endif // !TEST_STACK_HH__
