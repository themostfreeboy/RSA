/*
RSA加密算法说明:

p:质数(保密)

q:质数(保密)

n=p*q(公开)

e:(公开)
满足:e与(p-1)*(q-1)互质

d:(保密)
满足:e*d = 1 (mod ((p-1)*(q-1)) )

m:明文(m>=0&&m<n)

c:密文(c>=0&&c<n)

加密算法:
c=m^e mod n

解密算法:
m=c^d mod n

*/

#ifndef __RSA_H
#define __RSA_H

#pragma once

#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int Prime_Judge(int number);//判断number是否为质数
int Greatest_Common_Divisor_Calculate(int number1,int number2);//计算number1与number2的最大公约数(辗转相除法)
int RSA_All_Check(int p,int q,int n,int e,int d);//检查RSA算法中的所有参数是否正确
int RSA_d_Calculate(int p,int q,int e);//计算RSA算法中的d的值
int RSA_Code(int e,int n,int m);//RSA加密算法c=m^e mod n
int RSA_Decode(int d,int n,int c);//RSA解密算法m=c^d mod n
void Random(int min,int max,int number,int data[]);//生成min到max之间的number个随机数,随机数据存储于data数组中
void RSA_Key_Create(int e_min,int e_max,int number);//产生number组随机RSA算法秘钥参数
void Print_Prime(int min,int max);//显示min到max之间的所有质数
void RSA_e_Calculate(int p,int q,int min,int max);//已知p和q，计算min到max之间符合条件的e的值
void RSA_Print_SmallKey();//为了满足1个char的8位数据的编解码，防止int型范围溢出，产生较小的RSA算法的秘钥参数
int RSA_KeyResult_Check(int p,int q,int n,int e,int d);//为了满足1个char的8位数据的编解码，对0-255加密解密的结果进行校检
void RSA_File_Code(char* readfilename, char* writefilename,int e,int n);//RSA算法的文件加密
void RSA_File_Decode(char* readfilename, char* writefilename,int d,int n);//RSA算法的文件解密

#endif