#include <stdio.h>
#include <stdlib.h>
#include "myrsa.h"

void test()
{
	private_key pkey;

#if 0
	printf("create key...\n");
	pkey=MakePrime(MODE_1024);//产生1024位密钥
	while(rsa1024_checkprivatekey(pkey)==false)//产生的密匙不符合要求
	{
		pkey=MakePrime(MODE_1024);//重新产生1024位密钥
	}
	printf("create key finish\n");
	rsa1024_privatekey_outtofile("pkey.txt",pkey);
	print_privatekey(pkey);
#endif

#if 1
	printf("load key\n");
	int result_load=rsa1024_privatekey_loadfromfile("pkey.txt",pkey);
	printf("load key finish,restlt_load=%d\n",result_load);
#endif

	vlong m;
	vlong c;
	vlong mm;
	unsigned long a[32];
	for(int k=0;k<31;k++)   a[k]=k+32*5;
	a[31]=0xf0000000;
	m.load(a,32);
	printf("start code\n");
	c=Encrypt(pkey,m);
	printf("code finish\n");
	printf("start decode\n");
	mm=Decrypt(pkey,c);
	printf("decode finish\n");
	print_privatekey(pkey);
	print_vlong(m);
	print_vlong(c);
	print_vlong(mm);
	if(m==mm)     printf("m==mm\n");
	    else      printf("m!=mm\n");
}

int main()
{
	private_key pkey;
	//pkey=MakePrime(MODE_1024);
	//vlong m;
	//vlong c;
	//vlong mm;
	//unsigned long a[32]={0x61626364,0x65666779};
	//for(int k=2;k<32;k++)   a[k]=0x79797979;
	//m.load(a,32);
	//c=Encrypt(pkey,m);
	//mm=Decrypt(pkey,c);
	//print_privatekey(pkey);
	//print_vlong(m);
	//print_vlong(c);
	//print_vlong(mm);
	//int b=rsa1024_checkprivatekey(pkey);
	//printf("rsa1024_checkprivatekey=%d\n",b);

#if 0
	pkey=MakePrime(MODE_1024);//产生1024位密钥
	while(rsa1024_checkprivatekey(pkey)==false)//产生的密匙不符合要求
	{
		pkey=MakePrime(MODE_1024);//重新产生1024位密钥
	}
	rsa1024_privatekey_outtofile("pkey.txt",pkey);
	print_privatekey(pkey);
#endif

	int result_load=rsa1024_privatekey_loadfromfile("pkey.txt",pkey);
	printf("result_load=%d\n",result_load);
	int result_code=rsa1024_file_code("1.txt", "2.txt", pkey, MODE_NOCREATEPRIVATEKEY_NOCHECKPRIVATEKEY);
	//int result_code=rsa1024_file_code("1.txt", "2.txt", pkey, MODE_CREATEPRIVATEKEY);
	printf("result_code=%d\n",result_code);
	int result_decode=rsa1024_file_decode("2.txt", "3.txt", pkey);
	printf("result_decode=%d\n",result_decode);
	//print_privatekey(pkey);
	//rsa1024_privatekey_outtofile("pkey.txt",pkey);

	//test();

	system("pause");
	return 0;
}
