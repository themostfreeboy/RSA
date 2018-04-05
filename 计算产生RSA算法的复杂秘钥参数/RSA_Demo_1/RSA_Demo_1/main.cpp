#include "RSA.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
	int p,q,n,e,d,m,c;
	printf("正在计算中...\n");
	//RSA_Key_Create(100,10000,100);
	printf("计算完成!\n");
	p=101;
	q=103;
	n=p*q;//n=10403
	e=79;
	d=RSA_d_Calculate(p,q,e);//d=4519
	printf("p=%d,q=%d,n=%d,e=%d,d=%d,RSA_All_Check=%d\n",p,q,n,e,d,RSA_All_Check(p,q,n,e,d));
	while(1)
	{
		printf("input:m=");
		scanf("%d",&m);
		c=RSA_Code(e,n,m);
		printf("out:c=%d\n",c);
		m=0;
		m=RSA_Decode(d,n,c);
		printf("out:m=%d\n",m);
		system("pause");
		system("cls");
		printf("p=%d,q=%d,n=%d,e=%d,d=%d,RSA_All_Check=%d\n",p,q,n,e,d,RSA_All_Check(p,q,n,e,d));
	}
	system("pause");
	return 0;
}
