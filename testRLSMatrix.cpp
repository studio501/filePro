
#include "stdafx.h"
#include "testRLSMatrix.h"

//œ° Ëæÿ’Û≤‚ ‘
void testRLSMatrix()
{
	RLSMatrix<int> A,B,C,D,E,F;
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
}