#include "RSA.h"
#include <stdlib.h>
//#include <stdio.h>
int main()
{
	int p,q,n,e,d;
	p=131;
	q=223;
	n=p*q;//n=29213
	e=133;
	d=RSA_d_Calculate(p,q,e);//d=217
	RSA_File_Code(".\\1234.txt",".\\5678.txt",e,n);
	RSA_File_Decode(".\\5678.txt",".\\9101112.txt",d,n);
	system("pause");
	return 0;
}
