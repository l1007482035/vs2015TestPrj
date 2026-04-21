// testrand.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdlib.h>
#include <time.h>


int main()
{
	srand(time(NULL));
	for (int j = 0;j < 5;j++)
	{
		char red[6] = {}, cnt = 0, i = 0;
		while (6 > cnt)
		{
			int num = rand() % 33 + 1;
			for (i = 0; i < cnt; i++)
			{
				if (num == red[i])
				{
					break;
				}
			}
			if (i == cnt)
			{
				red[cnt++] = num;
			}
		}

		printf("red:");
		for (int i = 0; i < 6; i++)
		{
			printf("%hhd ", red[i]);
		}
		printf("blue:%d\n", rand() % 16 + 1);
	}

	
    return 0;
}

