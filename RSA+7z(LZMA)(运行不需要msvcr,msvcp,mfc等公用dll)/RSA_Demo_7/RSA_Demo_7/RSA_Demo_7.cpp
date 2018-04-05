// RSA_Demo_7.cpp : 定义控制台应用程序的入口点。

//#include <tchar.h>
#include <afx.h>
#include <afxwin.h>//MFC核心组件和标准组件
#include <afxext.h>//MFC扩展
//#include <afxdtctl.h>//MFC对Internet Explorer 4公共控件的支持
//#include <afxcmn.h>//MFC对Windows公共控件的支持
//#include <SDKDDKVer.h>

#include <stdio.h>
//#include <stdlib.h>
#include <conio.h>

#include "RSA.h"
#include "MyMFC.h"
#include "My7z.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 唯一的应用程序对象

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(NULL);

	if (hModule != NULL)
	{
		// 初始化 MFC 并在失败时显示错误
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			// TODO: 更改错误代码以符合您的需要
			_tprintf(_T("错误: MFC 初始化失败\n"));
			nRetCode = 1;
		}
		else
		{
			// TODO: 在此处为应用程序的行为编写代码。
			int choice=0;
			printf("此为JXL制作的加密解密程序，建议只对小文件进行加密解密操作，由于加密解密算法较复杂，如果文件过大会使得加密解密的时间较长：\n加密请输入1；\n解密请输入2。\n");
			scanf("%d",&choice);
			if(choice==1)//加密
			{
				printf("请将待加密的文件直接拖入到此控制台对话框中即可\n");
				char Origin_path_name[100];
				char RSA_Coded_path_name[100];
				char RSA_Coded_path_name_temp[100];
				char LZMA_7z_Coded_path_name[100];
				char Origin_file_name[100];
				scanf("%s",Origin_path_name);
				printf("正在加密中...\n");
				MyCreatDirectory(_T(".\\cache"));//在当前目录下新建一个临时文件夹cache
				strcpy(Origin_file_name,MyGetFileName(Origin_path_name));//从路径中获取文件名
				sprintf(RSA_Coded_path_name_temp,".\\cache\\%s",Origin_file_name);
				strcpy(RSA_Coded_path_name,MyAddFileName(RSA_Coded_path_name_temp,"(半加密临时文件)"));
				strcpy(LZMA_7z_Coded_path_name,MyAddFileName(Origin_path_name,"(已加密)"));
				RSA_File_Code(Origin_path_name,RSA_Coded_path_name,133,29213);//RSA算法加密 e=133 n=29213 (p=131,q=223,n=29213,e=133,d=217)
				My7z_LZMA_CodeFile(RSA_Coded_path_name,LZMA_7z_Coded_path_name);//LZMA算法进行7z压缩
				DeleteFile(MyCharToLPCTSTR(RSA_Coded_path_name));//删除RSA加密后但未进行zlib压缩时产生的临时文件
				RemoveDirectory(_T(".\\cache"));//删除产生的临时文件夹cache
				printf("加密完成!\n按任意键退出\n");
				getch();
			}
			else if(choice==2)//解密
			{
				printf("请将待解密的文件直接拖入到此控制台对话框中即可\n");
				char Origin_path_name[100];
				char LZMA_7z_Decoded_path_name[100];
				char LZMA_7z_Decoded_path_name_temp[100];
				char RSA_Decoded_path_name[100];
				char Origin_file_name[100];
				scanf("%s",Origin_path_name);
				printf("正在解密中...\n");
				MyCreatDirectory(_T(".\\cache"));//在当前目录下新建一个临时文件夹cache
				strcpy(Origin_file_name,MyGetFileName(Origin_path_name));//从路径中获取文件名
				sprintf(LZMA_7z_Decoded_path_name_temp,".\\cache\\%s",Origin_file_name);
				strcpy(LZMA_7z_Decoded_path_name,MyAddFileName(LZMA_7z_Decoded_path_name_temp,"(半解密临时文件)"));
				strcpy(RSA_Decoded_path_name,MyAddFileName(Origin_path_name,"(已解密)"));
				My7z_LZMA_DecodeFile(Origin_path_name,LZMA_7z_Decoded_path_name);//LZMA算法进行7z解压缩
				RSA_File_Decode(LZMA_7z_Decoded_path_name,RSA_Decoded_path_name,217,29213);//RSA算法解密 d=217 n=29213 (p=131,q=223,n=29213,e=133,d=217)
				DeleteFile(MyCharToLPCTSTR(LZMA_7z_Decoded_path_name));//删除RSA解密后但未进行zlib压缩时产生的临时文件
				RemoveDirectory(_T(".\\cache"));//删除产生的临时文件夹cache
				printf("解密完成!\n按任意键退出\n");
				getch();
			}
			else//输入有误
			{
				printf("你输入的数据有误，按任意键退出\n");
				getch();
			}
		}
	}
	else
	{
		// TODO: 更改错误代码以符合您的需要
		_tprintf(_T("错误: GetModuleHandle 失败\n"));
		nRetCode = 1;
	}

	return nRetCode;
}
