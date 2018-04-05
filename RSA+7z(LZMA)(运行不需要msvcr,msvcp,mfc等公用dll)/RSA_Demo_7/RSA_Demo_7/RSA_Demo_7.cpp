// RSA_Demo_7.cpp : �������̨Ӧ�ó������ڵ㡣

//#include <tchar.h>
#include <afx.h>
#include <afxwin.h>//MFC��������ͱ�׼���
#include <afxext.h>//MFC��չ
//#include <afxdtctl.h>//MFC��Internet Explorer 4�����ؼ���֧��
//#include <afxcmn.h>//MFC��Windows�����ؼ���֧��
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


// Ψһ��Ӧ�ó������

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(NULL);

	if (hModule != NULL)
	{
		// ��ʼ�� MFC ����ʧ��ʱ��ʾ����
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			// TODO: ���Ĵ�������Է���������Ҫ
			_tprintf(_T("����: MFC ��ʼ��ʧ��\n"));
			nRetCode = 1;
		}
		else
		{
			// TODO: �ڴ˴�ΪӦ�ó������Ϊ��д���롣
			int choice=0;
			printf("��ΪJXL�����ļ��ܽ��ܳ��򣬽���ֻ��С�ļ����м��ܽ��ܲ��������ڼ��ܽ����㷨�ϸ��ӣ�����ļ������ʹ�ü��ܽ��ܵ�ʱ��ϳ���\n����������1��\n����������2��\n");
			scanf("%d",&choice);
			if(choice==1)//����
			{
				printf("�뽫�����ܵ��ļ�ֱ�����뵽�˿���̨�Ի����м���\n");
				char Origin_path_name[100];
				char RSA_Coded_path_name[100];
				char RSA_Coded_path_name_temp[100];
				char LZMA_7z_Coded_path_name[100];
				char Origin_file_name[100];
				scanf("%s",Origin_path_name);
				printf("���ڼ�����...\n");
				MyCreatDirectory(_T(".\\cache"));//�ڵ�ǰĿ¼���½�һ����ʱ�ļ���cache
				strcpy(Origin_file_name,MyGetFileName(Origin_path_name));//��·���л�ȡ�ļ���
				sprintf(RSA_Coded_path_name_temp,".\\cache\\%s",Origin_file_name);
				strcpy(RSA_Coded_path_name,MyAddFileName(RSA_Coded_path_name_temp,"(�������ʱ�ļ�)"));
				strcpy(LZMA_7z_Coded_path_name,MyAddFileName(Origin_path_name,"(�Ѽ���)"));
				RSA_File_Code(Origin_path_name,RSA_Coded_path_name,133,29213);//RSA�㷨���� e=133 n=29213 (p=131,q=223,n=29213,e=133,d=217)
				My7z_LZMA_CodeFile(RSA_Coded_path_name,LZMA_7z_Coded_path_name);//LZMA�㷨����7zѹ��
				DeleteFile(MyCharToLPCTSTR(RSA_Coded_path_name));//ɾ��RSA���ܺ�δ����zlibѹ��ʱ��������ʱ�ļ�
				RemoveDirectory(_T(".\\cache"));//ɾ����������ʱ�ļ���cache
				printf("�������!\n��������˳�\n");
				getch();
			}
			else if(choice==2)//����
			{
				printf("�뽫�����ܵ��ļ�ֱ�����뵽�˿���̨�Ի����м���\n");
				char Origin_path_name[100];
				char LZMA_7z_Decoded_path_name[100];
				char LZMA_7z_Decoded_path_name_temp[100];
				char RSA_Decoded_path_name[100];
				char Origin_file_name[100];
				scanf("%s",Origin_path_name);
				printf("���ڽ�����...\n");
				MyCreatDirectory(_T(".\\cache"));//�ڵ�ǰĿ¼���½�һ����ʱ�ļ���cache
				strcpy(Origin_file_name,MyGetFileName(Origin_path_name));//��·���л�ȡ�ļ���
				sprintf(LZMA_7z_Decoded_path_name_temp,".\\cache\\%s",Origin_file_name);
				strcpy(LZMA_7z_Decoded_path_name,MyAddFileName(LZMA_7z_Decoded_path_name_temp,"(�������ʱ�ļ�)"));
				strcpy(RSA_Decoded_path_name,MyAddFileName(Origin_path_name,"(�ѽ���)"));
				My7z_LZMA_DecodeFile(Origin_path_name,LZMA_7z_Decoded_path_name);//LZMA�㷨����7z��ѹ��
				RSA_File_Decode(LZMA_7z_Decoded_path_name,RSA_Decoded_path_name,217,29213);//RSA�㷨���� d=217 n=29213 (p=131,q=223,n=29213,e=133,d=217)
				DeleteFile(MyCharToLPCTSTR(LZMA_7z_Decoded_path_name));//ɾ��RSA���ܺ�δ����zlibѹ��ʱ��������ʱ�ļ�
				RemoveDirectory(_T(".\\cache"));//ɾ����������ʱ�ļ���cache
				printf("�������!\n��������˳�\n");
				getch();
			}
			else//��������
			{
				printf("��������������󣬰�������˳�\n");
				getch();
			}
		}
	}
	else
	{
		// TODO: ���Ĵ�������Է���������Ҫ
		_tprintf(_T("����: GetModuleHandle ʧ��\n"));
		nRetCode = 1;
	}

	return nRetCode;
}
