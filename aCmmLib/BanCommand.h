// BanCommand.h
// ����ϵͳ����

class _AA_DLL_EXPORT_ BanCommand
{
public:
	BanCommand();
	~BanCommand();

public:
	static BOOL SetBanDIApplication(BOOL sign);//��ֹ�޸�ɾ��/��ӳ���
	static BOOL SetBanTaskManager(BOOL sign);//��ֹ�޸����������
	static BOOL SetBanLinkProperty(BOOL sign);//��ֹ�޸ı�������
	static BOOL SetBanComputername(BOOL sign);//��ֹ�޸ļ��������
	static BOOL SetBanMenu(BOOL sign);//��ֹ�޸ļ��������
	static BOOL DelStartItem(CString path);//ɾ��������
	static BOOL SetBanRegister(BOOL sign);//��ֹʹ��ע���
	static BOOL SetFileExtShow(BOOL bShow);// ��ʾ�ļ���׺��
};