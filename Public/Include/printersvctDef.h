#ifndef __GL_PRINTER_SVC____
#define __GL_PRINTER_SVC____


/************************************************************************/
/* ��Ŀ��λ��Աע�⣺add by zhandongbao 2008.12.17

1.����һ���ṹ���ĳ�ֶγ��Ȳ���ʱ��ʹ�ú����һ�£���ѧ�����ƣ�
	#define NAME_SIZE 50
	char szName[STU_NAME_SIZE];
2.����һ���ṹ��Ҫ�������������ṹ�������ͽṹ��ĸ����ֶ�����
2.������ʹ�õĽṹ��Ҫע����뷽ʽ
3.����ʹ�õĽṹ�壬���ʹ��Ĭ�϶��뷽ʽ
                                                                     */
/************************************************************************/



// #define WM_PRINT_MGR_REQ_JOB	1026	//��ӡ�����ն������ӡ�б�
// #define WM_PRINT_MGR_CHECK_USER	1028	//��ӡ�����ն���֤�û�
// #define WM_PRINT_MGR_REQ_JOB_FILE 1029	//��ӡ�����ն������ӡ�б�
#pragma pack(push, 1)

//δ��Ӵ�ӡվ��
class CWebSubmitJob
{
public:
	int nAccount;				//�û���
	bool bDuplx;
	bool bColor;
	int  nPageType;
	char szPath[MAX_PATH + 1];	//·��
	char szSnapPath[MAX_PATH + 1];
	char szDocName[MAX_PATH + 1];
};

#pragma pack(pop)

#define WM_WEB_SUBMIT_JOB					WM_USER + 1032	//
#define WM_XPS_TOOL_SUBMIT_JOB				WM_USER + 1033	//


#endif