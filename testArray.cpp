
#include "stdafx.h"
#include "testArray.h"

void arrayTestMain()
{
	Array<int> A;
	int i,j,k,*p,dim=3,b1=3,b2=4,b3=2;
	int e,*p1;
	initArray(A,dim,b1,b2,b3);
	p=A.bounds;
	cout<<"A.bounds=:\n";
	for(i=0;i<dim;++i) cout<<*(p+i)<<" ";
	p=A.constants;
	cout<<"\nA.constants=:\n";
	for(i=0;i<dim;++i) cout<<*(p+i)<<" ";
	printf("\n%dÒ³%dÐÐ%dÁÐ¾ØÕóÔªËØÈçÏÂ:\n",b1,b2,b3);
	for(i=0;i<b1;++i)
	{
		for(j=0;j<b2;++j)
		{
			for(k=0;k<b3;++k)
			{
				Assign(A,i*100+j*10+k,i,j,k);
				Value(e,A,i,j,k);
				printf("A[%d][%d][%d]=%2d ",i,j,k,e); // Êä³öA[i][j][k]
			}
			cout<<endl;
		}
		cout<<endl;
	}

	p1=A.base;
	cout<<"A.base=\n";
	for(i=0;i<b1*b2*b3;++i)
	{
		printf("%4d",*(p1+i));
		if(i%(b2*b3)==b2*b3-1) cout<<endl;
	}
	int a1=sizeof(int);
	int a2=sizeof(float);
	cout<<"Max num is : "<<Max<int>(3,1,5,6)<<endl;
	cout<<"Max num is : "<<Max<double>(3,1.9,5.9,6.7)<<endl;
}


//Ï¡Êè¾ØÕó²âÊÔ
void testSMatrix()
{
	TSMatrix<int> A,B,C,D,E,F;
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
	fastTransposeSMatrix(E,F);
	printSMatrix1(F);
}