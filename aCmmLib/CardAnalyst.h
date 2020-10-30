#pragma once
#include "stdafx.h"

class CCardAnalyst
{
public:
	CCardAnalyst(void);
	virtual ~CCardAnalyst(void);

	static CCardAnalyst& GetInstance()
	{
		static CCardAnalyst one;
		return one;
	}
	CString HandleCardNo(CString& szParam);//���Ŵ�����ں���

	CString DecToHex(CString& szParam);//ʮ�����ַ���ת16�����ַ���
	CString HexToDec(CString& szParam);//16�����ַ���ת10�����ַ���
	CString DecRevsToHex(CString& szParam);//10�����ַ�����ת16�����ַ���
	CString DecRevsToDec(CString& szParam);//10�����ַ�����ת10�����ַ���
	CString HexRevsToDec(CString& szParam);//16�����ַ�����ת10�����ַ���
	CString HexRevsToHex(CString& szParam);//16�����ַ�����ת16�����ַ���
	CString Intercept(CString& szParam);//��ȡ�ұ�λ��
	CString AddToLeft(CString& szParam);//������
	CString AddToRight(CString& szParam);//�Ҳ����
	CString Wiegand34To26(CString& szParam);//Τ��34ת26
	CString Concat( CString& szParam);
	CString InterceptLeft(CString& szParam);
	CString InterceptRight(CString& szParam);
	CString StrRevsToStr(CString& szParam);//�ַ�����ת ����1234567890 -> 9078563412
	CString Divide(CString& szParam);//����һ����

	BOOL Split(CString& source, CString& funout, CString& paramout);
	BOOL CheckValidate(CString& szParam);//������Ϸ���
};
