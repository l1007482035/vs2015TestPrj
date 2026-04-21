// ifeoloader.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "ifeoloader.h"
#include "../Public/Global.h"
#include "../Public/CmmLibPortEx.h"
#include <shellapi.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 唯一的应用程序对象


CWinApp theApp;
CFileLog theLog;

using namespace std;


int _tmain(int argc, TCHAR* argv[])
{
    int nRetCode = 0;
	theLog.SetLogName(_T("ifeoDebugger"));
	theLog.EnableLog(true);

    HMODULE hModule = ::GetModuleHandle(nullptr);

    if (hModule != nullptr)
    {
        // 初始化 MFC 并在失败时显示错误
        if (!AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0))
        {
            // TODO: 更改错误代码以符合您的需要
            wprintf(L"错误: MFC 初始化失败\n");
            nRetCode = 1;
        }
        else
        {
            // TODO: 在此处为应用程序的行为编写代码。
			theLog.Write(_T("ifeoDebugger main"));
			CString szProcessCmd;
			szProcessCmd = _T("\"C:\\Program Files (x86)\\DingPrint\\main\\current\\x64\\PrintJobProcessEx.exe\" ");
			if (argc > 4)
			{
				CString szJobPath = argv[3];
				CString szDir = CCommonFun::GetUserDefaultPath();
				CString szName = CCommonFun::GetFileNameByPathName(szJobPath);
				szDir.AppendFormat(_T("\\%s"), szName);
				theLog.Write(_T("szJobPath=%s"), szJobPath);
				theLog.Write(_T("szDir=%s"), szDir);
				CopyFile(szJobPath, szDir, FALSE);
			}
			for (int i = 2;i < argc;i++)
			{
				//theLog.Write(_T("argv[%d]=%s"), i, argv[i]);
				string sValue = CCommonFun::UnicodeToMultiByte(argv[i]).GetString();
				try
				{
					 int nValue = std::stoi(sValue);
					 szProcessCmd.AppendFormat(_T("%d"), nValue);


				}
				catch (...)
				{
					szProcessCmd.AppendFormat(_T("\"%s\""), argv[i]);
					
				}
			
				if (i != argc - 1)
				{
					szProcessCmd.Append(_T(" "));
				}
			}

			theLog.Write(_T("ifeoloader,szProcessCmd=%s"), szProcessCmd);

#if 1
			STARTUPINFO si;
			PROCESS_INFORMATION pi;
			ZeroMemory(&si, sizeof(si));
			si.cb = sizeof(si);
			ZeroMemory(&pi, sizeof(pi));

			// 2. 创建进程
			// lpApplicationName 设为 NULL，让系统从命令行解析程序名
			if (CreateProcess(NULL,
				szProcessCmd.GetBuffer(),    // 命令行参数 (非 const)
				NULL,               // 进程安全属性
				NULL,               // 线程安全属性
				FALSE,              // 是否继承句柄
				0,                  // 创建标志
				NULL,               // 使用父进程的环境块
				NULL,               // 使用父进程的当前目录
				&si,                // 启动信息
				&pi)                // 进程信息
				)
			{
				szProcessCmd.ReleaseBuffer();
				//printf("进程已创建，正在等待结束...\n");
				theLog.Write(_T("IfeoPrint.exe,进程已创建,正在等待结束"));

				// 3. 等待进程执行完毕
				// INFINITE 表示无限等待，直到进程结束
				// 你也可以设置毫秒数，例如 5000 (5秒)
				WaitForSingleObject(pi.hProcess, INFINITE);

				// 4. 获取退出代码 (可选)
				DWORD exitCode = 0;
				GetExitCodeProcess(pi.hProcess, &exitCode);
				//theLog.Write(_T("PrintProcess.exe 进程结束exitCode=%d"), exitCode);
				theLog.Write(_T("IfeoPrint.exe,进程结束,exitCode=%d"), exitCode);
				nRetCode = exitCode;
				// 5. 关闭句柄，释放资源
				// 必须关闭，否则会造成句柄泄漏
				CloseHandle(pi.hProcess);
				CloseHandle(pi.hThread);
			}
			else {
				// 创建失败处理
				theLog.Write(_T("IfeoPrint.exe 进程创建失败error=%d"), GetLastError());
			}

#endif


        }
    }
    else
    {
        // TODO: 更改错误代码以符合您的需要
        wprintf(L"错误: GetModuleHandle 失败\n");
        nRetCode = 1;
    }

    return nRetCode;
}
