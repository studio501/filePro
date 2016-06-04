
#include "stdafx.h"

#include "temp.h"
#include <iostream>
using namespace std;


template<class T>
 void testfunc(const T&a)
{
	cout<<a<<endl;
}

 template<class T>
 theclass<T>::theclass<T>()
	 :a(T(0))
 {

 }

 template <class T>
 void theclass<T>::set(T var)
 {
	 a = var;
 }

 template <class T>
 void theclass<T>::show()
 {
	cout<<a<<endl;
 }


 
 
