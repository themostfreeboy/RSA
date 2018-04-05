/*
��1��˵��(��������bug)��
����MakePrime�����������ܳ���ʱ�����⣬��������Ҫ������Ҫͨ��rsa1024_checkprivatekey������֤�������ܳ��Ƿ����Ҫ�󣬺����ڲ���Ϊ���ۼ��(��׼ȷ)��ʵ�����ݲ��Լ��(��׼ȷ)�����ֽ��С�
�������������ݲ��ԣ����ִ˰汾��һ���ǳ����ص�bug��
�˳������RSA��1024λ����ǿ�ȵ��㷨�������÷��鴦��ÿ��1024λ����1024/8=128byte��Ҳ����128/4=32(int)����ÿ������ݷֱ����RSA�㷨�ļ��ܲ��������һ���в�ȫ�����ݲ���(128-left_byte)�ķ�ʽ��ȫ��Ϊ�˱���left_byte(��Χ0~127)Ϊ0�����Բ���(128-left_byte)(��Χ1~128)��Ȼ���ٶ����һ����ܴ������ҳ���д���ļ�ʱ�����ļ�ͷд����3��byte�ı�־λ�����ڱ�־���ļ��Ƿ�Ϊ��������������н��ܹ��̶�Ӧ������������ɡ�
���ǣ����ļ�Ϊ���ı��ĵ����ĵ����ݾ�ΪASC2��ʱһ�������⣬������������ʱ�����ߴ������������ļ�ʱ������ȡÿ��1024λ(��128byte)�����һ��byteʱ��������ֽ����ݵĶ��������λΪ1����Ϊ0������Ӧ��ʮ�����Ʒ�ΧΪ0x80~0xffʱ��Ҳ�������temp_in[31]Ϊ0x80~0xffʱ���ڽ���RSA�㷨�ĺ��Ĳ���ʱ����vlong��������������ص�ָ��������ȡģ����ʱ���Ὣ������Ϊ�з������ĸ���������������Ϊ�޷�����������ʱ���������������ģ����ٰѴ�����������ܻ�ȥ�ᵼ�½��ܵĽ����ԭ����һ�¡�(��Ȼ��������ı��ĵ��������������ĵ�����������128-left_byte=128ʱҲ����˷�Χ�ڣ�Ҳ�ᵼ�´�bug��)
��������Ĳ鿴����û�з��־����ںδ���������Ϊ���з���������ֻ�Ǿ������������vlong���У�����Ĳ����������õ��ĺ�������Encrypt��encrypt��modexp��monty��modinv��exp��monty_exp��docopy��copy��clear�У���δ���־����ںδ���Ϊ���з���������
���Դ�bug�޷�ͨ���޸���Ӧ��vlong�����ĺ��ļ��㲿�ֽ����
�������վ�������һ�汾�н��ļ��ӽ��ܵķ����㷨�޸ģ������޸�RSA�㷨�ĺ��ļ��㲿�֡�
�����޸ķ�����Ŀǰ���㣬��ÿ��ֳ�127byte����������bug�����λtemp_in[31]ǿ����Ϊ0x00����󲹳����ݲ��ֵĲ���ֵ��Ϊ(127-left_byte)����������ֵ������⼫�������ϸ�ڲ���Ҳ����Ӧ�ĵ��������������Խ�������˰汾������bug�����ܹ�����Ϊ���·���������̡�

��2��˵����
�˰汾���޸���������bug��������õķ������������Ľ��������

��3��˵��(��ǰ��)��
����private_key��ֻ������p��q��n��e����û�б���d������ÿ�ν���ʱ����Ҫ������Щ�������d���ٽ�����Ӧ��������������������ʱÿ�ν��ܶ����ظ�����d��ֵ���ķ��˴���������ʱ�䣬���ԸĽ�������d��ֵ�ڲ����ܳ�ʱ���Ѿ�����������洢��private_key���У���Ӧ���������Լ�������غ���������Ӧ�ĸı䡣
*/

#include "myrsa.h"

private_key MakePrime(const unsigned long mode)//���ɴ�����p,q��n,e,d
{
	private_key pkey;
	char prand[2][512],tc;
	DWORD i,j,nn, nCount;
	srand((unsigned)time(NULL));
	if(mode == MODE_256)              nCount = 16;//����256λ
	    else if(mode == MODE_512)     nCount = 32;//����512λ
	    else if(mode == MODE_1024)    nCount = 64;//����1024λ
		else if(mode == MODE_2048)    nCount = 128;//����2048λ
		else if(mode == MODE_4096)    nCount = 256;//����4096λ

	for(i=0; i<2; i++)
	{
		for(j=0; j<nCount; j++)
		{
			tc = (char)(0x41+rand()%0xaf);
			prand[i][j] = tc;
		}
		prand[i][j]=0;
	}
	pkey.create(prand[0], prand[1]);//������������������p,q,�Լ�n,e,d
	return pkey;
}

vlong Encrypt(const private_key pkey, const vlong m)//����
{
	private_key temppkey;
	temppkey.p = pkey.p;
	temppkey.q = pkey.q;
	temppkey.n = pkey.n;
	temppkey.e = pkey.e;
	temppkey.d = pkey.d;
	vlong c = temppkey.encrypt(m);
	return c;
}

vlong Decrypt(const private_key pkey, const vlong c)//����
{
	private_key temppkey;
	temppkey.p = pkey.p;
	temppkey.q = pkey.q;
	temppkey.n = pkey.n;
	temppkey.e = pkey.e;
	temppkey.d = pkey.d;
	vlong m = temppkey.decrypt(c);
	return m;
}

void print_privatekey(const private_key pkey)//��ʾ˽Կ
{
	printf("p.length=%u\n",pkey.p.value->n);
	for(int i=0;i<pkey.p.value->n;i++)
	{
		printf("p[%u]=%08x\n",i,pkey.p.value->a[i]);
	}
	printf("q.length=%u\n",pkey.q.value->n);
	for(int i=0;i<pkey.q.value->n;i++)
	{
		printf("q[%u]=%08x\n",i,pkey.q.value->a[i]);
	}
	printf("n.length=%u\n",pkey.n.value->n);
	for(int i=0;i<pkey.n.value->n;i++)
	{
		printf("n[%u]=%08x\n",i,pkey.n.value->a[i]);
	}
	printf("e.length=%u\n",pkey.e.value->n);
	for(int i=0;i<pkey.e.value->n;i++)
	{
		printf("e[%u]=%08x\n",i,pkey.e.value->a[i]);
	}
	printf("d.length=%u\n",pkey.d.value->n);
	for(int i=0;i<pkey.d.value->n;i++)
	{
		printf("d[%u]=%08x\n",i,pkey.d.value->a[i]);
	}
}

void print_vlong(const vlong vl)//��ʾvlong����
{
	printf("vl.length=%u\n",vl.value->n);
	for(int i=0;i<vl.value->n;i++)
	{
		printf("vl[%u]=%08x\n",i,vl.value->a[i]);
	}
}

bool rsa1024_checkprivatekey(const private_key pkey)//����ܳ��Ƿ����Ҫ��(���̽�����ʱ��ϳ�)
{
	//������(ʵ�ʴ˴������⼴����������ܳ׵��㷨�����ô���������ܳף����ô˹��������࣬�˹�������Ҫ���������絼����ܳ��Ƿ���Ϲ��������������������������ʱ���ʵ�ʼ�����ݵļ��ܽ��ܡ�)
	if(is_probable_prime(pkey.p)==0)                        return false;//is_probable_prime���������������ȫ��ֻ������ܷ�100���ڵ�25����������
	if(is_probable_prime(pkey.q)==0)                        return false;
	if(pkey.p*pkey.q!=pkey.n)                               return false;
	if(gcd(pkey.p-1,pkey.e)!=1||gcd(pkey.q-1,pkey.e)!=1)    return false;
	if(pkey.d!=modinv(pkey.e,(pkey.p-1)*(pkey.q-1)))        return false;

	 //����ʵ�����ݼ��
	vlong m;
	vlong c;
	vlong mm;
	unsigned long a[32]={0x61626364,0x65666779};
	for(int i=2;i<32;i++)   a[i]=0x79797979;
	m.load(a,32);
	c=Encrypt(pkey,m);
	mm=Decrypt(pkey,c);
	if(m!=mm)    return false;
	return true;
}

long rsa1024_MyGetFileSize(const char* filename)//��ȡ�ļ���С�����ô˺���ʱ���ļ����봦��δ�򿪶�д״̬
{
	FILE *fp = NULL;
	errno_t err;
	err = fopen_s(&fp, filename, "rb");
	if (err != 0)
	{
		return -1;//�ļ���ʧ��
	}
    fseek(fp,0,SEEK_SET);
    fseek(fp,0,SEEK_END);
    long filesize=ftell(fp);
    rewind(fp);
	fclose(fp);
	return filesize;
}

int rsa1024_file_code(const char* readfilename, const char* writefilename, private_key &pkey, const unsigned long mode)//RSA�㷨1024λ����ǿ�ȼ��ܣ��ļ�ͷ��д��3��byte��־λ
{
	//���readfilename�ļ��Ƿ����
	errno_t err_read;
	FILE *fp_read = NULL;
	err_read = fopen_s(&fp_read, readfilename, "rb");
	if (err_read != 0)
	{
		return -1;//�ļ���ʧ��
	}
	fclose(fp_read);

	long read_filesize=rsa1024_MyGetFileSize(readfilename);//��ȡreadfilename�ļ���С
	if(read_filesize == -1)
	{
		return -6;//�ļ���ʧ��
	}
	if(mode==MODE_CREATEPRIVATEKEY)//����ʱ�����ܳ�
	{
		pkey=MakePrime(MODE_1024);//����1024λ��Կ
		while(rsa1024_checkprivatekey(pkey)==false)//�������ܳײ�����Ҫ��
		{
			pkey=MakePrime(MODE_1024);//���²���1024λ��Կ
		}
	}
	else if(mode==MODE_NOCREATEPRIVATEKEY_CHECKPRIVATEKEY)//����ʱ�������ܳף�ʹ�ø������ܳף������������ܳ׵ĺϷ���
	{
		if(rsa1024_checkprivatekey(pkey)==false)//�ܳײ�����Ҫ��
		{
			return -7;//�ܳײ�����Ҫ��
		}
	}
	else if(mode==MODE_NOCREATEPRIVATEKEY_NOCHECKPRIVATEKEY)//����ʱ�������ܳף�ʹ�ø������ܳף�Ҳ�����������ܳ׵ĺϷ��ԣ�������������ǰ�Ѽ�����ܳ׺Ϸ��Ե����
	{
		//��ִ���κβ���
	}
	unsigned long temp_in[32];
	unsigned long temp_out[32];
	vlong m;
	vlong c;
	long read_time=read_filesize/127+1;

	//readfilename�ļ�����
	errno_t err_write;
	FILE *fp_write = NULL;
	err_read = fopen_s(&fp_read, readfilename, "rb");
	if (err_read != 0)
	{
		return -3;//�ļ���ʧ��
	}
	err_write = fopen_s(&fp_write, writefilename, "wb");
	if (err_write != 0)
	{
		fclose(fp_read);
		return -4;//�ļ���ʧ��
	}

	//ͷ��д��3��byte��־λ
	fprintf(fp_write,"%c",('r')&(0xff));//����rsa�㷨����
	fprintf(fp_write,"%c",('2')&(0xff));//����MODE_1024=2��1024λ��Կǿ��
	fprintf(fp_write,"%c",('c')&(0xff));//����code���ܴ���

	unsigned char tempchar=0;
	unsigned int tempint=0;

	//ǰ(read_time-1)�εļ��ܴ���
	for(int i=0;i<read_time-1;i++)
	{
		for(int j=0;j<32;j++)
		{
			if(j==31)//�����һ�汾bug�Ķ�temp_in[31]�ĵ�������
			{
				tempint=0;
			    for(int k=0;k<3;k++)
		        {
			        fscanf(fp_read,"%c",&tempchar);
		            tempint=(tempint<<8)|(tempchar&(0xff));
		        }
			    temp_in[j]=tempint;
			}
			else
			{
				tempint=0;
			    for(int k=0;k<4;k++)
		        {
			        fscanf(fp_read,"%c",&tempchar);
		            tempint=(tempint<<8)|(tempchar&(0xff));
		        }
			    temp_in[j]=tempint;
			}
		}
		m.load(temp_in,32);
		c=Encrypt(pkey,m);
		c.store(temp_out,32);
		for(int j=0;j<32;j++)
		{
			tempint=temp_out[j];
			for(int k=0;k<4;k++)
			{
				tempchar=(tempint>>(24-8*k))&(0xff);
			    fprintf(fp_write,"%c",tempchar);
			}
		}
	}

	//���һ�εļ��ܴ���
	//���һ���������ݲ��ֵĴ���
	unsigned long left_byte=read_filesize-(read_time-1)*127;
	int j=0;
	for(j=0;j<left_byte/4;j++)
	{
		tempint=0;
		for(int k=0;k<4;k++)
		{
			fscanf(fp_read,"%c",&tempchar);
		    tempint=(tempint<<8)|(tempchar&(0xff));
		}
		temp_in[j]=tempint;
	}

	//���һ���������ݵ��������һ��int��(4 byte)�����ݲ��ִ���
	tempint=0;
	tempchar=127-left_byte;//Ϊ�˱�����������Ϊ0(left_byte����Χ0~126)�����Բ���(127-left_byte)��������(������Χ1~127)
	for(int i=0;i<4;i++)
	{
		tempint=(tempint<<8)|(tempchar&(0xff));
	}
    for(int i=0;i<left_byte%4;i++)
	{
		fscanf(fp_read,"%c",&tempchar);
		tempint=(tempint<<8)|(tempchar&(0xff));
	}
	temp_in[j]=tempint;
	

	//���һ���������ݲ�������������ݴ���
	tempint=0;
	tempchar=127-left_byte;
	for(int i=0;i<4;i++)
	{
		tempint=(tempint<<8)|(tempchar&(0xff));
	}
	for(int i=j+1;i<32;i++)
	{
		temp_in[i]=tempint;
	}

	//���һ���ֵļ��ܴ���
	m.load(temp_in,32);
	c=Encrypt(pkey,m);
	c.store(temp_out,32);
	for(int j=0;j<32;j++)
	{
		tempint=temp_out[j];
		for(int k=0;k<4;k++)
		{
			tempchar=(tempint>>(24-8*k))&(0xff);
			fprintf(fp_write,"%c",tempchar);
		}
	}

	fclose(fp_read);
	fclose(fp_write);
	return 1;//���ܳɹ�
}

int rsa1024_file_decode(const char* readfilename, const char* writefilename, const private_key pkey)//RSA�㷨1024λ����ǿ�Ƚ��ܣ�У���ļ�ͷ��д���3��byte��־λ
{
	//���readfilename�ļ��Ƿ����
	errno_t err_read;
	FILE *fp_read = NULL;
	err_read = fopen_s(&fp_read, readfilename, "rb");
	if (err_read != 0)
	{
		return -1;//�ļ���ʧ��
	}
	fclose(fp_read);

	long read_filesize=rsa1024_MyGetFileSize(readfilename);//��ȡreadfilename�ļ���С
	if(read_filesize == -1)
	{
		return -6;//�ļ���ʧ��
	}
	if(read_filesize%128!=3)//�������ļ�����
	{
		return -2;//�������ļ�����
	}

	unsigned long temp_in[32];
	unsigned long temp_out[32];
	vlong m;
	vlong c;
	unsigned long read_time=(read_filesize-3)/128;

	//readfilename�ļ�����
	errno_t err_write;
	FILE *fp_write = NULL;
	err_read = fopen_s(&fp_read, readfilename, "rb");
	if (err_read != 0)
	{
		return -3;//�ļ���ʧ��
	}

	//У��ͷ��д���3��byte��־λ
	unsigned char tempchar1=0,tempchar2=0,tempchar3=0;
	fscanf(fp_read,"%c",&tempchar1);//����rsa�㷨����
	fscanf(fp_read,"%c",&tempchar2);//����MODE_1024=2��1024λ��Կǿ��
	fscanf(fp_read,"%c",&tempchar3);//����code���ܴ���
	if(tempchar1!='r' || tempchar2!='2' || tempchar3!='c')//�������ļ�����
	{
		fclose(fp_read);
		return -5;
	}

	err_write = fopen_s(&fp_write, writefilename, "wb");
	if (err_write != 0)
	{
		fclose(fp_read);
		return -4;//�ļ���ʧ��
	}

	unsigned char tempchar=0;
	unsigned int tempint=0;

	//ǰ(read_time-1)�εĽ��ܴ���
	for(int i=0;i<read_time-1;i++)
	{
		for(int j=0;j<32;j++)
		{
			tempint=0;
			for(int k=0;k<4;k++)
		    {
			    fscanf(fp_read,"%c",&tempchar);
		        tempint=(tempint<<8)|(tempchar&(0xff));
		    }
			temp_in[j]=tempint;
		}
		c.load(temp_in,32);
		m=Decrypt(pkey,c);
		m.store(temp_out,32);
		for(int j=0;j<32;j++)
		{
			if(j==31)//�����һ�汾bug�Ķ�temp_out[31]�ĵ�������
			{
				tempint=temp_out[j];
			    for(int k=1;k<4;k++)
		        {
			        tempchar=(tempint>>(24-8*k))&(0xff);
			        fprintf(fp_write,"%c",tempchar);
		        }
			}
			else
			{
				tempint=temp_out[j];
			    for(int k=0;k<4;k++)
		        {
			        tempchar=(tempint>>(24-8*k))&(0xff);
			        fprintf(fp_write,"%c",tempchar);
		        }
			}
		}
	}

	//���һ�εĽ��ܴ���
	for(int j=0;j<32;j++)
	{
		tempint=0;
		for(int k=0;k<4;k++)
		{
			fscanf(fp_read,"%c",&tempchar);
		    tempint=(tempint<<8)|(tempchar&(0xff));
		}
		temp_in[j]=tempint;
	}
	c.load(temp_in,32);
	m=Decrypt(pkey,c);
	m.store(temp_out,32);

	//���һ���������ݲ��ֵĴ���
	unsigned long left_byte=127-(temp_out[31]>>24)&(0xff);
	int j=0;
	for(j=0;j<left_byte/4;j++)
	{
		tempint=temp_out[j];
		for(int k=0;k<4;k++)
		{
			tempchar=(tempint>>(24-8*k))&(0xff);
			fprintf(fp_write,"%c",tempchar);
		}
	}

	//���һ���������ݵ��������һ��int��(4 byte)�����ݲ��ִ���
	tempint=temp_out[j];
	for(int i=0;i<left_byte%4;i++)
	{
		tempchar=(tempint>>(8*(left_byte%4-i-1)))&(0xff);
		fprintf(fp_write,"%c",tempchar);
	}

	fclose(fp_read);
	fclose(fp_write);
	return 1;//���ܳɹ�
}

int rsa1024_privatekey_outtofile(const char* writefilename, const private_key pkey)//�����ܳ׵��ļ�
{
	//���writefilename�ļ��ܷ��
	errno_t err_write;
	FILE *fp_write = NULL;
	err_write = fopen_s(&fp_write, writefilename, "wb");
	if (err_write != 0)
	{
		return -1;//�ļ���ʧ��
	}

	//ͷ��д��3��byte��־λ
	fprintf(fp_write,"%c",('r')&(0xff));//����rsa�㷨����
	fprintf(fp_write,"%c",('2')&(0xff));//����MODE_1024=2��1024λ��Կǿ��
	fprintf(fp_write,"%c",('k')&(0xff));//����key�ܳ��ļ�

	unsigned char tempchar=0;
	unsigned int tempint=0;

	//д��p
	tempint=pkey.p.value->n;
	tempchar=tempint&(0xff);
	fprintf(fp_write,"%c",tempchar);
	for(int i=0;i<pkey.p.value->n;i++)
	{
		tempint=pkey.p.value->a[i];
		for(int j=0;j<4;j++)
		{
			tempchar=(tempint>>(24-8*j))&(0xff);
		    fprintf(fp_write,"%c",tempchar);
		}
	}

	//д��q
	tempint=pkey.q.value->n;
	tempchar=tempint&(0xff);
	fprintf(fp_write,"%c",tempchar);
	for(int i=0;i<pkey.q.value->n;i++)
	{
		tempint=pkey.q.value->a[i];
		for(int j=0;j<4;j++)
		{
			tempchar=(tempint>>(24-8*j))&(0xff);
		    fprintf(fp_write,"%c",tempchar);
		}
	}

	//д��n
	tempint=pkey.n.value->n;
	tempchar=tempint&(0xff);
	fprintf(fp_write,"%c",tempchar);
	for(int i=0;i<pkey.n.value->n;i++)
	{
		tempint=pkey.n.value->a[i];
		for(int j=0;j<4;j++)
		{
			tempchar=(tempint>>(24-8*j))&(0xff);
		    fprintf(fp_write,"%c",tempchar);
		}
	}

	//д��e
	tempint=pkey.e.value->n;
	tempchar=tempint&(0xff);
	fprintf(fp_write,"%c",tempchar);
	for(int i=0;i<pkey.e.value->n;i++)
	{
		tempint=pkey.e.value->a[i];
		for(int j=0;j<4;j++)
		{
			tempchar=(tempint>>(24-8*j))&(0xff);
		    fprintf(fp_write,"%c",tempchar);
		}
	}

	//д��d
	tempint=pkey.d.value->n;
	tempchar=tempint&(0xff);
	fprintf(fp_write,"%c",tempchar);
	for(int i=0;i<pkey.d.value->n;i++)
	{
		tempint=pkey.d.value->a[i];
		for(int j=0;j<4;j++)
		{
			tempchar=(tempint>>(24-8*j))&(0xff);
		    fprintf(fp_write,"%c",tempchar);
		}
	}

	fclose(fp_write);
	return 1;//�����ɹ�
}

int rsa1024_privatekey_loadfromfile(const char* readfilename, private_key &pkey)//���ļ��е����ܳ�
{
	//���readfilename�ļ��Ƿ����
	errno_t err_read;
	FILE *fp_read = NULL;
	err_read = fopen_s(&fp_read, readfilename, "rb");
	if (err_read != 0)
	{
		return -1;//�ļ���ʧ��
	}

	//У��ͷ��д���3��byte��־λ
	unsigned char tempchar1=0,tempchar2=0,tempchar3=0;
	fscanf(fp_read,"%c",&tempchar1);//����rsa�㷨����
	fscanf(fp_read,"%c",&tempchar2);//����MODE_1024=2��1024λ��Կǿ��
	fscanf(fp_read,"%c",&tempchar3);//����key�ܳ��ļ�
	if(tempchar1!='r' || tempchar2!='2' || tempchar3!='k')//�������ļ�����
	{
		fclose(fp_read);
		return -2;
	}

	unsigned char tempchar=0;
	unsigned int tempint=0;
	unsigned int templength=0;
	unsigned long tempdata[128];

	//����p
	fscanf(fp_read,"%c",&templength);
	for(int i=0;i<templength;i++)
	{
		tempint=0;
		for(int j=0;j<4;j++)
		{
			fscanf(fp_read,"%c",&tempchar);
		    tempint=(tempint<<8)|(tempchar&(0xff));
		}
		tempdata[i]=tempint;
	}
	pkey.p.load(tempdata,templength);

	//����q
	fscanf(fp_read,"%c",&templength);
	for(int i=0;i<templength;i++)
	{
		tempint=0;
		for(int j=0;j<4;j++)
		{
			fscanf(fp_read,"%c",&tempchar);
		    tempint=(tempint<<8)|(tempchar&(0xff));
		}
		tempdata[i]=tempint;
	}
	pkey.q.load(tempdata,templength);

	//����n
	fscanf(fp_read,"%c",&templength);
	for(int i=0;i<templength;i++)
	{
		tempint=0;
		for(int j=0;j<4;j++)
		{
			fscanf(fp_read,"%c",&tempchar);
		    tempint=(tempint<<8)|(tempchar&(0xff));
		}
		tempdata[i]=tempint;
	}
	pkey.n.load(tempdata,templength);

	//����e
	fscanf(fp_read,"%c",&templength);
	for(int i=0;i<templength;i++)
	{
		tempint=0;
		for(int j=0;j<4;j++)
		{
			fscanf(fp_read,"%c",&tempchar);
		    tempint=(tempint<<8)|(tempchar&(0xff));
		}
		tempdata[i]=tempint;
	}
	pkey.e.load(tempdata,templength);

	//����d
	fscanf(fp_read,"%c",&templength);
	for(int i=0;i<templength;i++)
	{
		tempint=0;
		for(int j=0;j<4;j++)
		{
			fscanf(fp_read,"%c",&tempchar);
		    tempint=(tempint<<8)|(tempchar&(0xff));
		}
		tempdata[i]=tempint;
	}
	pkey.d.load(tempdata,templength);

	fclose(fp_read);
	return 1;//����ɹ�
}