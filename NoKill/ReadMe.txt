简介：此程序能让 NTSD、WMIC、TASKKILL、任务管理器等大多数进程结束工具无法结束本此程序（支持所有64位 Windows）。

运行方法：先把“NoKill”文件夹放到C盘里，然后启动服务“InjectDLL - Service.exe”。请用“启动服务.bat”来启动服务（无法双击启动服务）。
测验方法：先运行此程序，然后尝试结束“NoKill.exe”。请不要用任务管理器的“应用程序”栏结束（Windows 10 为“进程”），因为任务管理器在结束进程前会先向进程的窗口方式一个关闭消息（进程可以不接收，但我添加没加这个功能）。可以用命令行“TASKKILL /F /IM NoKill.exe”结束或用任务管理器的“进程”栏结束（Windows 10 为“详细信息”）。测试之后请重新启动电脑以回复正常。

InspectDLL.dll 原理：把“OpenProcess”的内存改为本DLL中的“NewAPI”的内存，让宿主进程调用“OpenProcess”时跳转至“NewAPI”。“NewAPI”在被调用时会检查当前PID是否等于被保护的PID（在“C:\NoKill\NoKillPID.tmp”中，支持“C:\NoKill\NoKillPID.tmp”中有多个PID，可在75行修改）。如果当前PID是否等于被保护的PID就返回0号进程（系统空闲进程）的句柄，否则把内存改回原内存，然后调用“OpenProcess”，储存结果，最后在把内存改为“NewAPI”的内存。

InspectDLL.exe 原理：定义一个容器，然后扫描系统中所有进程（包含系统进程，这就是它要以服务运行的原因），依次用一个线程注入“InspectDLL.dll”（用线程是为了防止被挂起的进程卡死）并加入容器中。接着，主线程会启动一个线程，负责扫描新的进程并将其传回主线程。与此同时，主线程启动线程2，负责扫描容器中的每个进程是否存在，如果不存在，就从容器中删除。主线程用扫描进程时用的线程的向线程1传回的进程注入“InspectDLL.dll”，并把它加入容器中。

C:\NoKill\NoKill.exe 原理：获取自身PID并写入“C:\NoKill\NoKillPID.tmp”（将自身保护起来），然后无限Sleep等待21亿毫秒。

此程序没有版权，欢迎转载。
