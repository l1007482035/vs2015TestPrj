
#ifndef _NET_CMDANDSTRUCTDEF_HEADER
#define _NET_CMDANDSTRUCTDEF_HEADER
//----------------------------
#define NET_MAXPACK_SIZE	2048

#define PACKINDENTIFY			32165
#define PACK_SMALL			0x0001//С�� tcpĬ�϶���С����tcpЭ�鱣֤��˳��
#define PACK_LARGE			0x0002//��� �鲥��Ĭ���Ǵ������֤˳��
#define PACK_COMPRESS		0x0004//ѹ����
#pragma pack(push, 1)
//��ͷ
typedef struct tag_Net_Pack_Head
{
	UINT		nPackBodySize;		//���Ĵ�С����������ͷ
	UINT		nMainCmd;			//������
	UINT		nSubCmd;			//������
	WORD		nIndentify;			//���ı�ʶ
	WORD		nPackMask;			//�ִ����С�����Ƿ�Ϊ	ѹ����������������
	UINT		nReserve;			//tcpʱ�������ֶΣ��ϲ㲻����ʹ�ô��ֶΣ���Ϊѹ����ʱ�����ֶα�ʶδѹ��ǰ���Ĵ�С
	//�鲥������ʱ����ʶ�鲥����Դ��ip��ѧ��id
}NET_PACK_HEAD,*PNET_PACK_HEAD;

//--------------------------
//�����ͷ��nPackMaskΪ���ʱ�Ż�ʹ��
typedef struct tag_LargePackHead
{
	UINT		nGUID;				//UDP���ݰ�ʱ��
	WORD		nPackCount;			//���ʱΪ�����ݰ�����
	WORD		nPackIndex;			//���ʱΪ�����ݰ��������±��1��ʼ
	UINT		nSrcID;				//������Դ��ʶ����ͬʱ���ڶ������Դʱʹ��
	UINT		nAllBodySize;		//һ��������ܴ�С
}LARGEPACK_HEAD,*PLARGEPACK_HEAD;

//-----------------------------
//ѹ����ͷ��nPackMaskΪѹ����ʱ�Ż�ʹ��
typedef struct tag_CompressPackHead
{
	UINT		nCompressedSize;		//ѹ�����С
	UINT		nUncompressedSize;		//δѹ����С
	UINT		nCompressLevel;			//ѹ������
}COMPRESSPACK_HEAD,*PCOMPRESSPACK_HEAD;

typedef struct tag_BufferBlockHead
{
	UINT	nBufferBlockSize;	//�����������Ĵ�С
	UINT	nBufferHeadSize;	//������ͷ�ṹ�Ĵ�С
	long	nRefCount;			//���ü�����Ϊ0ʱ�ͷŻ�����
	UINT	nSourceThreadID;	//����Դ���߳�ID
	UINT    nSourceEquipID;		//����Դ�豸ID
	BOOL	bTempBigBlock;		//�Ƿ�����ʱ���ٵĴ��ڴ滺����	
//	UINT	nSourceClassID;		//������������ĸ��༶ģ�͵ģ���ѧ������ʦ�ģ�
}BUFBLOCK_HEAD;

// ������֤��������ݲ���
// edited by jarry 2012-1-16
typedef struct tag_ExternSegment
{
	DWORD	dwCulTime;
}EXTERNSEG;

typedef struct tag_DATA_PACK	//ֱ��ת�����ݰ��ṹ
{
	UINT	nMainCmd;
	UINT	nSubCmd;
	UINT	nMgrID;					//�����ID
	UINT	nEquipCount;			//ѧ������
	UINT	nEquipIDListOffset;	//ѧ���б�
//	UINT	nClassCount;		//�༶ģ�͸���
//	UINT	nClassListOffset;	//�༶ģ���б�ƫ��
} DATA_PACK,*PDATA_PACK;

#pragma pack(pop)
typedef void (*PFOnBCData)(BYTE* pBuf,int nLen,DWORD,DWORD,int);
typedef void (*PFOnBCDataWithSrcID)(BYTE* pBuf,int nLen,DWORD,DWORD,int,UINT);

#define WM_NETBASE				WM_USER + 1000
#define WM_NEW_CLIENT_SOCK		WM_NETBASE + 1
#define WM_SOCKET_ON_CLOSE		WM_NETBASE + 2
#define WM_REDIRECT_PACK		WM_NETBASE + 3
#define WM_SOCKET_CMPLT			WM_NETBASE + 4
#endif