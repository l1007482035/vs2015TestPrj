// OpenMPTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


#include <omp.h>
#include <iostream>

int main()
{
	const int numThreads = 4;
	int threadCount[numThreads];

	// 初始化数组
	for (int i = 0; i < numThreads; ++i) {
		threadCount[i] = 0;
	}

	// 并行区域
#pragma omp parallel num_threads(numThreads)
	{
		int threadID = omp_get_thread_num();
		printf("=====opm,threadID=%d\n", threadID);
		threadCount[threadID]++;
	}

	// 输出每个线程的计数
	for (int i = 0; i < numThreads; ++i) {
		std::cout << "Thread " << i << " count: " << threadCount[i] << std::endl;
	}

	return 0;
}