/*********************************************************************
* ��Ȩ���� (C)2011��ISafeTec��
* 
* �ļ����ƣ�  SorenDefine.h
* ����ժҪ��  ����ϵͳʹ�ö���
* ˵    ����  
* ��ǰ�汾��  1.0.0.0
* ��    �ߣ�  SongQX
* ��    �ڣ�  2011/06/27
***********************************************************************/

#pragma once

#pragma pack(push, 1)

//--------------------------------------------
// �ļ����ܽṹ�嶨�忪ʼ 
//--------------------------------------------

#define SOFTWARE_NAME_LEN	50
#define SOFTWARE_VER_LEN	20

// ������Ϣ
typedef struct tagSoftwareInfo
{
	CHAR		szName[SOFTWARE_NAME_LEN];	// ������ƣ�ֻ����ʾ��
	CHAR		szVersion[SOFTWARE_VER_LEN]; // ����汾
	CHAR		szImage[MAX_PATH]; // ��������
}SOFTWAREINFO;

// ������ܹ���
typedef struct tagSoftwareRule
{
	DWORD			dwSize;	// �ṹ���С��������ڽṹ�忪ʼλ��
	SOFTWAREINFO	SoftwareInfo; // ������Ϣ
	DWORD			dwCryptLength; // ������չ���ĳ���
	DWORD			dwIgnorLength; // ������չ���ĳ���
	BYTE			pszExtList[1]; // ��չ�����ݣ���'|'�ָ���ǰ���Ǽ�����չ���������Ǻ�����չ��
}SOFTWARERULE;


// ���ܷ�ʽ
#define SOREN_CA_NULL			0XFFFF //δ����
#define SOREN_CA_XOR			0XFFFE //ʹ�ü����ʽ����
#define SOREN_CA_AES_LOC		0XFFFD //ʹ��aes���汾���ļ�

// �㷨��Ϣ
typedef struct tagCryptAlgInfo
{
	DWORD		dwSize;	// �ṹ���С
	DWORD		dwAlgCode;	// �㷨����
	DWORD		dwKeyLength; // ��Կ����
	BYTE		pbKey[1];	// ��Կ����
}CRYPTALGINFO;


// ��������ʹ�õ��㷨
typedef struct tagCryptAlgType
{
	DWORD			dwSize;	// �ṹ���С
	DWORD			dwTypeID; // ʹ���㷨�����ͣ������ļ�����Կ���桢����ȡ�
	CRYPTALGINFO	CryptAlgInfo;
}CRYPTALGTYPE;

//--------------------------------------------
// �ļ����ܽ���
//--------------------------------------------


//--------------------------------------------
// �ļ���־�ṹ�嶨�忪ʼ 
//--------------------------------------------

// �ļ���־����������
#define SOREN_LOG_OP_CREATE		0X1
#define SOREN_LOG_OP_READ		0X2
#define SOREN_LOG_OP_WRITE		0X4
#define SOREN_LOG_OP_DELETE		0X8
#define SOREN_LOG_OP_RENAME		0x10 

#define SOREN_LOG_OP_TYPE_ALL	(SOREN_LOG_OP_CREATE | SOREN_LOG_OP_READ | SOREN_LOG_OP_WRITE | SOREN_LOG_OP_DELETE | SOREN_LOG_OP_RENAME) // �����ļ���־����

#define SOREN_LOG_FILTER_USB	0X1000 //��־�������ͣ�usb

// �ļ���־������˵��

// ɾ���ļ�
#define SOREN_LOG_OP_PARAM_DELETE_CLOSE			0X0	//create�ļ�ʱ����delete����
#define SOREN_LOG_OP_PARAM_DELETE_SETINF		0X1	//ͨ��irp_setinformation FileDispositionInformationɾ��


// �ļ���־�� ��д�ļ������Ĳ���
typedef struct tagReadWriteLogParam
{
	LARGE_INTEGER	ByteOffset;
	ULONG			Length;	
}READWRITELOGPARAM;

// �ļ���־
//--------------------------------------------
// ˵��: ԭ�ȵ�FILESYSTEMLOG�ṹ�峤�Ȳ��̶����ĳɹ̶���FILESYSTEMLOGEX
// ʱ��: 2011/07/22
// Add by SongQX
//--------------------------------------------

typedef struct tagFileSystemLogEx
{
	DWORD		dwSize; //�ṹ���С,Ŀǰ��С�ǹ̶��ģ����Բ���Ҫ�õ����ֵ��
	DWORD		dwPid; // ����id
	char		szPath[MAX_PATH]; //·��
	DWORD		dwOpType; //��������
	DWORD		dwOpParam; //����˵��������ȡ���ڲ�������
	//BYTE		bParam[1]; //����˵��������ȡ���ڲ�������
	union
	{
		READWRITELOGPARAM param;		//��дʱʹ��
		char	szNewPath[MAX_PATH];	//������ʹ�ã��ļ����ַ���
	};
}FILESYSTEMLOGEX;

//--------------------------------------------
// �ļ���־���� 
//--------------------------------------------


//--------------------------------------------
// �ļ�Ȩ�޿�ʼ 
//--------------------------------------------

// �ļ��ļ��й���
#define SOREN_FILE_ACCESS_GET_INFO		0X1 //��ȡ���ԣ�δ����
#define SOREN_FILE_ACCESS_SET_INFO		0X2 //�������ԣ�δ����
#define SOREN_FILE_ACCESS_RENAME		0X4 //������
#define SOREN_FILE_ACCESS_DELETE		0X8 //ɾ��
#define SOREN_FILE_ACCESS_SHOW			0X10 //��ʾ
#define SOREN_FILE_ACCESS_OPEN			0X20 //�򿪣�createfile)

// �ļ���
//#define SOREN_FILE_ACCESS_DIR			0X100 //�г��ļ������ݣ�ʹ�ø��ļ����µ���Ŀ¼���ļ�����֧�֣�ʹ��SOREN_FILE_ACCESS_OPEN
//#define SOREN_FILE_ACCESS_MD			0X200 //�������ļ��л��ļ�����δʵ��

// �ļ�

//#define SOREN_FILE_ACCESS_READ		0X100 //���ļ�����֧�֣�ʹ��SOREN_FILE_ACCESS_OPEN
#define SOREN_FILE_ACCESS_WRITE			0X200 //д�ļ���


//#define SOREN_FILE_ACCESS_ALL	(SOREN_FILE_ACCESS_GET_INFO | SOREN_FILE_ACCESS_SET_INFO | SOREN_FILE_ACCESS_RENAME | SOREN_FILE_ACCESS_DELETE | SOREN_FILE_ACCESS_SHOW | SOREN_FILE_ACCESS_READ | SOREN_FILE_ACCESS_WRITE)
#define SOREN_FILE_ACCESS_ALL			0xFFFF

typedef struct tagFileAccessAuth
{
	DWORD	Size;		//�ṹ���С
	BYTE	Directory;	//�Ƿ����ļ��У�ȡֵֻ��0��1����ҪŪ��FILE_ATTRIBUTE_DIRECTORY��0n16����
	ULONG	Access;		//Ȩ��
	char	Path[MAX_PATH];	//·��
}FILEACCESSAUTH;
//--------------------------------------------
// �ļ�Ȩ�޽��� 
//--------------------------------------------


//------------------------------------------------------
// [11/4/2011 Songqx]
// ������ļ�����Ȩ��

// ��չ��
#define  FILEACCESSLISTMODE_BLACK 0
#define  FILEACCESSLISTMODE_WHITE 1

#define  FILEACCESSLISTTYPE_EXT		0
#define  FILEACCESSLISTTYPE_PATH	1

typedef struct tagSoftwareFileAccess
{
	DWORD			dwSize;	// �ṹ���С��������ڽṹ�忪ʼλ��
	SOFTWAREINFO	SoftwareInfo; // ������Ϣ
	DWORD			dwMode;//ģʽ��0Ϊ��������1Ϊ��������
	DWORD			dwType;//���ͣ�0����չ����1��·��
	DWORD			dwParam; // ��չ����
	BYTE			pszTextList[1]; // ��չ����·�����ݣ� ֮����'|'�ָ�.
}SOFTWAREFILEACCESS;

//------------------------------------------------------
#pragma pack(pop)

#define MAX_SOREN_FILE_SIZE		(10 * 1024 * 1024) (10MB)





