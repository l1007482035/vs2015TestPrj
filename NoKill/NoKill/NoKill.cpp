#include <fstream>
#include <iostream>
#include <Windows.h>

int main() {
	std::cout<<"PID:" << getpid()<<std::endl;
	std::ofstream fout("NoKillPID.tmp");
	fout << getpid();
	fout.close();
	Sleep(2100000000);
	Sleep(2100000000);
	Sleep(2100000000);
	Sleep(2100000000);
	Sleep(2100000000);
	Sleep(2100000000);
	Sleep(2100000000);
	Sleep(2100000000);
	Sleep(2100000000);
	Sleep(2100000000);
	Sleep(2100000000);
	Sleep(2100000000);
	Sleep(2100000000);
	Sleep(2100000000);
	Sleep(2100000000);
	Sleep(2100000000);
	Sleep(2100000000);
}
