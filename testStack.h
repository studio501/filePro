#ifndef TEST_STACK_HH__
#define TEST_STACK_HH__

#define STACK_INIT_SIZE  80
#define STACK_INC_SIZE  20
typedef int SElemType ;  //for common test

//struct PosType
//{
//	int x;//��ֵ
//	int y;//��ֵ
//};
//struct SElemType
//{
//	int ord;//ͨ������·���ϵ����к�
//	int di;//����һ��ͨ�����ߵķ��� 0~3:��������
//	PosType seat;//ͨ�������Թ��е�λ��
//};


struct SqStack
{
	SElemType *top,*base;
	int stackSize;
};


//
typedef void (*visitstack_func)(SElemType);

//��ӡһ��Ԫ��
void print_stack(SElemType e);

//���뵽һ��Ԫ�ص��ļ�
void writetofile_stack(SElemType e);

//����һ�����з����ļ�
void writeBreakLine(const char *fileName="editLine.txt");

//����һ����ջ
void initStack(SqStack &S);

//����ջ
void destroyStack(SqStack &S);

//���ջ
void clearStack(SqStack &S);

//�Ƿ��ǿ�ջ
bool isStackEmpty(SqStack &S);

//��ǰջ�ĳ���
int stackLength(SqStack &S);

//��ȡջ��Ԫ��
bool getTop(SqStack &S,SElemType &e);

//ѹջ
void pushStack(SqStack &S,SElemType e);

//��ջ
bool popStack(SqStack &S,SElemType &e);

//����ջ
void stackTraverse(SqStack S,visitstack_func vFunc);

//===============================ջ�����Ӧ��
//ת������ N<10
void conversion_unit(int n=123,int N=8);

//ʮ����ת��Ϊʮ������
void conversion_16(int n);

//��������ƥ��
void check_bracket(const char *fileName="bracket.txt",int line=1);

//�б༭����
void lineEdit(const char *fileName="inputline.txt");

//#define MAXLENGTH 25
//typedef int MazeType[MAXLENGTH][MAXLENGTH];
//MazeType g_m;
//int g_x,g_y;
//PosType g_begin,g_end;//�Թ���������� ��������
//
////����Թ��Ľ�
//void print_m();



#endif // !TEST_STACK_HH__
