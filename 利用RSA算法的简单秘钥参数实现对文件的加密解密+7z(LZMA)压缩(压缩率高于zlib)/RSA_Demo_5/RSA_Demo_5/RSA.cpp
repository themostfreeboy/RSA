#include "RSA.h"

int Prime_Judge(int number)//�ж�number�Ƿ�Ϊ����
{	
	if(number<2)      return 0;//��������
	int tag=1,i=0;
	for(i=2;i<=sqrt(number*1.0);i++)
	{
		if(number%i==0)
		{
			tag=0;
			return 0;//��������
		}
	}
	if(tag==1)      return 1;//������
}

int Greatest_Common_Divisor_Calculate(int number1,int number2)//����number1��number2�����Լ��(շת�����)
{
	if(number1<0||number2<0)      return -1;//��������
	if(number2==0)      return number1;
	else                return Greatest_Common_Divisor_Calculate(number2,number1%number2);
}

int RSA_All_Check(int p,int q,int n,int e,int d)//���RSA�㷨�е����в����Ƿ���ȷ
{
	if(Prime_Judge(p)==0)                                       return 0;//����ȷ
	if(Prime_Judge(q)==0)                                       return 0;//����ȷ
	if(p*q!=n)                                                  return 0;//����ȷ
	if(Greatest_Common_Divisor_Calculate((p-1)*(q-1),e)!=1)     return 0;//����ȷ
	if((e*d)%((p-1)*(q-1))!=1)                                  return 0;//����ȷ
	return 1;//��ȷ
}

int RSA_d_Calculate(int p,int q,int e)//����RSA�㷨�е�d��ֵ
{
	//�������Ƿ���ȷ
	if(Prime_Judge(p)==0)                                       return -1;//��������ȷ
	if(Prime_Judge(q)==0)                                       return -1;//��������ȷ
	if(Greatest_Common_Divisor_Calculate((p-1)*(q-1),e)!=1)     return -1;//��������ȷ
	//������ȷ
	int d=1;
	while(((e*d)%((p-1)*(q-1)))!=1)                             d++;
	return d;
}

int RSA_Code(int e,int n,int m)//RSA�����㷨c=m^e mod n
{	
	if(!((m>=0)&&(m<n)))            return -1;//��������
	int c=1,i=0;
	for(i=e;i>=1;i--)
	{
		c=c*m;
		c=c%n;
	}
	return c;
}

int RSA_Decode(int d,int n,int c)//RSA�����㷨m=c^d mod n
{	
	if(!((c>=0)&&(c<n)))            return -1;//��������
	int m=1,i=0;
	for(i=d;i>=1;i--)
	{
		m=m*c;
		m=m%n;
	}
	return m;
}

void Random(int min,int max,int number,int data[])//����min��max֮���number�������,������ݴ洢��data������
{
    time_t t;
	int temp=0,i=0;
	if(min>max)//����min��max
	{
		temp=min;
		min=max;
		max=temp;
	}
    srand((unsigned) time(&t));
	for(i=0;i<number;i++)
	{
		data[i]=(rand()%(max-min))+min;
	}
}

void RSA_Key_Create(int e_min,int e_max,int number)//����number�����RSA�㷨��Կ����
{
	int p,q,n,e,d,data[100000],e_i=0,p_i=0,q_i=0;
	Random(e_min,e_max,100000,data);
	e=data[e_i];
	p_i=e%100000;
	p=data[p_i];
	q_i=p%100000;
	q=data[q_i];
	while(number>0)
	{		
		while(Prime_Judge(p)==0)      p=data[(++p_i)%100000];		
		while(Prime_Judge(q)==0)      q=data[(++q_i)%100000];
		if(Greatest_Common_Divisor_Calculate(e,(p-1)*(q-1))==1)
		{
			d=RSA_d_Calculate(p,q,e);
			n=p*q;
			if(RSA_All_Check(p,q,n,e,d)==1)
			{
				printf("p=%d,q=%d,n=%d,e=%d,d=%d\n",p,q,n,e,d);
				number--;
				e=data[(++e_i)%100000];
			}			
		}
		p=data[(++p_i)%100000];
		q=data[(++q_i)%100000];
	}
}

void Print_Prime(int min,int max)//��ʾmin��max֮�����������
{
	int temp=0,i=0;
	printf("\nPrint_Prime start:\n");
	if(min>max)//����min��max
	{
		temp=min;
		min=max;
		max=temp;
	}
	for(i=min;i<=max;i++)
	{
		if(Prime_Judge(i)==1)
		{
			printf("%d\t",i);
		}
	}
	printf("\nPrint_Prime end!\n");
}

void RSA_e_Calculate(int p,int q,int min,int max)//��֪p��q������min��max֮�����������e��ֵ
{
	int temp=0,i=0;
	printf("\nRSA_e_Calculate start:\n");
	if(min>max)//����min��max
	{
		temp=min;
		min=max;
		max=temp;
	}
	for(i=min;i<=max;i++)
	{
		if(Greatest_Common_Divisor_Calculate(i,(p-1)*(q-1))==1)
		{
			printf("%d\t",i);
		}
	}
	printf("\nRSA_e_Calculate end!\n"); 
}

void RSA_Print_SmallKey()//Ϊ������1��char��8λ���ݵı���룬��ֹint�ͷ�Χ�����������С��RSA�㷨����Կ����
{
	int i,j,k,d;
	printf("\nRSA_Print_SmallKey start:\n");
	for(i=3;i<256;i++)
	{
		if(Prime_Judge(i)==1)
		{
			for(j=3;j<256;j++)
			{
				if(Prime_Judge(j)==1)
				{
					for(k=3;k<256;k++)
					{
						if(Greatest_Common_Divisor_Calculate(k,(i-1)*(j-1))==1)
						{
							d=RSA_d_Calculate(i,j,k);
							if(d<256&&RSA_All_Check(i,j,i*j,k,d)==1)
							{
								printf("p=%d,q=%d,n=%d,e=%d,d=%d\n",i,j,i*j,k,d);
							}
						}
					}
				}
			}
		}
	}
	printf("\nRSA_Print_SmallKey end!\n");
}

int RSA_KeyResult_Check(int p,int q,int n,int e,int d)//Ϊ������1��char��8λ���ݵı���룬��0-255���ܽ��ܵĽ������У��
{
	int i,m=0,c=0;
	n=p*q;
	for(i=0;i<256;i++)
	{
		c=RSA_Code(e,n,i);
		m=RSA_Decode(d,n,c);
		printf("ԭʼ����=%d,���ܺ�c=%d,���ܺ�m=%d\n",i,c,m);
		if(m!=i)       return 0;//���ܽ��ܲ���ѡȡʧ��
	}
	return 1;//���ܽ��ܲ���ѡȡ�ɹ�
}

void RSA_File_Code(char* readfilename, char* writefilename,int e,int n)//RSA�㷨���ļ�����(�˺�����ƻ���p=131,q=223,n=29213,e=133,d=217)
{
	errno_t err_read, err_write;
	FILE *fp_read = NULL;
	FILE *fp_write = NULL;
	err_read = fopen_s(&fp_read, readfilename, "rb");
	err_write = fopen_s(&fp_write, writefilename, "wb");
	if (err_read != 0)
	{
		return;//�ļ���ʧ��
	}
	if (err_write != 0)
	{
		return;//�ļ���ʧ��
	}
	unsigned char m=0;
	int c=0;
	unsigned char c_high=0,c_low=0;
	while (fscanf_s(fp_read, "%c", &m) != EOF)
	{
		c=RSA_Code(e,n,(int)m);
		c_high=(c>>8) & (0xff);
		c_low=c & (0xff);
		fprintf_s(fp_write, "%c", c_high);
		fprintf_s(fp_write, "%c", c_low);
		//printf("m=%d,c=%d,c_high=%d,c_low=%d\n",m,c,c_high,c_low);
	}
	fclose(fp_read);
	fclose(fp_write);
}

void RSA_File_Decode(char* readfilename, char* writefilename,int d,int n)//RSA�㷨���ļ�����(�˺�����ƻ���p=131,q=223,n=29213,e=133,d=217)
{
	errno_t err_read, err_write;
	FILE *fp_read = NULL;
	FILE *fp_write = NULL;
	err_read = fopen_s(&fp_read, readfilename, "rb");
	err_write = fopen_s(&fp_write, writefilename, "wb");
	if (err_read != 0)
	{
		return;//�ļ���ʧ��
	}
	if (err_write != 0)
	{
		return;//�ļ���ʧ��
	}
	unsigned char m=0;
	int c=0;
	unsigned char c_high=0,c_low=0;
	while (fscanf_s(fp_read, "%c", &c_high) != EOF)
	{
		fscanf_s(fp_read, "%c", &c_low);
		c=(c_high<<8) | (c_low);
		m=(RSA_Decode(d,n,c)) & (0xff);
		fprintf_s(fp_write, "%c", m);
		//printf("c_high=%d,c_low=%d,c=%d,m=%d\n",c_high,c_low,c,m);
	}
	fclose(fp_read);
	fclose(fp_write);
}