#pragma once

#ifndef __MY7Z_H
#define __MY7Z_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "7zFile.h"
//#include "7zTypes.h"//��������h�ļ�����
#include "7zVersion.h"
#include "Alloc.h"
//#include "Compiler.h"//��������h�ļ�����
//#include "LzFind.h"//��������h�ļ�����
//#include "LzFindMt.h"//��������h�ļ�����
//#include "LzHash.h"//��������h�ļ�����
#include "LzmaDec.h"
#include "LzmaEnc.h"
#include "Precomp.h"
//#include "Threads.h"//��������h�ļ�����
//������7zStream.cpp

#define IN_BUF_SIZE (1 << 16)//������7z�ٷ�LZMA�㷨SDK��LzmaUtil.c��
#define OUT_BUF_SIZE (1 << 16)//������7z�ٷ�LZMA�㷨SDK��LzmaUtil.c��

void PrintHelp(char *buffer);//������7z�ٷ�LZMA�㷨SDK��LzmaUtil.c��
int PrintError(char *buffer, const char *message);//������7z�ٷ�LZMA�㷨SDK��LzmaUtil.c��
int PrintErrorNumber(char *buffer, SRes val);//������7z�ٷ�LZMA�㷨SDK��LzmaUtil.c��
int PrintUserError(char *buffer);//������7z�ٷ�LZMA�㷨SDK��LzmaUtil.c��
static SRes Decode2(CLzmaDec *state, ISeqOutStream *outStream, ISeqInStream *inStream, UInt64 unpackSize);//������7z�ٷ�LZMA�㷨SDK��LzmaUtil.c��
static SRes Decode(ISeqOutStream *outStream, ISeqInStream *inStream);//������7z�ٷ�LZMA�㷨SDK��LzmaUtil.c��
static SRes Encode(ISeqOutStream *outStream, ISeqInStream *inStream, UInt64 fileSize, char *rs);//������7z�ٷ�LZMA�㷨SDK��LzmaUtil.c��
int main2(int numArgs, const char *args[], char *rs);//������7z�ٷ�LZMA�㷨SDK��LzmaUtil.c��

int My7z_LZMA_CodeFile(const char *in_file_name, const char* out_file_name);//ͨ��LZMA�㷨ѹ��
int My7z_LZMA_DecodeFile(const char *in_file_name, const char* out_file_name);//ͨ��LZMA�㷨��ѹ������ѹһ����My7z_LZMA_CodeFile����ѹ���������ļ��ᵼ�»���������������������bug��δ���

#endif