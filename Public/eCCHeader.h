#ifndef _ECCHEADER_404E0530_5CE8_4D95_9F3F_013F79B22316_H_
#define _ECCHEADER_404E0530_5CE8_4D95_9F3F_013F79B22316_H_

#ifdef  _AA_DLL_
#define _AA_DLL_EXPORT_		__declspec(dllexport)
#define _AA_DLL_EXPORT_C_ 	extern "C" __declspec(dllexport)
#else
#define _AA_DLL_EXPORT_		__declspec(dllimport)
#define _AA_DLL_EXPORT_C_	extern "C" __declspec(dllimport)
#endif

_AA_DLL_EXPORT_ BOOL GetAccountPolicyInfoEx(OUT char* pData1, OUT char* pData2, OUT char* pData3, OUT char* pData4, OUT char* pData5, OUT char* pData6, OUT char* pData7, OUT char* pData8);		//��ȡ���������ע�����
_AA_DLL_EXPORT_ BOOL GetAccountPolicy(IN int nData);			//�������Ƿ�Ϸ�
_AA_DLL_EXPORT_ BOOL GetAccountPolicyVersion(OUT int* nData);	//��ȡ�Ƿ�Ϊ��ʽ�汾,0-��ʾ�棬1-��ʽ��
_AA_DLL_EXPORT_ BOOL GetAccountPolicyCount(OUT int* nData);		//��ȡ���ܵ���
_AA_DLL_EXPORT_ BOOL GetAccountPolicyOver(OUT char* pData);		//��ȡ���ܽ�ֹ��Чʱ��
_AA_DLL_EXPORT_ BOOL GetAccountPolicyInfo(OUT char* pData);		//��ȡ�汾��Ϣ,(pDataҪ�㹻��Ļ�����)
_AA_DLL_EXPORT_ BOOL InstallA();		//ע�ᵱǰ����Ϊ���֤��ӡ���԰�
_AA_DLL_EXPORT_ BOOL InstallB();		//ע�ᵱǰ����Ϊ�ƴ�ӡ���԰�
_AA_DLL_EXPORT_ BOOL InstallC();		//ע�ᵱǰ����Ϊ�����ӡ���԰�
_AA_DLL_EXPORT_ CString EncryptString(IN CString szOrgString);		//�����ַ���
_AA_DLL_EXPORT_ CString DecryptString(IN CString szEncryptString);	//�����ַ���

#endif	//_ECCHEADER_404E0530_5CE8_4D95_9F3F_013F79B22316_H_