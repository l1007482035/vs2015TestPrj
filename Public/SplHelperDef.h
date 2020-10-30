#ifndef _SPLHELPERDEF_C71D6D41_C58E_4ff8_B39E_CF694E3DC0DF_H_
#define _SPLHELPERDEF_C71D6D41_C58E_4ff8_B39E_CF694E3DC0DF_H_

enum SplType{ST_UnKnow, ST_EMF, ST_PCL, ST_PCL_5, ST_PCL_6, ST_PS, ST_PS_3, ST_PS_2, ST_XPS};

#define PostScript_Print_Param_PageSize			TEXT("/PageSize")				//ֽ�Ϳ�ߴ�С

#define PostScript_Print_Param_Duplex			TEXT("Duplex")				//˫���ӡ����
#define PostScript_Print_Param_Duplex_None		TEXT("%%BeginFeature: *Duplex None")				//�����ӡ
#define PostScript_Print_Param_Duplex_NoTumble	TEXT("%%BeginFeature: *Duplex DuplexNoTumble")	//˫�泤�ߴ�ӡ
#define PostScript_Print_Param_Duplex_Tumble	TEXT("%%BeginFeature: *Duplex DuplexTumble")	//˫��̱ߴ�ӡ
//��/Duplex true /Tumble false��	//˫�棺������ֽ����ת���رա�˫�泤��
#define PostScript_Print_Param_DuplexFlag	TEXT("/Duplex")	//˫���ӡ���أ�true/falae
#define PostScript_Print_Param_TumbleFlag	TEXT("/Tumble")	//ֽ����ת���أ�true/falae

//@PJL SET QTY = 1
#define PostScript_Print_Param_PJL_Copies	TEXT("@PJL SET QTY")

//ƻ��Mac��ӡ��PS�ļ�
#define PostScript_Print_Param_Color_On_MAC		TEXT("%%BeginFeature: *ColorModel RGB")
#define PostScript_Print_Param_Color_Off_MAC	TEXT("%%BeginFeature: *ColorModel Gray")

#define PostScript_Print_Param_Copies_L3	TEXT("%%BeginNonPPDFeature: NumCopies")
#define PostScript_Print_Param_Copies_L2	TEXT("%RBINumCopies:")
#define PostScript_Print_Param_Page_Begin	TEXT("%%BeginPageSetup")
#define PostScript_Print_Param_Page_End		TEXT("%%EndPageSetup")
#define PostScript_Print_Param_Color_On_LG	TEXT("%%BeginFeature: colorbw color")			//���
#define PostScript_Print_Param_Color_Off_LG	TEXT("%%BeginFeature: colorbw blackandwhite")	//���
#define PostScript_Print_Param_Color_On_LM	TEXT("@PJL SET RENDERMODE=COLOR")				//����
#define PostScript_Print_Param_Color_Off_LM	TEXT("@PJL SET RENDERMODE=GRAYSCALE")			//����
#define PostScript_Print_Param_Color_Off_HpUniversalPrinting	TEXT("@PJL SET GRAYSCALE=BLACKONLY")			//����ͨ��PS����
#define PostScript_Print_Param_Page_End		TEXT("%%EndPageSetup")
#define PostScript_Print_Param_Pages		TEXT("%%Pages:")
#define PostScript_Print_Param_AtEnd		TEXT("(atend)")
#define SPL_PostScript_Flag					TEXT("@PJL ENTER LANGUAGE=POSTSCRIPT")	//POSTSCRIPT �ļ���־
#define SPL_PCL_Flag						TEXT("@PJL ENTER LANGUAGE=PCL")	//pcl �ļ���־
#define SPL_PCL6_Flag						TEXT("@PJL ENTER LANGUAGE=PCLXL")	//PCL6 �ļ���־


#endif