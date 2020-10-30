#ifndef _PDFHELPER_517B7F85_B0C5_480E_B35B_199AC523DB5A_H_ 
#define _PDFHELPER_517B7F85_B0C5_480E_B35B_199AC523DB5A_H_

#ifdef  _AA_DLL_
#define _AA_DLL_EXPORT_		__declspec(dllexport)
#define _AA_DLL_EXPORT_C_ 	extern "C" __declspec(dllexport)
#else
#define _AA_DLL_EXPORT_		__declspec(dllimport)
#define _AA_DLL_EXPORT_C_	extern "C" __declspec(dllimport)
#endif

#include <windows.h>
#include <shlwapi.h>
#include <cstdio>

#include "PrintProcessDef.h"

#define PDF_DATA_DIR	L"PdfData"		//PDF����cmap������Ŀ¼��

//�ο�SplashColorMode
enum ImageColorMode {
	imageModeMono1,		// 1 bit per component, 8 pixels per byte,
	//   MSbit is on the left
	imageModeMono8,		// 1 byte per component, 1 byte per pixel
	imageModeRGB8,		// 1 byte per component, 3 bytes per pixel:
	//   RGBRGB...
	imageModeBGR8,		// 1 byte per component, 3 bytes per pixel:
	//   BGRBGR...
	imageModeXBGR8		// 1 byte per component, 4 bytes per pixel:
	//   XBGRXBGR...
};

typedef struct  
{
	const char* pszHeader;	//ҳü���ݣ�UTF8����
	const char* pszFooter;	//ˮӡ���ݣ�UTF8����
	const char* pszWater;	//ҳ�����ݣ�UTF8����
}WaterInfo;

enum PageBoxType
{
	MediaBox,
	CropBox,
	BleedBox,
	TrimBox,
	ArtBox
};

typedef struct
{
	double X1;
	double Y1;
	double X2;
	double Y2;
}PageBox;

/* ����CPdfHelper�����Ҫ˵����
1.����·��������ʹ��UTF8���룬�磺cPdfFilePath��GetPdfFilePath�ķ���ֵ��
2.ˮӡ����Ҳ��UTF8���롣
3.��ӡ�������û������ĵ���ʹ��UTF8���롣
*/
class _AA_DLL_EXPORT_ CPdfHelper
{
public:
	//���캯��
	CPdfHelper();

	/**
	* @author zengxl
	* @param cPdfFilePath: pdf�ļ�·����UTF8����
	* @param cOwnerPassword: ����
	* @param cUserPassword: ����
	*/
	//���캯��
	CPdfHelper(const char *cPdfFilePath, const char *cOwnerPassword = NULL, const char *cUserPassword = NULL);


	//��������
	~CPdfHelper();

	/**
	* @author zengxl
	* @param cPdfFilePath: pdf�ļ�·����UTF8����
	* @param cOwnerPassword: ����
	* @param cUserPassword: ����
	* @return BOOL: TURE-�򿪳ɹ���FALSE-��ʧ��
	*/
	//��PDF�ļ�
	BOOL OpenFile(const char *cPdfFilePath, const char *cOwnerPassword = NULL, const char *cUserPassword = NULL);

	/**
	* @author zengxl
	* @return void:
	*/
	//�رձ��򿪵�pdf�ļ�
	void CloseFile();

	/**
	* @author zengxl
	* @return BOOL: TURE-�򿪳ɹ���FALSE-��ʧ��
	*/
	//�ж�PDF�Ƿ���ȷ�Ĵ�
	BOOL IsOK();

	/**
	* @author zengxl
	* @return int: PDF�ļ�ҳ��
	*/
	//��ȡ�򿪵�PDF�ļ�ҳ��
	int GetPageCount();

	/**
	* @author zengxl
	* @return const char*: PDF�ļ�·����UTF8����
	*/
	//��ȡ�򿪵�PDF�ļ�·��
	const char* GetPdfFilePath();

	/**
	* @author zengxl
	* @param nPageIndex: pdfҳ�룬ҳ��������0��ʼ
	* @param hDPI: ��ȡ��λͼ�ĺ���dpi
	* @param vDPI: ��ȡ��λͼ������dpi
	* @param color: ��ȡ��λͼ��ɫ��ģʽ
	* @param nWidth: ��ȡ��λͼ�Ŀ������ֵ����Ϊ��������
	* @param nHeight: ��ȡ��λͼ�ĸ߶�����ֵ����Ϊ��������
	* @param nStride: ��ȡ��λͼ��Strideֵ����Ϊ��������
	* @param scan0: ��ȡ��λͼ������ָ�룬��Ϊ��������
	* @return BOOL: TURE-��ȡ�ɹ���FALSE-��ȡʧ��
	*/
	//��ȡָ��PDFҳ���λͼ���ݣ���scan0��ʹ�����,�������FreeBitmapData�ͷ��ڴ�
	BOOL GetBitmap(int nPageIndex, double hDPI, double vDPI, ImageColorMode color,
		int& nWidth, int& nHeight, int& nStride, unsigned char **scan0);

	/**
	* @author zengxl
	* @param scan0: λͼ������ָ��
	* @return void:
	*/
	//�ͷ�GetBitmap�ӿڷ��ص�λͼ�ڴ�����
	void FreeBitmapData(unsigned char *scan0);

	/**
	* @author zengxl
	* @param cPrinterName: ��ӡ������UTF8����
	* @param cDocName: ��ӡ�ĵ�������UTF8����
	* @param nBeginPage: ��ӡPDF����ʼҳ��ҳ��������0��ʼ�������-1,��ʾ��PDF��һҳ��ʼ��ӡ
	* @param nEndPage: ��ӡPDF�Ľ���ҳ��ҳ��������0��ʼ�������-1,��ʾ��ӡ��PDF���һҳ
	* @param nPagesPerPaper: ���һ��ӡ��������ʾ����ҳPDF���ݴ�ӡ��һ��ֽ���棬ֻ֧��1,2,4,6,8,9,16
	* @param wColor: ��ӡPDF�����ɫ��ģʽ
	* @param wPaperSize: ��ӡPDF�����ֽ�ŵ�ֽ��
	* @param wOrientation: ��ӡPDF��������ݵķ���һ��PDF�����з������ԣ��˲�����ʱ��Ч
	* @param wCopies: ��ӡPDF��������������ڵ���1
	* @param wCollate: �ڴ�ӡ����ĵ�ʱ���Ƿ�������ݴ�ӡ
	* @param wDuplex: ��ӡPDF�����˫�������������ҳ��˫�泤�ߺ�˫��̱�
	* @param wPaperSource: ��ӡPDF�����ֽ��ѡ��
	* @param wPaperWidth: ���Բ���wPaperSize���Զ����ӡPDF�����ֽ�Ŵ�С�Ŀ�ȣ���λ��0.1���ף�Ҫ�����0
	* @param wPaperHeight: ���Բ���wPaperSize���Զ����ӡPDF�����ֽ�Ŵ�С�ĸ߶ȣ���λ��0.1���ף�Ҫ�����0
	* @param bUseCropBox: ��ӡPDF��CropBox��Χ���ݣ�һ��ΪFALSE
	* @param bUseFullPage: ��ӡPDF�����ݵ���ӡ�����������򣬶��Ǵ�ӡ��������������ڴ�ӡ����һ��ʹ����������
	* @param bUsePDFPageSize: ��ӡPDF������PDF����������ƥ���ֽ�ͣ�wPaperSize��ʱ��Ч
	* @param bForceGray: ��ӡPDF������ǿ��ת���ɻҶȣ�һ������wColor�����Դ�ӡ��cPrinterName��Ч�ǲ�ʹ�ã�����һ���Ĭ��ʹ��
	* @param pWaterInfo: ��ӡPDFʱ��ҳ�����ˮӡ�����ݣ�����ҳü��ҳ�ź��м�ˮӡ
	* @param callBack: ��ӡPDF�Ļص�����ָ�룬������ӡ�Ľ��ȵ���Ϣ
	* @param pCallBackData: ��ӡPDF�Ļص��ӿ��Դ�����ָ�룬�ڻص�ʱ��ԭ������
	* @return BOOL: TURE-��ӡ�ɹ���FALSE-��ӡʧ��
	*/
	//ʹ��ָ���Ĳ�����ӡPDF�ļ���ָ����ӡ��
	BOOL PrintToPrinter(const char *cPrinterName, const char *cDocName = NULL,
		int nBeginPage = -1, int nEndPage = -1, int nPagesPerPaper = 1,
		WORD wColor = DMCOLOR_MONOCHROME, WORD wPaperSize = DMPAPER_A4,
		WORD wOrientation = DMORIENT_PORTRAIT, WORD wCopies = 1,
		WORD wCollate = DMCOLLATE_TRUE,
		WORD wDuplex = DMDUP_SIMPLEX, WORD wPaperSource = DMBIN_AUTO,
		WORD wPaperWidth = 0, WORD wPaperHeight = 0,
		BOOL bUseCropBox = FALSE, BOOL bUseFullPage = TRUE,
		BOOL bUsePDFPageSize = TRUE, BOOL bForceGray = FALSE, 
		WaterInfo* pWaterInfo = NULL,
		FPrintProcessCallBack callBack = NULL, 
		PrintProcessCallBackData* pCallBackData = NULL);

	/**
	* @author zengxl
	* @param nPageIndex: PDFҳ�룬ҳ��������0��ʼ
	* @param box: ��ȡ��PDF��PageBox��Ϣ����Ϊ��������
	* @param type: ��ȡ��PDF��PageBox������
	* @return BOOL: TURE-��ȡ�ɹ���FALSE-��ȡʧ��
	*/
	//��ȡPDF��ָ��ҳ��ҳ���С
	BOOL GetPageBox(int nPageIndex, PageBox& box, PageBoxType type = MediaBox);

	/**
	* @author zengxl
	* @param nPageIndex: PDFҳ�룬ҳ��������0��ʼ
	* @return int: PDFҳ����ת�ĽǶȣ��Ƕ��ƣ���0,90,270,360
	*/
	//��ȡPDF��ָ��ҳ��ҳ����ת�ĽǶ�
	int GetPageRotate(int nPageIndex);
	
	/**
	* @author zengxl
	* @param nPageIndex: PDFҳ�룬ҳ��������0��ʼ
	* @return BOOL: TURE-��ʾ�հ�ҳ��FALSE-��ʾ�ǿհ�ҳ
	*/
	//�ж�ָ����ҳ���Ƿ�Ϊ�հ�ҳ
	BOOL IsBlankPage(int nPageIndex);

	/**
	* @author zengxl
	* @param cJobUser: ��ӡ��ҵ��ҵ�����û���UTF8����
	* @return void:
	*/
	//���ô�ӡ��ҵ��ҵ�����û�
	void SetJobUser(const char *cJobUser);

protected:
	void InitEnvironment();
	void SetPagesPerPaper(int nPagesPerPaper);
	BOOL IsBlankBitmap(ImageColorMode color, int nWidth, int nHeight, int nStride, unsigned char *scan0);

public:
	void *m_doc;			//PDFDoc
	void *m_surface;		//cairo_surface_t
	void *m_fileName;		//GooString
	void *m_outputName;		//GooString
	void *m_outputFileName;	//GooString
	void *m_imageFileName;	//GooString
	void *m_ownerPW;		//GooString
	void *m_userPW;			//GooString
	void *m_printer;		//GooString

	int m_firstPage;
	int m_lastPage;
	int m_pagesPerPaper;
	int m_currentPage;

	//
	bool m_png;
	bool m_jpeg;
	bool m_ps;
	bool m_eps;
	bool m_pdf;
	bool m_printToWin32;
	bool m_onePaperPrintCompleted;	//һ��ֽ���ݴ�ӡ���
	bool m_printdlg;
	bool m_svg;
	bool m_tiff;

	bool m_printOnlyOdd;
	bool m_printOnlyEven;
	bool m_singleFile;
	double m_max_resolution;
	double m_x_resolution;
	double m_y_resolution;
	int m_scaleTo;
	int m_x_scaleTo;
	int m_y_scaleTo;
	int m_crop_x;
	int m_crop_y;
	int m_crop_w;
	int m_crop_h;
	bool m_useCropBox;
	bool m_mono;
	bool m_gray;
	bool m_transp;

	bool m_level2;
	bool m_level3;
	bool m_origPageSizes;
	char m_paperSize[15];
	double m_paperWidth;
	double m_paperHeight;
	bool m_noCrop;
	bool m_expand;
	bool m_noShrink;
	bool m_noCenter;
	bool m_duplex;
	char m_tiffCompressionStr[16];

	bool m_setupdlg;

	bool m_useWin32PageSize;	//ǿ��ʹ��DEVMODE�е�dmPaperSize������ʹ��dmPaperWidth��dmPaperLength
	bool m_printing;
	bool m_printingAbort;		//��ӡ����ֹ
	bool m_printingOutOfMemory;	//��ӡ�ڴ治��
	FILE *m_output_file;
	bool m_usePDFPageSize;
	bool m_useFullPage;
	bool m_forceGray;	//ǿ�ƻҶ�(�ڰ�ɫ)��ӡ,
						//ĳЩ��ӡ��(��֪:ʩ��)���ܿ��ƺڰ׺Ͳ�ɫ��ӡ,
						//���ύ��ҵʱ,ǿ�ƽ���ҵ��Ⱦ�ɻҶ�ͼ.

	//
	HDC m_hdc;
	HGLOBAL m_hDevmode;
	HGLOBAL m_hDevnames;
	DEVMODEW *m_devmode;
	char* m_printerName;	//��ӡ����,UTF8����
	char* m_jobUser;		//��ӡ��ҵ�������û�,UTF8����

	bool m_useWater;
	WaterInfo* m_waterInfo;
};

#endif	//_PDFHELPER_517B7F85_B0C5_480E_B35B_199AC523DB5A_H_