#pragma once

#ifndef __MYRSA_H
#define __MYRSA_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "prime.h"
#include "vlong.h"
#include "rsa.h"

#define MODE_256  0//256λ����ǿ��
#define MODE_512  1//512λ����ǿ��
#define MODE_1024 2//1024λ����ǿ��
#define MODE_2048 3//2048λ����ǿ��
#define MODE_4096 4//4096λ����ǿ��

#define MODE_CREATEPRIVATEKEY                     0//����ʱ�����ܳ�
#define MODE_NOCREATEPRIVATEKEY_CHECKPRIVATEKEY   1//����ʱ�������ܳף�ʹ�ø������ܳף������������ܳ׵ĺϷ���
#define MODE_NOCREATEPRIVATEKEY_NOCHECKPRIVATEKEY 2//����ʱ�������ܳף�ʹ�ø������ܳף�Ҳ�����������ܳ׵ĺϷ��ԣ�������������ǰ�Ѽ�����ܳ׺Ϸ��Ե����

private_key MakePrime(const unsigned long mode);//���ɴ�����p,q��n,e
vlong Encrypt(const private_key pkey, const vlong m);//����
vlong Decrypt(const private_key pkey, const vlong c);//����
void print_privatekey(const private_key pkey);//��ʾ˽Կ
void print_vlong(const vlong vl);//��ʾvlong����
bool rsa1024_checkprivatekey(const private_key pkey);//����ܳ��Ƿ����Ҫ��(���̽�����ʱ��ϳ�)
long rsa1024_MyGetFileSize(const char* filename);//��ȡ�ļ���С�����ô˺���ʱ���ļ����봦��δ�򿪶�д״̬
int rsa1024_file_code(const char* readfilename, const char* writefilename, private_key &pkey, const unsigned long mode);//RSA�㷨1024λ����ǿ�ȼ��ܣ��ļ�ͷ��д��3��byte��־λ
int rsa1024_file_decode(const char* readfilename, const char* writefilename, const private_key pkey);//RSA�㷨1024λ����ǿ�Ƚ��ܣ�У���ļ�ͷ��д���3��byte��־λ
int rsa1024_privatekey_outtofile(const char* writefilename, const private_key pkey);//�����ܳ׵��ļ�
int rsa1024_privatekey_loadfromfile(const char* readfilename, private_key &pkey);//���ļ��е����ܳ�

#endif