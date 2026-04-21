// ThreadAndCore.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


#include <windows.h>
#include <iostream>
#include <vector>

int main() {
	DWORD bufferSize = 0;
	GetLogicalProcessorInformation(nullptr, &bufferSize);

	std::vector<SYSTEM_LOGICAL_PROCESSOR_INFORMATION> buffer(bufferSize / sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION));
	if (!GetLogicalProcessorInformation(buffer.data(), &bufferSize)) {
		std::cerr << "Error: " << GetLastError() << std::endl;
		return 1;
	}

	int physicalCoreCount = 0;
	int logicalCoreCount = 0;

	for (const auto& info : buffer) {
		if (info.Relationship == RelationProcessorCore) {
			physicalCoreCount++; // 物理核心数量
								 // 计算 ProcessorMask 中设置的位数（逻辑核心数量）
			logicalCoreCount += __popcnt(info.ProcessorMask);
		}
	}

	std::cout << "物理核心数量: " << physicalCoreCount << std::endl;
	std::cout << "逻辑核心数量: " << logicalCoreCount << std::endl;

	return 0;
}

