
#include "stdafx.h"

#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

class ReplaceAlgorithm
{
public: 
	virtual void Replace()=0;
};

class LRU_ReplaceAlgorithm : public ReplaceAlgorithm
{
public:
	void Replace()
	{
		cout<<"Least Recently used replace algorithm"<<endl;
	}
};

class FIFO_ReplaceAlgorithm : public ReplaceAlgorithm
{
public:
	void Replace()
	{
		cout<<"first in first out replace algorithm"<<endl;
	}
};

class Random_ReplaceAlgorithm : public ReplaceAlgorithm
{
public:
	void Replace()
	{
		cout<<"Random replace algorithm"<<endl;
	}
};

template<class RA>
class cache
{
private: 
	RA m_ra;
public:
	cache(){}
	~cache(){}
	void replace(){m_ra.Replace();}

};

void testStratedy()
{
	auto c1 = new cache<Random_ReplaceAlgorithm>();
	c1->replace();

	auto c2 = new cache<LRU_ReplaceAlgorithm>();
	c2->replace();

	auto c3 = new cache<FIFO_ReplaceAlgorithm>();
	c3->replace();
}

//////////////////////////////////////////////////////////////////////////

class Deque
{
public:
	void push_back(int x) {cout<<"deque push_back"<<endl;}
	void push_front(int x) {cout<<"deque push_front"<<endl;}
	void pop_back(){cout<<"deque pop_back"<<endl;}
	void pop_front() {cout<<"deque pop_front"<<endl;}
};

class Sequence
{
public:
	virtual void push(int x)=0;
	virtual void pop() = 0;
};

class stack : public Sequence
{
public:
	void push(int x){deque_.push_back(x);}
	void pop(){deque_.pop_back();}

private:
	Deque deque_;
};

class queue : public Sequence
{
private:
	Deque deque_;
public:
	void push(int x){deque_.push_back(x);}
	void pop(){deque_.pop_front();}
};

void testAdapter()
{
	Sequence *s1 = new stack();
	Sequence *s2 = new queue();

	s1->push(1);s1->pop();
	s2->push(1);s2->pop();
	delete s1;
	delete s2;
}

//////////////////////////////////////////////////////////////////////////单例模式

#define singleton_mode 1

#if singleton_mode == 0

class singleton{
private:
	singleton(){cout<<"call singleton()";}
	static singleton *ins;
public:
	static singleton * getInstance()
	{
		if(!ins)
			ins = new singleton();
		return ins;
	}
};
singleton * singleton::ins=NULL;

#elif singleton_mode == 1

#include "singleton.h"
#include "singletonA.h"
#include "singletonB.h"
singleton * singleton::ins=NULL;

singleton * singleton::getInstance(const char *name)
{
	if(!ins)
	{
		if(strcmp(name,"singletonA")==0)
		{
			ins = new singletonA();
		}
		else if(strcmp(name,"singletonB")==0)
		{
			ins = new singletonB();
		}
		else
			ins = new singleton();
	}
	return ins;
}

#else
#endif


void testSingleton()
{
#if singleton_mode == 0 
	auto pIns = singleton::getInstance();
	auto pIns1 = singleton::getInstance();
	auto pIns2 = singleton::getInstance();
	auto pIns3 = singleton::getInstance();
	auto pIns4 = singleton::getInstance();

#else
	auto pIns1 = singleton::getInstance("singletonA");
	pIns1->show();

	auto pIns2 = singleton::getInstance("singletonB");
	pIns2->show();

	auto pIns = singleton::getInstance("");
	pIns->show();
#endif
}

//////////////////////////////////////////////////////////////////////////原型模式
class Resume
{
protected:
	char * name;
public:
	Resume(){}
	virtual ~Resume(){}
	virtual Resume * clone(){return NULL;}
	virtual void set(char *n){}
	virtual void show(){}
};

class ResumeA : public Resume
{
public:
	ResumeA(const char * str)
	{
		if(!str)
		{
			name = new char[1];
			name[0] ='\0';
		}
		else
		{
			name = new char(strlen(str)+1);
			strcpy(name,str);
		}
	}
	ResumeA(const ResumeA &r)
	{
		name = new char[strlen(r.name)+1];
		strcpy(name,r.name);
	}

	ResumeA * clone()
	{
		return new ResumeA(*this);
	}

	void show(){printf("ResumeA name: %s\n",name);}
};

void testPrototype()
{
	Resume *r1 = new ResumeA("asadfasf");
	Resume *r2 = new ResumeA("bnbmf");
	Resume *r3 = r1->clone();
	Resume *r4 = r2->clone();
	r1->show();r2->show();
	delete r1;delete r2;
	r1=r2=NULL;
	r3->show();r4->show();
	delete r3;delete r4;
	r3=r4=NULL;
}

//////////////////////////////////////////////////////////////////////////建造者模式

class Builder    
{  
public:  
	virtual void BuildHead() {}  
	virtual void BuildBody() {}  
	virtual void BuildLeftArm(){}  
	virtual void BuildRightArm() {}  
	virtual void BuildLeftLeg() {}  
	virtual void BuildRightLeg() {}  
}; 

class ThinBuilder : public Builder  
{  
public:  
	void BuildHead() { cout<<"build thin body"<<endl; }  
	void BuildBody() { cout<<"build thin head"<<endl; }  
	void BuildLeftArm() { cout<<"build thin leftarm"<<endl; }  
	void BuildRightArm() { cout<<"build thin rightarm"<<endl; }  
	void BuildLeftLeg() { cout<<"build thin leftleg"<<endl; }  
	void BuildRightLeg() { cout<<"build thin rightleg"<<endl; }  
}; 

class FatBuilder : public Builder  
{  
public:  
	void BuildHead() { cout<<"build fat body"<<endl; }  
	void BuildBody() { cout<<"build fat head"<<endl; }  
	void BuildLeftArm() { cout<<"build fat leftarm"<<endl; }  
	void BuildRightArm() { cout<<"build fat rightarm"<<endl; }  
	void BuildLeftLeg() { cout<<"build fat leftleg"<<endl; }  
	void BuildRightLeg() { cout<<"build fat rightleg"<<endl; }  
}; 

class Director    
{  
private:  
	Builder *m_pBuilder;  
public:  
	Director(Builder *builder) { m_pBuilder = builder; }  
	void Create(){  
		m_pBuilder->BuildHead();  
		m_pBuilder->BuildBody();  
		m_pBuilder->BuildLeftArm();  
		m_pBuilder->BuildRightArm();  
		m_pBuilder->BuildLeftLeg();  
		m_pBuilder->BuildRightLeg();  
	}  
};  



void testBuilder()
{
	ThinBuilder thin;
	Director dir1(&thin);
	dir1.Create();

	FatBuilder fat;
	Director dir2(&fat);
	dir2.Create();
}

//////////////////////////////////////////////////////////////////////////外观组合模式
#include <list>
#include <string>
class Company    
{  
public:  
	Company(string name) { m_name = name; }  
	virtual ~Company(){}  
	virtual void Add(Company *pCom){}  
	virtual void Show(int depth) {}  
protected:  
	string m_name;  
};  
//具体公司  
class ConcreteCompany : public Company    
{  
public:  
	ConcreteCompany(string name): Company(name) {}  
	virtual ~ConcreteCompany() {}  
	void Add(Company *pCom) { m_listCompany.push_back(pCom); } //位于树的中间，可以增加子树  
	void Show(int depth)  
	{  
		for(int i = 0;i < depth; i++)  
			cout<<"-";  
		cout<<m_name<<endl;  
		list<Company *>::iterator iter=m_listCompany.begin();  
		for(; iter != m_listCompany.end(); iter++) //显示下层结点  
			(*iter)->Show(depth + 2);  
	}  
private:  
	list<Company *> m_listCompany;  
};  
//具体的部门，财务部  
class FinanceDepartment : public Company   
{  
public:  
	FinanceDepartment(string name):Company(name){}  
	virtual ~FinanceDepartment() {}  
	virtual void Show(int depth) //只需显示，无限添加函数，因为已是叶结点  
	{  
		for(int i = 0; i < depth; i++)  
			cout<<"-";  
		cout<<m_name<<endl;  
	}  
};  
//具体的部门，人力资源部  
class HRDepartment :public Company    
{  
public:  
	HRDepartment(string name):Company(name){}  
	virtual ~HRDepartment() {}  
	virtual void Show(int depth) //只需显示，无限添加函数，因为已是叶结点  
	{  
		for(int i = 0; i < depth; i++)  
			cout<<"-";  
		cout<<m_name<<endl;  
	}  
};  



void testMakeup()
{
	Company *root = new ConcreteCompany("总公司");  
	Company *leaf1=new FinanceDepartment("财务部");  
	Company *leaf2=new HRDepartment("人力资源部");  
	root->Add(leaf1);  
	root->Add(leaf2);  

	//分公司A  
	Company *mid1 = new ConcreteCompany("分公司A");  
	Company *leaf3=new FinanceDepartment("财务部");  
	Company *leaf4=new HRDepartment("人力资源部");  
	mid1->Add(leaf3);  
	mid1->Add(leaf4);  
	root->Add(mid1);  
	//分公司B  
	Company *mid2=new ConcreteCompany("分公司B");  
	FinanceDepartment *leaf5=new FinanceDepartment("财务部");  
	HRDepartment *leaf6=new HRDepartment("人力资源部");  
	mid2->Add(leaf5);  
	mid2->Add(leaf6);  
	root->Add(mid2);  
	root->Show(0);  

	delete leaf1; delete leaf2;  
	delete leaf3; delete leaf4;  
	delete leaf5; delete leaf6;   
	delete mid1; delete mid2;  
	delete root;  
}

//////////////////////////////////////////////////////////////////////////代理

class Image
{
protected:
	string m_imageName;
public:
	Image(string name)
		:m_imageName(name)
	{

	}
	virtual ~Image(){}
	virtual void show(){}
};

class BigImage : public Image
{
public:
	BigImage(string name):Image(name){}
	~BigImage(){}
	void show(){cout<<"show big image "<<m_imageName<<endl;}
};

class BigImageProxy : public Image
{
private:
	BigImage *m_bigImage;
public:
	BigImageProxy(string name):Image(name),m_bigImage(NULL){}
	~BigImageProxy(){delete m_bigImage;}
	void show()
	{
		if(m_bigImage == NULL)
			m_bigImage = new BigImage(m_imageName);
		m_bigImage->show();
	}
};

template<class T>
class my_auto_ptr
{

public:
	explicit my_auto_ptr(T *p=NULL):pointee(p){}
	my_auto_ptr(my_auto_ptr<T> &rhs):pointee(rhs.release()){}
	~my_auto_ptr(){delete pointee;}
	my_auto_ptr<T>& operator=(my_auto_ptr<T>& rhs)
	{
		if(this != &rhs) reset(rhs.release());
		return *this;
	}
	T & operator*() const {return *pointee;}
	T * operator->() const {return pointee;}
	T * get() const {return pointee;}
	T * release()
	{
		T *old = pointee;
		pointee = NULL;
		return old;
	}

	void reset(T *p=NULL)
	{
		if(pointee !=p)
		{
			delete pointee;
			pointee = p;
		}
	}
private:
	T *pointee;
};


template<class T>
class smart_ptr
{
public:
	smart_ptr(T *p =0):pointee(p),count(new size_t(1)){}
	smart_ptr(const smart_ptr &rhs):pointee(rhs.pointee),count(rhs.count){++*count;}
	~smart_ptr(){decr_count();}
	smart_ptr & operator= (const smart_ptr &rhs)
	{
		++*count;
		decr_count();
		pointee = rhs.pointee;
		count = rhs.count;
		return *this;
	}
	T *operator->(){return pointee;}
	const T* operator->()const{return pointee;}
	T &operator*(){return *pointee;}
	const T &operator*()const{return *pointee;}
	size_t get_refcount(){return *count;}

private:
	T * pointee;
	size_t *count;
	void decr_count()
	{
		if(--*count==0)
		{
			delete pointee;
			delete count;
		}
	}
};

void testProxy()
{
	Image * image = new BigImageProxy("proxy.jpg");
	image->show();
	delete image;

	
	auto p1 = new my_auto_ptr<int>(new int(10) );
	auto p2 = new my_auto_ptr<int>(new int(20) );

	my_auto_ptr<int> * p3;
	p3=p1;
	p3=p2;

	auto pp1 = new smart_ptr<int>(new int(10) );
	auto pp2 = new smart_ptr<int>(new int(20) );

	smart_ptr<int> * pp3;
	pp3=pp1;
	pp3=pp2;

	
	
	int a = 100;
}


//////////////////////////////////////////////////////////////////////////状态模式
class War;  
class State   
{  
public:  
	virtual void Prophase() {}  
	virtual void Metaphase() {}  
	virtual void Anaphase() {}  
	virtual void End() {}  
	virtual void CurrentState(War *war) {}  
};  
//战争  
class War  
{  
private:  
	State *m_state;  //目前状态  
	int m_days;      //战争持续时间  
public:  
	War(State *state): m_state(state), m_days(0) {}  
	~War() { delete m_state; }  
	int GetDays() { return m_days; }  
	void SetDays(int days) { m_days = days; }  
	void SetState(State *state) { delete m_state; m_state = state; }  
	void GetState() { m_state->CurrentState(this); }  
}; 

//战争结束  
class EndState: public State  
{  
public:  
	void End(War *war) //结束阶段的具体行为  
	{  
		cout<<"战争结束"<<endl;  
	}  
	void CurrentState(War *war) { End(war); }  
};  
//后期  
class AnaphaseState: public State  
{  
public:  
	void Anaphase(War *war) //后期的具体行为  
	{  
		if(war->GetDays() < 30)  
			cout<<"第"<<war->GetDays()<<"天：战争后期，双方拼死一搏"<<endl;  
		else  
		{  
			war->SetState(new EndState());  
			war->GetState();  
		}  
	}  
	void CurrentState(War *war) { Anaphase(war); }  
};  
//中期  
class MetaphaseState: public State  
{  
public:  
	void Metaphase(War *war) //中期的具体行为  
	{  
		if(war->GetDays() < 20)  
			cout<<"第"<<war->GetDays()<<"天：战争中期，进入相持阶段，双发各有损耗"<<endl;  
		else  
		{  
			war->SetState(new AnaphaseState());  
			war->GetState();  
		}  
	}  
	void CurrentState(War *war) { Metaphase(war); }  
};  
//前期  
class ProphaseState: public State  
{  
public:  
	void Prophase(War *war)  //前期的具体行为  
	{  
		if(war->GetDays() < 10)  
			cout<<"第"<<war->GetDays()<<"天：战争初期，双方你来我往，互相试探对方"<<endl;  
		else  
		{  
			war->SetState(new MetaphaseState());  
			war->GetState();  
		}  
	}  
	void CurrentState(War *war) { Prophase(war); }  
};


void testState()
{
	War *war = new War(new ProphaseState());  
	for(int i = 1; i < 40;i += 5)  
	{  
		war->SetDays(i);  
		war->GetState();  
	}  
	delete war;
}


//////////////////////////////////////////////////////////////////////////

void showValue(const int &t)
{
	cout<<t<<endl;
}

class A
{
	mutable int num;
public:
	A(){num=5;}
	void disp()
	{
		cout<<num<<" of normal disp"<<endl;
	}
	void disp() const
	{
		++num;
		cout<<num<<" of const disp"<<endl;
	}
	void set(int n)
	{
		num = n;
	}
};


int returnFunc(int a,int b)
{
	return a+b;
}

void testConst()
{
	//const int j=5;
	//int *ptr;
	//void *p = (void *)&j;
	//ptr = (int *)p;
	//(*ptr)++;
	//showValue(j);
	//cout<<j<<endl;

	////int &r = 5;
	//const int &rr = 0;

	/*int const **p1;
	int *const *p2;
	int i=6,j=10;
	const int *ptr1 = &i;
	int *const ptr2 = &j;
	p1=&ptr1;
	p2=&ptr2;
	cout<<**p1<<"  "<<**p2<<endl;*/

	A a1;
	a1.set(3);
	((const A &)(a1)).disp();
	a1.disp();


	
}


//////////////////////////////////////////////////////////////////////////
void testGoto()
{
	for(int i=0;i<10;++i)
		for(int k=0;k<10;++k)
			for(int j=0;j<10;++j)
				if(i+k+j == 20)
					goto show;
show:
				{
					cout<<"kjsfndakj"<<endl;
					int i=100;
					cout<<i<<endl;
					if(i<200) cout<<"less"<<endl;
					goto shownot;
				}
shownot:
				cout<<"should not be show"<<endl;
	
}

//////////////////////////////////////////////////////////////////////////
void testVolitate()
{
	volatile int i=10;
	int a=i;
	cout<<a<<endl;
	__asm{
		mov dword ptr [ebp-4],80
	}
	int b=i;
	cout<<b<<endl;
}

//////////////////////////////////////////////////////////////////////////

#define printVar(v,index) cout<<#v#index" is "<<v##index<<endl

void testMacro()
{
	int i1=1,i2=2,i3=100,a100=200;
	printVar(i,1);
	printVar(i,2);
	printVar(i,3);
	printVar(a,100);
}
//////////////////////////////////////////////////////////////////////////
void testWChar()
{
	char *p;
	wchar_t s[] = L"ABC";
	char name[] = "张三";
	wchar_t wname[] =L"张三";
	cout<<sizeof(wchar_t)<<endl;
	cout<<sizeof(s)<<endl;
	p=(char *)s;
	for(int i=0;i<sizeof(s);++i)
		cout<<(int)p[i]<<" ";
	cout<<endl;
	cout<<s<<" "<<endl;
	wcout<<s<<endl;

	std::wcout.imbue(std::locale("chs"));
	wcout<<wname<<endl;
	//cout<<"哈哈"<<endl;
}

//////////////////////////////////////////////////////////////////////////

void printAll(int n1,...)
{
	int *ptr = &n1;
	while(*ptr)
	{
		cout<<*ptr<<endl;
		ptr++;
	}
}

void testVAFunc()
{
	printAll(1,2,0);
}

//////////////////////////////////////////////////////////////////////////
class st
{
	double as;
	int ag;
public:
	st(double s,int a)
		:as(s),ag(a)
	{}
	operator double()
	{
		return as+ag;
	}
};

void testConvert()
{
	st s1(80.1,18);
	st s2(70.1,29);

	bool a = s1<s2;
	cout<<a<<endl;
}
//////////////////////////////////////////////////////////////////////////

int getaint()
{
	/*int temp;
	cin>>temp;
	return temp;*/
	return 0;
}

class A1{
public:
	static const int i;
	static const int j;
};

const int A1::i = 5;
const int A1::j = getaint();

void testStaticConst()
{
	cout<<A1::i<<endl;
	cout<<A1::j<<endl;
}

//////////////////////////////////////////////////////////////////////////

void testmultiArr()
{
	typedef int out[3];

	out * p = new out[2];

	int a[2][3] = {1,2,3,4,5,6};
	for(int i=0;i<2;++i)
		for(int j=0;j<3;++j)
			p[i][j] = a[i][j];

	for(int i=0;i<2;++i)
		for(int j=0;j<3;++j)
			cout<<p[i][j]<<" ";
	delete []p;
}

//////////////////////////////////////////////////////////////////////////
class stu
{
public:
	int age;
	int score;
};

double average(stu * objs,int stu::*pm,int count)
{
	int result = 0;
	for(int i=0;i<count;++i)
		result += objs[i].*pm;
	return (double)(result)/count;
}

void testMemberDataPointer()
{
	stu my[5] = {{17,75},{19,85},{20,80},{21,78},{22,83}};
	double age_ave = average(my,&stu::age,5);
	double sco_ave = average(my,&stu::score,5);
	cout<<"age_ave: "<<age_ave<<" sco_ave "<<sco_ave<<endl;

	stu s1 = {1,1};
	cout<<s1.*&stu::age<<endl;
	stu *ps1 = &s1;
	cout<<ps1->*&stu::age<<endl;
}


//////////////////////////////////////////////////////////////////////////
class handle::wrapped
{
public:
	int i;
};

void handle::create()
{
	working = new wrapped;
	working->i=5;
}

int handle::read()
{
	return working->i;
}

void handle::change(int i=0)
{
	working->i=i;
}

void handle::destroy()
{
	delete working;
	working=NULL;
}

handle::handle()
{
	create();
}

handle::~handle()
{
	destroy();
}

void testHandle()
{
	handle u;
	cout<<u.read()<<endl;
	u.destroy();
	u.create();
	u.change(9);
	u.change();
	cout<<u.read()<<endl;
}

//////////////////////////////////////////////////////////////////////////
template<class T,int size>
class Average
{
	T elements[size];
	T av;
public:
	Average(T *in)
	{
		av = T(0);
		for(int i=0;i<size;++i)
		{
			elements[i]=in[i];
			av+=in[i];
		}
		av/=size;
	}
	void show()
	{
		cout<<"the elements are : ";
		for(int i=0;i<size;++i) cout<<elements[i]<<" ";
		cout<<endl<<"the average is : "<<av<<endl;
	}
};

template<class T,T*total,int *number>
class single
{
	T sv;
public:
	single(T s)
	{
		sv = s;
		(*total)+=s;
		(*number)++;
	}
	T get()
	{
		return sv;
	}
};

int Int_total;
int Int_number;
double Dbl_total;
double dbl_number;


template<class T,int len>
class Array
{
	int size;
	T elements[len];
public:
	int getSize(){return len;}
	Array()
		:size(len)
	{

	}
	T &operator[](int i)
	{
		return elements[i];
	}
	template<class T,int len> 
	friend ostream& operator<<(ostream &,const Array<T,len>&);

	void show()
	{
		for(int i=0;i<size;++i)
			cout<<elements[i]<<" ";
		cout<<endl;
	}
};
	

template<class T,int len> 
ostream& operator<<(ostream &out,const Array<T,len>& a)
{
	for(int i=0;i<len;++i)
	{
		out<<a.elements[i];
		if(typeid(a.elements[i])==typeid(int) || typeid(a.elements[i])==typeid(double)) out<<" ";
	}
	return out;
}

template<class T,int a>
class student
{
	int age;
public:
	student():age(a){}
	double score;
	void show()
	{
		cout<<"the student's age is : "<<age<<" and its scroe is "<<score<<endl;
	}
};

template<class T,int a,template<class ,int > class A>
class container
{
public:
	A<T,a> entity;
	void show(){entity.show();}
};


template<class T>
void func(T t)
{
	cout<<t<<endl;
}

template<class T>
class A2
{
	T num;
public:
	A2():num(T(6.8)){}
	void invoke(void(*p)(T))
	{
		p(num);
	}

	/*template<class T>
	friend void showA2(const A2<T>& a){cout<<a.num<<endl;};*/

	template<class T1>
	friend void showA2(const A2<T1>&);
};

template<class T>
void showA2(const A2<T> &a )
{
	cout<<a.num<<endl;
}

//template<class T>
//void showA2(const A2<int> &a )
//{
//	cout<<a.num<<endl;
//}
//
//void showA2(const A2<double> &a )
//{
//	cout<<a.num<<endl;
//}

template<class T>
T Max(const T t1,const T t2)
{
	return (t1>t2)?t1:t2;
}

typedef const char * PCC;
template<>PCC Max<PCC>(PCC s1,PCC s2)
{
	return (strcmp(s1,s2)>0)?s1:s2;
}

#include "temp.h"

template<class T>
class Less
{
public:
	bool operator()(const T &t1,const T&t2)
	{
		return (t1<t2);
	}
};

template<class T>
class Bigger
{
public:
	bool operator()(const T&t1,const T&t2)
	{
		return (t1>t2);
	}
};

template<class T,class T1>
void printValue(const T&t1,const T&t2,T1 cmp)
{
	if(cmp(t1,t2))
		cout<<t1<<endl;
	else
		cout<<t2<<endl;
}

#include "String.h"

void testTemplate1()
{
	String s1;
	String s2("abc");
	String s3=s2;
	s3[0]='p';
	cout<<s2.c_str()<<endl;
	cout<<s3.c_str()<<endl;
	s1=s3;
	s2=s3;
	cout<<s1.c_str()<<endl;
	cout<<s2.c_str()<<endl;
	cout<<s3.c_str()<<endl;

	/*printValue(1,7,Bigger<int>());
	printValue(1.1,1.7,Less<double>());


	cout<<Max(10,5)<<endl;;
	cout<<Max("very","good")<<endl;*/

	//theclass<int> tobj;
	////tobj.set((int)0);
	//tobj.set(100);
	//tobj.show();
	

	//testfunc(3);
	//A2<double> a;
	//showA2(a);

	//A2<int> a1;
	//showA2(a1);

	//int i=5;
	////cout<<Max(i,'a')<<endl;
	//cout<<Max<int>(i,'a')<<endl;

	/*int arr_in[3] = {1,2,3};
	double arr_db[6] = {1.0,6.8,8.9,5.5,2.2,8.5};
	Average<int,2> ia(arr_in);
	Average<double,6> da(arr_db);
	ia.show();
	da.show();

	single<int,&Int_total,&Int_number> arr1[3]={3,6,9};
	cout<<Int_number<<" "<<Int_total<<endl;
	for(int i=0;i<3;++i)
		cout<<arr1[i].get()<<endl;

	Array<double,3> ald;
	ald[0]=1.1;
	ald[1]=2.2;
	ald[2]=3.3;
	cout<<ald<<endl;

	Array<Array<double,3>,4> a2d;
	for(int i=0;i<a2d.getSize();++i)
		for(int j=0;j<a2d[i].getSize();++j)
			a2d[i][j] = i+j;
	cout<<a2d<<endl;
	
	//cout<<typeid(int)<<endl;

	container<double,3,Array> obj1;
	obj1.entity[0]=1.1;
	obj1.entity[1]=2.2;
	obj1.entity[2]=3.3;
	obj1.show();

	container<double,18,student> obj2;
	obj2.entity.score=100;
	obj2.show();

	A2<int> a21;
	a21.invoke(func);

	A2<double> a22;
	a22.invoke(func*/
}

//////////////////////////////////////////////////////////////////////////
#include <iomanip>
void codeFunc(int i)
{
	if(i>5) cout<<"more"<<endl;
	else cout<<"less"<<endl;
}

void showCode(unsigned char * pi)
{
	unsigned char * keep = pi;
	int tmp = *pi;
	unsigned long exp;
	if(tmp==233)
	{
		unsigned long addr = 0L;
		exp=1;
		for(int i=0;i<4;++i)
		{
			pi++;
			tmp=int(*pi);
			addr +=tmp*exp;
			exp*=256;
		}
		addr +=int(keep)+5;
		showCode((unsigned char *)addr);
	}
	else
	{
		for(int i=0;i<4;++i)
		{
			cout<<setfill('0');
			cout<<"0X"<<setw(8)<<hex<<int(pi)<<":";
			for(int j=0;j<10;++j)
			{
				tmp=*(pi++);
				cout<<setw(2)<<hex<<tmp<<" ";
			}
			cout<<endl;
		}
	}
}

void testPrintCode()
{
	void (*pf1)(int);
	pf1 = codeFunc;
	unsigned char * pi = (unsigned char *)pf1;
	showCode(pi);
}


//////////////////////////////////////////////////////////////////////////

int *testStackCapacityAddr;
int testStackCapacityCount;

void testStackCapacityFunc(int i)
{
	cout<<testStackCapacityCount<<" : "<<(int)testStackCapacityAddr - int(&i)<<endl;
	testStackCapacityCount++;
	testStackCapacityAddr = &i;
	testStackCapacityFunc(i);
}

void testStackCapacity()
{
	int i;
	testStackCapacityAddr = &i;
	testStackCapacityFunc(2);
}


//////////////////////////////////////////////////////////////////////////

class theMemoryPool;

class ActualClass
{
	static int count;
	int num[10];
public:
	ActualClass()
	{
		count++;
		for(int i=0;i<10;++i)
			num[i]=count+i;
	}

	void show()
	{
		cout<<this<<" : ";
		for(int i=0;i<10;++i)
			cout<<num[i]<<" ";
		cout<<endl;
	}

	void * operator new(size_t size);
	

	void operator delete(void *p);
};

class theMemoryPool
{
	static MemPool<sizeof(ActualClass),2> mp;
	friend class ActualClass;
};

void * ActualClass::operator new(size_t size)
{
	return theMemoryPool::mp.malloc();
}

void ActualClass::operator delete(void *p)
{
	theMemoryPool::mp.free(p);
}

MemPool<sizeof(ActualClass),2> theMemoryPool::mp;
int ActualClass::count;

void testMemPool()
{
	ActualClass *p1 = new ActualClass;
	p1->show();
	ActualClass *p2 = new ActualClass;
	p2->show();
	delete p1;
	p1 = new ActualClass;
	p1->show();
	ActualClass *p3 = new ActualClass;
	p3->show();
	delete p1;
	delete p2;
	delete p3;
}

//////////////////////////////////////////////////////////////////////////

class PA
{
	int i;
	char c;
	void privateFunc()
	{
		cout<<"this is a private function of base class "<<endl;
	}
public:
	PA()
		:i(5)
		,c('a')
	{

	}
};

class PB : public PA
{
public:
	void printBaseI()
	{
		int *p = reinterpret_cast<int *>(this);
		cout<<*p<<endl;

		char *pc = reinterpret_cast<char *>(this);
		cout<<*(pc+sizeof(int))<<endl;
	}

	void usePrivateFunction()
	{
		void(*funcp)();
		__asm{
			mov eax,PA::privateFunc
			mov funcp,eax
		}
		funcp();
	}
};

void testPrivate()
{
	PB b;
	b.printBaseI();
	b.usePrivateFunction();
}


//////////////////////////////////////////////////////////////////////////
#define SFA(function) __asm{\
	mov eax,function}\
	__asm{mov p,eax}\
	cout<<"In SFA Address of "#function" is 0x"<<p<<endl;

void showvtableContent(char * className,void *pObj,int index)
{
	unsigned long *pAddr;
	pAddr = reinterpret_cast<unsigned long *>(pObj);
	pAddr = (unsigned long *)*pAddr;
	cout<<"the content of "<<className<<"'s vtable["<<index<<"]";
	cout<<"is 0x"<<(void *)pAddr[index]<<endl;
}

class Base
{
	int i;
public:
	virtual void f1()
	{
		cout<<"Base's f1()"<<endl;
	}
	virtual void f2()
	{
		cout<<"Base's f2()"<<endl;
	}
	virtual void f3()
	{
		cout<<"Base's f3()"<<endl;
	}
};

class Derived : public Base
{
public:

	virtual void f4()
	{
		cout<<"Derived's f4()"<<endl;
	}
	void f3()
	{
		cout<<"Derived's f3()"<<endl;
	}
	void f1()
	{
		cout<<"Derived's f1()"<<endl;
	}
};

void testvtbl()
{
	Base b1;
	Derived d1;
	void * p;
	unsigned long *pAddr;
	pAddr = reinterpret_cast<unsigned long *>(&b1);
	cout<<"addres of vtable of base is 0x"<<(void *)*pAddr<<endl;
	pAddr = reinterpret_cast<unsigned long *>(&d1);
	cout<<"address of vtable of derived is 0x"<<(void *)*pAddr<<endl;
	SFA(Base::f1);
	showvtableContent("Base",&b1,0);
	SFA(Base::f2);
	showvtableContent("Base",&b1,1);
	SFA(Base::f3);
	showvtableContent("Base",&b1,2);

	cout<<"==========================="<<endl;
	SFA(Derived::f1);
	showvtableContent("Derived",&d1,0);
	SFA(Derived::f2);
	showvtableContent("Derived",&d1,1);
	SFA(Derived::f3);
	showvtableContent("Derived",&d1,2);
	SFA(Derived::f4);
	showvtableContent("Derived",&d1,3);
	
}

//////////////////////////////////////////////////////////////////////////

class A3
{
	int num[3];
public:
	A3()
	{
		num[0]=1;
		num[1]=2;
		num[2]=3;
	}
	int & operator[](int sub)
	{
		if(sub<0 || sub >2)
			throw sub;
		else
			return num[sub];
	}
};

void testArrIndex()
{
	A3 a;
	A3 *p = &a;
	try
	{
		for(int i=0;i<=4;++i)
			cout<<p[0][i]<<endl;
	}
	catch(int sub)
	{
		cout<<"subscript out of range : "<<sub<<endl;
	}

	int arr[3] = {1,2,3};
	cout<<1[arr]<<endl;
}

//////////////////////////////////////////////////////////////////////////

template<class T>
class data_container
{
	T * p;
public:
	data_container(T * inp)
	{
		p = inp;
	}
	~data_container()
	{
		delete p;
	}
// 	template<class T>
// 	friend T operator *(const data_container<T> &);
	T operator*()
	{
		return *p;
	}
};

template<class T>
T operator*(const data_container<T> &d)
{
	return *(d.p);
}

void testDept()
{
	data_container<int> id(new int(5));
	data_container<double> dd(new double(7.8));
	cout<<*id<<" "<<*dd<<endl;
}

//////////////////////////////////////////////////////////////////////////
ostream & Tab(ostream &outs)
{
	for(int i=0;i<4;++i)
		outs<<"-";
	return outs;
}

ostream & Money(ostream &outs)
{
	outs<<left<<'$'<<setw(12)<<setfill('#');
	return outs;
}

ostream & Fuck(ostream &outs)
{
	outs<<"fuck you";
	return outs;
}


void testCustomSymbol()
{
	double amount = 1.23456;
	cout<<"the amount is"<<Tab<<Money<<amount<<endl;
	cout<<Fuck<<endl;
}

//////////////////////////////////////////////////////////////////////////
#include <conio.h>



void testNoEasySave()
{
	char c[6];
	cout<<"please input password: ";
	for(int i=0;i<5;++i)
	{
		c[i]=_getch();
		cout<<"*";
	}
	cout<<endl;
	c[5]='\0';
	if(string(c)=="hello")
		cout<<"your password are right";
	else
		cout<<"your password are wrong";
}
//////////////////////////////////////////////////////////////////////////

#include <locale>
void testLocale()
{
	locale native("");
	locale usa("American_USA.1252");
	locale Holland("Dutch");
	locale global;
	cout<<"native: "<<native.name()<<endl;
	cout<<"classic : "<<locale::classic().name()<<endl;
	cout<<"global: "<<global.name()<<endl;
	cout<<"Holland: "<<Holland.name()<<endl;
	cout<<"usa: "<<usa.name()<<endl;
}

//////////////////////////////////////////////////////////////////////////

#include <fstream>
void testCharCode()
{
	char str1[10] = "ABC我们";
	wchar_t str2[10] = L"ABC我们";
	ofstream file1("df1.txt",ios_base::out);
	file1<<str1;
	file1.close();
	wofstream file2("df2.txt",ios_base::out);
	file2.imbue(locale("CHS"));
	file2<<str2;
	file2.close();
	ofstream file3("df3.txt",ios_base::out);
	short flag = 0xFEFF;
	file3.write((char *)&flag,sizeof(short));
	file3.write((char *)str2,wcslen(str2)*2);
	file3.close();
}

//////////////////////////////////////////////////////////////////////////

#include <string>
#include <locale.h>
using namespace std;
static string ws2s(const wstring &ws)
{
	size_t convertedChars=0;
	string curLocale = setlocale(LC_ALL,NULL);
	setlocale(LC_ALL,"chs");
	const wchar_t * _Source = ws.c_str();
	size_t _Dsize = 2*ws.size()+1;
	char * _Dest = new char[_Dsize];
	wcstombs_s(&convertedChars,_Dest,_Dsize,_Source,_TRUNCATE);
	string result = _Dest;
	delete [] _Dest;
	setlocale(LC_ALL,curLocale.c_str());
	return result;
}

static wstring s2ws(const string &s)
{
	size_t convertedChars=0;
	setlocale(LC_ALL,"chs");
	const char * _Source = s.c_str();
	size_t _Dsize = s.size()+1;
	wchar_t * _Dest = new wchar_t[_Dsize];
	mbstowcs_s(&convertedChars,_Dest,_Dsize,_Source,_TRUNCATE);
	wstring result = _Dest;
	delete []_Dest;
	setlocale(LC_ALL,"C");
	return result;
}
void testS_2_Ws_convert()
{
	wchar_t *wstr = L"ABC我们";
	cout<<wstr<<endl;
	string obj(ws2s(wstr));
	cout<<obj<<endl;

	char * str = "ABC我们";
	wcout<<str<<endl;
	wstring wobj(s2ws(str));
	wcout<<wobj<<endl;
}

//////////////////////////////////////////////////////////////////////////

#include <ctime>
#include <sys/types.h>
#include <sys/stat.h>
#include <cerrno>
#include <cstring>
void testFileInfo()
{
	struct stat fileInfo;
	char message[30];
	if(stat("df1.txt",&fileInfo)!=0)
	{
		cout<<"error"<<endl;
	}
	cout<<fileInfo.st_size<<" "<<(char)(fileInfo.st_dev+'A')<<endl;
	ctime_s(message,29,&fileInfo.st_ctime);
	cout<<message<<endl;
	ctime_s(message,29,&fileInfo.st_mtime);
	cout<<message<<endl;
}

//////////////////////////////////////////////////////////////////////////

#include <direct.h>
#include <errno.h>
#include <cstdio>
void testFileOpts()
{
	char filepath[100];
	char *forcestr;
	_getcwd(filepath,99);
	cout<<filepath<<endl;

	forcestr = _getcwd(NULL,0);
	cout<<forcestr<<endl;

	if(forcestr) free(forcestr);

	if(_chdir(".."))
	{
		switch(errno)
		{
		case ENOENT:
			cout<<"unable to locate the directory"<<endl;
			break;
		case EINVAL:
			cout<<"invalid buffer"<<endl;
			break;
		default:
			cout<<"unknown error"<<endl;
			break;
		}
	}
	else
	{
		forcestr = _getcwd(NULL,0);
		cout<<forcestr<<endl;
		if(forcestr) free(forcestr);
	}
	_chdir("./filePro");

	rename("df2.txt","df22.txt");
	remove("df3.txt");
	_mkdir("test");
	_rmdir("test");
}

//////////////////////////////////////////////////////////////////////////

void testBinaryFile()
{
	ofstream fout("bfile1.dat",ios::binary);
	/*int num = 30;
	fout.write((char *)(&num),sizeof(num));*/
	

	struct OBj
	{
		int number;
		char letter;
	}obj;
	obj.number=109;
	obj.letter='M';
	
	fout.write((char*)(&obj),sizeof(obj));

	OBj obj1;
	obj1.number=200;
	obj1.letter='B';
	fout.write((char*)(&obj1),sizeof(obj1));
	fout.close();

	ifstream fin("bfile1.dat",ios::binary);
	OBj obj2;
	fin.read((char*)(&obj2),sizeof(obj2));
	fin.read((char*)(&obj2),sizeof(obj2));
	cout<<obj2.number<<" "<<obj2.letter<<endl;
	fin.close();

	fin.open("bfile1.dat",ios_base::in | ios_base::binary);
	fout.open("copyofbf1.dat",ios_base::out | ios_base::binary);
	if(!fin || !fout) cout<<"open file error"<<endl;
	char buf[1];
	do 
	{
		fin.read(&buf[0],1);
		fout.write(&buf[0],fin.gcount());
	} while (fin.gcount()>0);
	fin.close();
	fout.close();

	cout<<__FILE__<<__FUNCTION__<<__LINE__<<endl;
}

//////////////////////////////////////////////////////////////////////////
#include "dynamic.h"
void testDll()
{
	ReUse1 r1;
	r1.Effect();

	ReUse2 r2;
	r2.Output("hhh");
}
//////////////////////////////////////////////////////////////////////////
void testDesign()
{
	testDll();
	//testBinaryFile();
	//testFileOpts();
	//testFileInfo();
	//testS_2_Ws_convert();
	//testCharCode();
	//testLocale();
	//testNoEasySave();
	//testCustomSymbol();
	//testDept();
	//testArrIndex();
	//testvtbl();
	//testPrivate();
	//testMemPool();
	//testStackCapacity();
	//testPrintCode();
	//testStratedy();
	//testAdapter();
	//testSingleton();
	//testPrototype();
	//testBuilder();
	//testMakeup();
	//testProxy();
	//testState();
	//testConst();
	//testGoto();
	//testVolitate();
	//testMacro();
	//testWChar();
	//testVAFunc();
	//testConvert();
	//testStaticConst();
	//testmultiArr();
	//testMemberDataPointer();
	//testHandle();
	//testTemplate1();
}
