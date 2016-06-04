

#pragma once

template<class T>
void testfunc(const T&);

//template<class T>
//void testfunc(const T& a)
//{
//	cout<<a<<endl;
//}

template<class T>
class theclass
{
	T a;
public:
	theclass();

	void show();
	void set(T var);
};
