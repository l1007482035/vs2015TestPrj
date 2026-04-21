// Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Test.h"
#include "../mfcDllTest/Hello.h"
#include "../CmmLib/SpdLog.h"
#pragma comment(lib,"../Release/mfcDllTest.lib")


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 唯一的应用程序对象

CWinApp theApp;
CSpdLog theLog;

using namespace std;

#include <iostream>
#include <string>
using namespace std;


#define MY_VAR_NAME(var1, var2)\
	cout << "输入的第一个宏参数名为: " << #var1 <<endl;\
	cout << "输入的第二个宏参数名为: " << #var2 <<endl;\
	cout << "两个宏参数名连接起来为: " << #var1###var2 <<endl;

#define MY_PRINT_VAR(var)\
	{	\
		cout << #var << "的值为：" << var << endl; \
	}

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

// 打印vector元素
void print(const std::string& text, const std::vector<int>& vc) {
	std::cout << text << std::endl;
	for (auto it:vc)
	{
		printf("%d ", it);
	}
	std::cout << std::endl;
}


#include <random>
#include <chrono>
#include <numeric>
#include<iostream>
#include<algorithm>
#include<functional>
using namespace std;
//自定义函数
bool cmp(int a, int b) 
{
	return a > b;
}
typedef struct student {
	char name[20];
	int math;
	int english;

}Student;

typedef struct student2 {
	char  name[20];
	int math;
	int english;
	//按math从大到小排序
	inline bool operator < (const student2 &x) const 
	{
		if (math == x.math)
		{
			return english > x.english;
		}
		return math > x.math;
	}
}Student2;

bool cmp2(Student a, Student b)
{
	if (a.math > b.math)
		return a.math < b.math;//按math从小到大排序 
	else if (a.math == b.math)
		return a.english > b.english; //math相等，按endlish从大到小排序23 
}
#undef min
#undef max
#include <iomanip>

int main() 
{
	return 0;
	std::random_device rd2;
	default_random_engine e(rd2());
	uniform_int_distribution<unsigned> u(0, 100); //随机数分布类，生成的随机数在0-100之间

	for (size_t i = 0; i < 10; ++i)
		cout << u(e) << endl; //将u作为随机数源，生成10个随机数
	return 0;
	//给定权重的随机
	std::random_device rd1;
	//std::mt19937 gen(rd1());
	std::default_random_engine engine(rd1());
	std::discrete_distribution<> distr({ 1, 2, 3, 4, 5 });
	//std::discrete_distribution<int> distr{ 2,2,1,1,2,2,1,1,2,2 };
	cout << endl;
	cout << "min() == " << distr.min() << endl;
	cout << "max() == " << distr.max() << endl;
	cout << "probabilities (value: probability):" << endl;
	vector<double> p = distr.probabilities();
	int counter = 0;
	for (const auto& n : p) {
		cout << fixed << setw(11) << counter << ": " << setw(14) << setprecision(10) << n << endl;
		++counter;
	}

	for (int i = 0;i < 10;i++)
	{
		printf("%d\n", distr(engine));
	}
	cout << endl;
	return 0;

#if 0
	Student2 a[4] = { { "apple",67,60},{ "limei",90,80},{ "apple",67 ,70} };
	sort(a, a + 3);
	for (int i = 0; i < 3; i++)
		cout << a[i].name << " " << a[i].math << " " << a[i].english << " "<<endl;
#endif
#if 0
	int s[] = { 34,56,11,23,45 };
	vector<int>arr(s, s + 5);
	sort(arr.begin(), arr.end(), greater<int>());
	for (int i = 0; i < arr.size(); i++)
		cout << arr[i] << " ";
#endif
#if 0
	Student a[4] = { { "apple",67,89 },{ "limei",90,56 },{ "apple",90,99 } };
	sort(a, a + 3, cmp2);
	for (int i = 0; i < 3; i++)
		cout << a[i].name << " " << a[i].math << " " << a[i].english << endl;
#endif
#if 0
	//sort函数第三个参数自己定义，实现从大到小
	int a[] = { 45,12,34,77,90,11,2,4,5,55 };
	sort(a, a + 10, cmp);
	for (int i = 0; i < 10; i++)
		cout << a[i] << " ";
#endif

	


#if 0
	vector<int> vData(10);  //数据
	vector<int> vIndex(10); //序号
	iota(vData.begin(), vData.end(), 0);  //递增赋值
	iota(vIndex.begin(), vIndex.end(), 0);//递增赋值
	random_shuffle(vData.begin(), vData.end());//打乱数据
	for (auto data : vData) 
	{
		cout << data << ","; 
	}
	cout << endl;
	sort(vIndex.begin(), vIndex.end(),[&vData](int a, int b) { return vData[a] > vData[b]; });//此处对数据判断，然后对序号排列
	for (auto index : vIndex) 
	{ 
		cout << vData[index] << ","; 
	}
	cout << endl;
#endif

	//return 0;

// 	
// 	for (int i = 0;i < 5;i++)
// 	{
// 		//unsigned seed = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
// 		unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
// 		cout << seed << endl;
// 	}
// 	
// 	return 0;
	//default_random_engine eng;    // 生成随机无符号数
// 	for (size_t i = 0; i < 10; i++)
// 		// e() “调用”对象来生成下一个随机数
// 		cout << e() << endl;
	std::random_device rd;
	for (int i = 0;i < 10;i++)
	{
		cout << rd() << endl;
	}

#if 0
	std::mt19937 eng(std::random_device{}());
	uniform_int_distribution<unsigned> distribution(1, 12);
	std::vector<int> numbers(10);
	std::generate(numbers.begin(), numbers.end(), [&]() {return distribution(eng); });

// 	for (int i = 0; i < 10; ++i)
// 	{
// 		e.seed(std::chrono::steady_clock::now().time_since_epoch().count());
// 		cout << u(e) << ' ';
// 	}
// 		
	for (auto it: numbers)
	{
		cout << it << " ";
	}
	cout << endl;
	for (int i = 0; i < 10;i++)
	{
		cout << distribution(eng) << " ";
	}
#endif

#if 0
	std::vector<int> vc = { 9, 7,6 ,9, 8, 2, 5, 6, 2,1 };
	print("origin vc:", vc);
	std::sort(vc.begin(), vc.end());
	print("after sort vc:", vc);
	auto index_it = std::unique(vc.begin(), vc.end());
	print("after sort + unique vc:", vc);
	vc.erase(index_it, vc.end());
	print("after sort + unique + erase vc:", vc);
	std::cin.get();
#endif
	return 0;
}

#if 0
int main()
{
    int nRetCode = 0;

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
			MY_VAR_NAME(var1, var2);
			int a = 10;
			MY_PRINT_VAR(a);
            // TODO: 在此处为应用程序的行为编写代码。

			//printf("main theLog Addr=%x\n",&theLog);
			//CHello hello;
		
			//CSpdLog one = CSpdLog::GetInstance();
			//printf("main,one=%x\n", &one);
			//hello.Func();
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
#endif