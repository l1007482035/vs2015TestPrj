#pragma once

#ifdef DLLEXPORT
#define DLL __declspec(dllexport)
#else
#define DLL __declspec(dllimport)
#endif

//·����ʹ�÷�б��
extern "C" DLL int WINAPI ConvertToPDF(int count, char* pdfpath, ...);
//·����ʹ�÷�б��
extern "C" DLL int WINAPI ConvertToPDF2(int arraysize, char* pdfpath, char* jpgs[]);
