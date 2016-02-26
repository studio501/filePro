
#include "stdafx.h"
#include "testCLMatrix.h"

//œ° Ëæÿ’Û≤‚ ‘
void testCLSMatrix()
{
	CrossList<int> A,B,C,D,E,F;
	initSMatrix(A);
	initSMatrix(B);
	initSMatrix(C);
	initSMatrix(D);
	initSMatrix(E);
	initSMatrix(F);
	createSMatrix(A);
	printSMatrix1(A);
	createSMatrix(B,2);
	printSMatrix1(B);
	addSMatrix(A,B,C);
	printSMatrix1(C);
	destroySMatrix(C);
	multSMatrix(A,B,C);
	printSMatrix1(C);
	transposeSMatrix(C,D);
	printSMatrix1(D);
	createSMatrix(E,3);
	printSMatrix1(E);
	subtSMatrix(A,B,F);
	printSMatrix1(F);
}