/*********************************************************************
* ��Ȩ���� (C)2011��ISafeTec��
* 
* �ļ����ƣ�  SorenOp.h
* ����ժҪ��  
* ˵    ����  
* ��ǰ�汾��  1.0.0.0
* ��    �ߣ�  SongQX
* ��    �ڣ�  2011/06/30
***********************************************************************/
#pragma once

// SorenOp������ģ�飬Ϊ�˰���SorenOPʱ�����������
#include "../Public/Include/SDefine.h"
#include "../Public/Include/SorenDefine.h"
#include "../Public/SorenCodeExport.h"
#include "../Public/SorenBaseExport.h"
#include "../Public/messageport.h"
#include "../Public/Include/CmmInterface.h"
using namespace isafetec;

// Ϊ�˷����������ȡu�̼��ܷ�ʽ����def.hͷ�ļ�
#include "../../Drivers/DevDriver/def.h"

// Soren�Լ���ͷ�ļ�
#include "../SorenOp/FileSystemControl.h"
#include "../SorenOp/SorenOp.h"
#include "../SorenOp/FileSystemLog.h"
#include "../SorenOp/deviceexport.h"

#ifdef _DEBUG
#pragma comment(lib,"..\\Debug\\sorenop.lib")
#else
#pragma comment(lib,"..\\Release\\sorenop.lib")
#endif