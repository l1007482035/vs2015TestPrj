//int rBuffer[22];          	//���ջ����� ����
//int sBuffer[22];           //���ͻ����� ����

#ifdef __cplusplus
extern "C" {
#endif

extern "C" _declspec(dllimport) int StrHexToByte(char* Value,int len,int* ByteArray);
extern "C" _declspec(dllimport) int StrHexToChar(char* Value,int len,char* CharArray);

extern "C" _declspec(dllimport) int OpenPort(int Port);     //�򿪴���
extern "C" _declspec(dllimport) int ClosePort(int Port);    //�رմ���
extern "C" _declspec(dllimport) int Call(int Port);         //����
extern "C" _declspec(dllimport) int BeepEx(int Port);       //����     

extern "C" _declspec(dllimport) int LoadAPassword(int Port,int Block,char* Psw);  //װ������
extern "C" _declspec(dllimport) int ReadData(int Port,int Block,char* Data);      //��������
extern "C" _declspec(dllimport) int WriteData(int Port,int Block,char* Data);     //д������
extern "C" _declspec(dllimport) int GetCardNo(int Port,char* CardNo);             //ȡ����
//��ָ����д�붨���ַ���
extern "C" _declspec(dllimport) int WriteDataEx(int Port,int Block,char* Psw,char* pData,int len);
//��ָ����д�붨���ַ���
extern "C" _declspec(dllimport) int ReadDataEx(int Port,int Block,char* Psw,char* pData,int len);
//�޸�����
extern "C" _declspec(dllimport) int ChangePassword(int Port,int Sector,char* OldPsw,char* NewPsw);

#ifdef __cplusplus
}
#endif